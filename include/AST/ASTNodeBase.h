/**
 * @file ASTNodeBase.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-08
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Tags.h"
#include "AbstractVisitor.h"


class ASTNodeBase {
public:

    using ast_tag = AstTag::undefined_tag;

    virtual void accept(AbstractVisitor& av) //= 0;
    {av.visit(*this);}

    virtual ~ASTNodeBase() {}
};