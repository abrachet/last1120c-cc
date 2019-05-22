/**
 * @file ARM64.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-21
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "AST/AbstractVisitor.h"
#include "AST/Decl/GlobalVarDecl.h"
#include "AST/Decl/FunctionDecl.h"
#include "AST/Variable.h"
#include "AST/Stmt/ExternStmt.h"
#include "AST/Stmt/AutoStmt.h"
#include "AST/Expr/AssignmentExpr.h"
#include "AST/Expr/BinaryOperator.h"
#include "AsmStream.h"
#include <string>
#include <cstring>
#include <map>
#include <memory>

/**
 * 
 * For expressions x9 is used as the result of any expression and x10 
 * and x11 are where the results of the left and right hand of that expressions
 * reside. For example a = 1 + 2 would be turned into
 * mov x10, #1
 * mov x11, #2
 * add x9, x10, x11
 * str x9, [sp, 8] // or wherever 'a' is
 * 
 * This of course is many more instructions than it needs to be. But this is
 * the easiest way if we had something like a = (1 + 2) * 3
 * it then becomes 
 * mov x10, #1
 * mov x11, #2
 * add x9, x10, x11
 * mov x10, x9
 * mov x11, #3
 * mul x9, x10, x11
 * 
 * By using this way, all binary operators are very easy to implement its
 * always <mnemonic> x9, x10, x11. This increases uniformity. Also the result of
 * any expression is always stored in x9. For example:
 * a return statement is generalized as return(<expr>);
 * so wether we have return(0) or reutrn((1 + 2) * 3);
 * the return is now easy, we evaulate the expression, in the case of 0:
 * mov x9, #0
 * and then return:
 * // stack maintence omitted
 * mov, r0, x9
 * ret
 * 
 * Choosing these registers makes sense because they are temporary
 * general use registers. They may get clobered but we dont care if they are just
 * used to compute expressions. 
 */
class ARM64Backend : public AbstractVisitor {
    AsmStream<> stream;

    struct {
        FunctionDecl* func = nullptr;
        Token function_name;
        // from extern declarations
        std::vector<Token> known_symbols;
        std::vector<Variable> auto_vars; // locals

        std::size_t stack_size = 0;

        std::map<Token, std::string> variable_locations;
        
        bool in_function_scope = false;
        bool done_with_local_decls = false;

        void enter_function(FunctionDecl* fd) 
        {
            in_function_scope = true;
            function_name = fd->get_name();
            func = fd;
        }

        void exit_function() 
        {
            known_symbols.clear();
            auto_vars.clear();
            variable_locations.clear();
            in_function_scope = false;
            done_with_local_decls = false;
            stack_size = 0;
            func = nullptr;
        }

    } current_function;

    /**
     * @todo of course this doesn't account for chars not being 
     * the same width as ints
     * 
     */
    void calc_size()
    {
        if (current_function.done_with_local_decls)
            return;

        char buf[64];

        current_function.done_with_local_decls = true;
        current_function.stack_size = (2 + current_function.auto_vars.size()) * 8;

        const uint64_t stack_size = current_function.stack_size;

        stream.write("stp x29, x30, [sp, -%lu]!", stack_size);
        stream.write("mov x29, sp");

        uint64_t sp = stack_size - 24;
        auto args = current_function.func->get_args();
        for (int i = 0; i < args.size(); i++) {
            snprintf(buf, 64, "[sp, %lu]", sp);
            std::string func_arg = buf;
            current_function.variable_locations[args[i].name] = func_arg;
            stream.write("str x%d, %s", i, buf);
            sp -= 8;
        }

        uint64_t current = stack_size - 8;
        
        for (auto& i : current_function.auto_vars) {
            snprintf(buf, 64, "[sp, %lu]", current);
            current -= 8;
            current_function.variable_locations[i.name] = std::string(buf);
        }

        for (auto& i : current_function.known_symbols) {
            std::string str = i.to_string();
            str = "=" + str;
            current_function.variable_locations[i] = str;
        }
    }

    static void emit_expr(std::shared_ptr<Expr> expr)
    {
        //static char buf[64];
        if (auto* bo = dynamic_cast<BinaryOperator*>(expr.get())) {
            
        }
    }

public:
    ARM64Backend(const char* asmfile)
    : stream(asmfile)
    {}

    void visit(GlobalVarDecl& gv) override 
    {
        const char* name = gv.get_token().to_string().c_str();

        int64_t init_value = gv.get_value();

        std::size_t size = gv.is_array() ? init_value * 8 : 8;

        stream.write(".global %s", name);
        stream.write("%s", gv.is_array() ? ".bss" : ".data");
        stream.write(".type %s, %%object", name);
        stream.write(".size %s, %zu", name, size);
        stream.write_label("%s:", name);
        
        if (gv.is_array())
            stream.write(".zero %zu", size);
        else
            stream.write(".xword %ld", init_value);
    }


    void visit(FunctionDecl& fd) override 
    {
        const char* name = fd.get_name().to_string().c_str();

        stream.write(".text");
        stream.write(".global %s", name);
        stream.write(".type %s, %%function", name);
        stream.write_label("%s:", name);

        current_function.enter_function(&fd);

        auto statements = fd.get_statments();

        auto args = fd.get_args();
        if (args.size() > 8) {
            std::cerr << "too many arguments passed for function: " << name << std::endl;
            std::terminate();
        }


        for (auto i : statements)
            i->accept(*this);

        stream.write("ldp x29, x30, [sp], %ld", current_function.stack_size);
        stream.write("ret");
        current_function.exit_function();
    }

    void visit(ExternStmt& es) override 
    {
        assert(current_function.in_function_scope && "not in function");
        calc_size();

        auto& vec = current_function.known_symbols;
        auto& ins = es.get_tokens();

        vec.insert(vec.begin(), ins.begin(), ins.end());
    }

    void visit(AutoStmt& as) override 
    {
        assert(current_function.in_function_scope && "not in function");
        calc_size();

        auto& vec = current_function.auto_vars;
        auto& ins = as.get_tokens();

        vec.insert(vec.begin(), ins.begin(), ins.end());
    }

    void visit(AssignmentExpr& ae) override 
    {
        auto right_expr = ae.get_right_side();

        right_expr->accept(*this);

        std::string location = current_function.variable_locations[ae.get_left_side()];

        stream.write("str x9, %s", location.c_str());
    }

    void visit(BinaryOperator& bo) override 
    {

    }

};
