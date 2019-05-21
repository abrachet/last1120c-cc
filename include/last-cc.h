/**
 * @file CC.hh
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief 
 * @version 0.1
 * @date 2019-05-07
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#define likely(x)      __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

