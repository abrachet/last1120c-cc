/**
 * @file BinaryOperator.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Mathematical operators which take two operands
 * @version 0.1
 * @date 2019-05-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Expr.h"
#include "Token.h"
#include "last-cc_assert.h"
#include <memory>

class BinaryOperator : public Expr {


public:

    /// Can be Or'd with Assignment to make it compound ie += / =+ (old C style)
    enum Type : unsigned char {
        None = 0,
        Addition = 1,
        Subtraction,
        Multiplication,
        Division,
        Equality,

        Assignment = 1 << 7,
    };

    BinaryOperator(Type type, Type ord = None) 
    : type( static_cast<Type>(type | ord) )
    {
        if (type != Assignment)
            cc_assert(ord == None || ord == Assignment, "ord may only be of" 
                    "type Assignment or None");

        if (type == Assignment || ord == Assignment)
            cc_assert(ord != Equality && type != Equality, "cannot have Assignment"
                    " | Equality");
    }

    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }

    inline void 
    add_children(std::shared_ptr<Expr> l, std::shared_ptr<Expr> r)
    {
        this->left  = l;
        this->right = r;
    }

    inline Type get_type() const
    {
        return this->type;
    }

    const std::shared_ptr<Expr>& get_right() const
    {
        return this->right;
    }

    const std::shared_ptr<Expr>& get_left() const
    {
        return this->left;
    }

private:
    Type type;
    std::shared_ptr<Expr> left;
    std::shared_ptr<Expr> right;
};
