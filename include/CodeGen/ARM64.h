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

#include "AsmStream.h"

class ARM64Backend : public AbstractVisitor {
    AsmStream<> stream;

public:
    ARM64Backend(const char* asmfile)
    : stream(asmfile)
    {}

    void visit(GlobalVarDecl& gv) override {
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
};
