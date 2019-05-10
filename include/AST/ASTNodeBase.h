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

class AbstractVisitor;

class ASTNodeBase {
public:

    using ast_tag = AstTag::undefined_tag;

    virtual void accept(AbstractVisitor&) = 0;
    virtual ~ASTNodeBase() {}
};