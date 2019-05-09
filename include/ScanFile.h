/**
 * @file ScanFile.hh
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-07
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include "TokenizedFile.h"

/**
 * @brief Returns a list of all scanned tokens from a file
 * 
 * @param filename name of file to 
 * @return valid if valid file, none if invalid file
 */
TokenizedFile scan_file(const char* filename) noexcept(false);
