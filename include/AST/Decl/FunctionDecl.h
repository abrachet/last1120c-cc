/**
 * @file FunctionDecl.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Decl.h"
#include "AbstractVisitor.h"
#include "Token.h"
#include "LocalVar.h"
#include "NodeList.h"
#include "Type.h"
#include "AST/Tags.h"
#include <vector>

class FunctionDecl : public Decl {
    Type return_type;
    Token function_name;

    NodeList statements;

    
public:

    using ast_tag = AstTag::recursive_tag;


    FunctionDecl(Token name)
    : return_type(Type(Token("int", 3), 8)), function_name(name)
    {}

    virtual ~FunctionDecl() {}

    virtual void accept(AbstractVisitor& av) override {
        av.visit(*this);
    }

    
    Token get_name() 
    {
        return this->function_name;
    }

};
