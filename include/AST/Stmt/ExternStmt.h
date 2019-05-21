/**
 * @file ExternStmt.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief represents an 'extern' statement. In the form 'extern symbol1, symbol2, ...;'
 * @version 0.1
 * @date 2019-05-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Stmt.h"
#include "AbstractVisitor.h"
#include "Token.h"
#include "AST/Tags.h"
#include <vector>

class ExternStmt : public Stmt {
    std::vector<Token> tokens;

public:

    using ast_tag = AstTag::leaf_tag;

    ExternStmt(std::vector<Token> tokens)
    : tokens(std::move(tokens))
    {}

    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }

};