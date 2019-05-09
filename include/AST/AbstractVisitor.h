/**
 * @file AbstractVisitor.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-08
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "ASTNodeBase.h"

class AbstractVisitor {
public:
    virtual void visit(ASTNodeBase&) = 0;
};
