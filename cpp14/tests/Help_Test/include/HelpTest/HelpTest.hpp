// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Some Utility for testing purpose header

#ifndef __self_HelpTest
#define __self_HelpTest
#pragma once

#include "gtest/gtest.h"

namespace self
{

class UDTfT // User Defined Data Type for Testing
{
    int a; char b; double c;
public:
    UDTfT(int a_ = 0, char b_ = ' ', double c_ = 1.5);
    UDTfT(const UDTfT& other);
    void set(int a_, char b_, double c_);
    friend bool operator==(const UDTfT& first, const UDTfT& other);
    friend bool operator!=(const UDTfT& first, const UDTfT& other);
};

template<typename A, typename B>
struct Encapsulation {
    typedef A main_;
    typedef B base_;
};

#define TestTypes ::testing::Types<INTEGER, char, UDTfT>
#define ENABLE_IF(condition) typename std::enable_if<condition>::type 
#define IS_SAME(a, b) std::is_same<a, b>::value

}

#endif
