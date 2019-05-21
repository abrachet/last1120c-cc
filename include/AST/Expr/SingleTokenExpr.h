/**
 * @file SingleTokenExpr.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Expressions for a single token like a variable or a literal
 * @version 0.1
 * @date 2019-05-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Expr.h"

class SingleTokenExpr : public Expr {
    Token token;

public:
    SingleTokenExpr(Token token)
    : token(token)
    {}

    virtual ~SingleTokenExpr() {}

    inline const Token& get_token() const {
        return this->token;
    }

    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }

};
