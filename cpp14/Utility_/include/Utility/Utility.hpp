// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Utility Code Header

#pragma once
#ifndef __self_Utility
#define __self_Utility 1

#include <string>
#include <stdint.h>
#include <exception>

namespace self
{

using INTEGER = int64_t;
class exception : public std::exception
{
   std::string s;
public:
   exception(std::string ss): s(ss) { ; }
   ~exception() throw () { ; }
   const char* what() const throw() { return ("Exception: " + s).c_str(); }
};
#define ENABLE_IF(condition, type_) typename std::enable_if<condition, type_>::type 
#define IS_SAME(a, b) std::is_same<a, b>::value

}

#endif
