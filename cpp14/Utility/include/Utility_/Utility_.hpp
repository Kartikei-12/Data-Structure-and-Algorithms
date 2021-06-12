// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Utility Code Header

#ifndef __self_Utility
#define __self_Utility 1
#pragma once

#include <string>
#include <exception>
#include <stdint.h>

namespace self
{

typedef int64_t INTEGER;
class exception: public std::exception
{
    std::string message;
public:
    exception(std::string msg = "");
    virtual const char* what() const throw();
};

}

#endif
