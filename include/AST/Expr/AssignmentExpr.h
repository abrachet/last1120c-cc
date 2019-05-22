/**
 * @file AssignmentExpr.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief represents assignment to a variable
 * @version 0.1
 * @date 2019-05-22
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Expr.h"
#include "Token.h"
#include <memory>

class AssignmentExpr : public Expr {
    Token left_var;
    std::shared_ptr<Expr> right_side;


public:
    AssignmentExpr(Token left_var, std::shared_ptr<Expr> e = nullptr)
    : left_var(left_var), right_side(e)
    {}

    const std::shared_ptr<Expr>& get_right_side() const 
    {
        return this->right_side;
    }

    Token get_left_side() const 
    {
        return this->left_var;
    }
};
