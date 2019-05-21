/**
 * @file Expr.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "AST/ASTNodeBase.h"
#include "AST/Tags.h"
#include "AST/AbstractVisitor.h"
#include "Token.h"
#include <vector>

class Expr : public ASTNodeBase {
    std::vector<Token> tokens;

public:
    using ast_tag = AstTag::leaf_tag;

    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }
};
