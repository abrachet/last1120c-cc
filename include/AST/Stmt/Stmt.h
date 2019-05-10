/**
 * @file Stmt.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "ASTNodeBase.h"

class Stmt : public ASTNodeBase {
public:
    virtual void accept(AbstractVisitor& av) = 0;
    virtual ~Stmt() {}
};
