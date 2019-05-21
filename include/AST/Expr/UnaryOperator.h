/**
 * @file UnaryOperator.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Class for unary operators like ++ or --
 * @version 0.1
 * @date 2019-05-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Expr.h"
#include <memory>

struct UnaryOperator : public Expr {
    enum Type : unsigned char {
        Increment,          // ++
        Decrement,          // --
        Positive,           // +
        Negative,           // -
        LogicalNegation,    // !
        Negation,           // ~
        Addressof,          // &
        Indirection,        // *
    };

    const Type    type:7;
    const bool  prefix:1;

    std::shared_ptr<Expr> operand;

    UnaryOperator(Type type, bool prefix = true)
    : type(type), prefix(prefix)
    {}

    virtual ~UnaryOperator() {}

    void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }

};
