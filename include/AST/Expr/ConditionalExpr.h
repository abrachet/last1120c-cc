/**
 * @file ConditionalExpr.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Expr.h"
#include "AbstractVisitor.h"

struct ConditionalExpr : public Expr {

    void accept(AbstractVisitor& av) override {
        return av.visit(*this);
    }
};
