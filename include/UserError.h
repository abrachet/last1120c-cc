/**
 * @file UserError.h
 * @author Alex Brachet (abrachet@purdue.edu)
 * @brief Class for logging user erros in their source code
 * @version 0.1
 * @date 2019-05-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */
#pragma once

#include <string>
#include <cassert>

class UserError {
    std::string error;
    bool is_error;

public:
    UserError()
    : is_error(false) 
    {}

    UserError(std::string error)
    : error(std::move(error)), is_error(true)
    {}

    UserError(UserError&) = delete;

    void make_error(std::string err)
    {
        assert(!is_error && "UserError already was an error");
        this->error = err ;
        this->is_error = true;
    }

    const std::string& get_error()
    {
        assert(is_error && "tried to get error from non_error");
        return error;
    }

    inline operator bool() const 
    {
        return is_error;
    }


};