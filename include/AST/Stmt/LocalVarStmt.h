/**
 * @file LovalVarStmt.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Node for the keyword auto, meaning stack allocated. In the form
 * auto var1, var2, ...; 
 * @version 0.1
 * @date 2019-05-10
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Stmt.h"
#include "AbstractVisitor.h"
#include "Token.h"
#include "AST/Variable.h"
#include <vector>

class LocalVarStmt : public Stmt {
    Variable local_var;

};
