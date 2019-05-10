/**
 * @file NodeList.h
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
#include <vector>
#include <memory>

using NodeList = std::vector<std::shared_ptr<ASTNodeBase>>;
