/**
 * @file AutoStmt.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Node for the keyword auto, meaning stack allocated. In the form
 * auto var1, var2, ...; 
 * @version 0.1
 * @date 2019-05-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Stmt.h"
#include "AbstractVisitor.h"
#include "AST/Variable.h"
#include "AST/Tags.h"
#include <vector>

class AutoStmt : public Stmt {
    std::vector<Variable> tokens;

public:

    using ast_tag = AstTag::leaf_tag;
    
    AutoStmt(std::vector<Variable> tokens)
    : tokens(std::move(tokens))
    {}

    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }

    const std::vector<Variable>& get_tokens() const {
        return this->tokens;
    }
};