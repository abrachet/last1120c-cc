/**
 * @file IfStmt.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Stmt.h"
#include "AbstractVisitor.h"
#include "AST/Variable.h"
#include "AST/Tags.h"
#include <vector>

class IfStmt : public Stmt {

    

public:
    using ast_tag = AstTag::recursive_tag;


};
