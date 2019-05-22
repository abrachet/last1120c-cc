/**
 * @file NumberExpr.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Expr.h"

class NumberExpr : public Expr {
    int64_t value;

public:
    NumberExpr(int64_t value)
    : value(value)
    {}

    virtual ~NumberExpr() {}

    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }

    inline int64_t get_value() const {
        return value;
    }
};
