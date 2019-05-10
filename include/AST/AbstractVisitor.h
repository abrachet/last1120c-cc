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

class FunctionDecl;
class GlobalVarDecl;

class ExternStmt;
class AutoStmt;

class Expr;
class ConditionalExpr;

class AbstractVisitor {
public:

    virtual void visit(GlobalVarDecl&) = 0;
    virtual void visit(FunctionDecl&)  = 0;

    virtual void visit(ExternStmt&);
    virtual void visit(AutoStmt&);

    virtual void visit(Expr&);
    virtual void visit(ConditionalExpr&);

};
