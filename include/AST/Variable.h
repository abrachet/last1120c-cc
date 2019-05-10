/**
 * @file LocalVar.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "Type.h"
#include "Token.h"
#include "Modifier.h"

struct Variable {
    Modifier modifier;
    Type  type;
    Token name;
};
