/**
 * @file AssignmentExpr.h
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

struct AssignmentExpr : public Expr {
    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }
};
