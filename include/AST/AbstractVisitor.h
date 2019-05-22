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

#include <stdexcept>
#include <iostream>

class ASTNodeBase;

class FunctionDecl;
class GlobalVarDecl;

class ExternStmt;
class AutoStmt;

class Expr;
class ConditionalExpr;
class BinaryOperator;
class UnaryOperator;
class SingleTokenExpr;
class NumberExpr;
class AssignmentExpr;

class AbstractVisitor {

    // this is better than pure virtual because in testing I dont need to 
    // implement all of these. In any real situation this has the same effect anyway
    [[noreturn]] static void not_implemented() {
        std::cerr << "Function was visited but not overriden" << std::endl;
        std::terminate();
    }

public:
    
    virtual void visit(ASTNodeBase&)     { not_implemented(); }

    virtual void visit(GlobalVarDecl&)   { not_implemented(); }
    virtual void visit(FunctionDecl&)    { not_implemented(); }

    virtual void visit(ExternStmt&)      { not_implemented(); }
    virtual void visit(AutoStmt&)        { not_implemented(); }

    virtual void visit(Expr&)            { not_implemented(); }
    virtual void visit(AssignmentExpr&)  { not_implemented(); }
    virtual void visit(ConditionalExpr&) { not_implemented(); }
    virtual void visit(BinaryOperator&)  { not_implemented(); }
    virtual void visit(UnaryOperator&)   { not_implemented(); }
    virtual void visit(SingleTokenExpr&) { not_implemented(); }
    virtual void visit(NumberExpr&)      { not_implemented(); }

};
