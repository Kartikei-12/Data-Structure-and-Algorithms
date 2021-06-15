// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Utility Code Header

#ifndef __self_Utility
#define __self_Utility 1
#pragma once

#include <stdint.h>
#include <exception>

namespace self
{

using INTEGER = int64_t;
class exception : public std::exception
{
   std::string s;
public:
   exception(std::string ss): s(ss) {}
   ~exception() throw () {}
   const char* what() const throw() { return s.c_str(); }
};

}

#endif
