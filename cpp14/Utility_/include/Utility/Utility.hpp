/**
 * @headerfile Utility.hpp
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Utility code for the project.
 * @author Kartikei Mittal
*/

#pragma once
#ifndef __self_Utility
#define __self_Utility 1

#include <stdint.h>
#include <string>
#include <exception>

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self {

using INTEGER = int64_t;
/**
 * @class exception
 * @brief Exception class for the project.
*/
class exception : public std::exception {
   std::string s; /// Exception message string
public:
   explicit exception(std::string ss): s(ss) { ; }
   ~exception() throw (){ ; }
   const char* what() const throw() { return ("Exception: " + s).c_str(); }
};
#define ENABLE_IF(condition, type_) typename std::enable_if<condition, type_>::type
#define IS_SAME(a, b) std::is_same<a, b>::value

} // namespace self

#endif
