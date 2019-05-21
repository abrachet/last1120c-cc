/**
 * @file CCAssert.hh
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Provides assert macro which throws instead of abort() this is useful for 
 * testing with gtest
 * @version 0.1
 * @date 2019-05-06
 * 
 * @copyright Copyright (c) 2019
 */
#pragma once

#include <stdexcept>

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define LINE_STRING STRINGIZE(__LINE__)

#ifndef NDEBUG
#define cc_assert(e, message) \
    static_cast<bool>(e) ? \
        (void) 0 : \
        throw std::runtime_error( "cc assertation failed: " #e " | " message " [" __FILE__ ":" LINE_STRING "]" )
#else
#define cc_assert(e, message) (void) 0
#endif
