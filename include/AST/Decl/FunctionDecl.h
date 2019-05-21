/**
 * @file FunctionDecl.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Token.h"
#include "Decl.h"
#include "AST/Type.h"
#include "AST/NodeList.h"
#include "AST/AbstractVisitor.h"
#include "AST/Tags.h"
#include "AST/Variable.h"
#include <vector>

class FunctionDecl : public Decl {
    const Type return_type;
    const Token function_name;

    std::vector<Variable> arguments;

    NodeList statements;

public:

    using ast_tag = AstTag::recursive_tag;

    FunctionDecl(Token function_name, Type return_type = BuiltinTypes::builtin_int)
    : return_type(return_type), function_name(function_name)
    {}

    FunctionDecl(const FunctionDecl &) = default;

    FunctionDecl& operator=(const FunctionDecl &) = default;

    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }

    inline const std::vector<Variable>& get_args() const
    {
        return arguments;
    }

    inline void add_arguments(std::vector<Variable> vec)
    {
        arguments.insert(arguments.end(), vec.begin(), vec.end());
    }

    inline void add_argument(Variable v)
    {
        this->arguments.push_back(v);
    }

    
    inline const Token get_name() const noexcept
    {
        return this->function_name;
    }

    inline void add_statment(std::shared_ptr<ASTNodeBase> stmt) 
    {
        statements.push_back(std::move(stmt));
    }

};
