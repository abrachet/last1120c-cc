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

//#include "ASTNodeBase.h"
#include <stdexcept>
#include <iostream>

class ASTNodeBase;

class FunctionDecl;
class GlobalVarDecl;

class ExternStmt;
class AutoStmt;

class Expr;
class ConditionalExpr;

class AbstractVisitor {

    [[noreturn]] static void not_implemented() {
        std::cerr << "Function was visited but not overriden" << std::endl;
        std::terminate();
    }

public:
    
    virtual void visit(ASTNodeBase&) { 
        std::cout << "visit(ASTNodeBase&)\n"; 
        not_implemented(); 
    }
    

    virtual void visit(GlobalVarDecl&)   { not_implemented(); }
    virtual void visit(FunctionDecl&)    { not_implemented(); }

    virtual void visit(ExternStmt&)      { not_implemented(); }
    virtual void visit(AutoStmt&)        { not_implemented(); }

    virtual void visit(Expr&)            { not_implemented(); }
    virtual void visit(ConditionalExpr&) { not_implemented(); }

};
