// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Some Utility for testing purpose header

#ifndef __self_HelpTest
#define __self_HelpTest
#pragma once

#include <ostream>

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
    friend struct ComparatorClass;
    friend struct InverseComparatorClass;
    friend std::ostream& operator<<(std::ostream& os, const UDTfT& dt);
};

struct ComparatorClass
{
    bool operator()(UDTfT A, UDTfT B);
};
struct InverseComparatorClass
{
    bool operator()(UDTfT A, UDTfT B);
};

template<typename A, typename B, bool inverse_ = false, typename comparator_ = void>
struct Encapsulation {
    typedef A main_;
    typedef B base_;
    const static bool inverse = inverse_;
    typedef comparator_ CompClass;
};

#define TestTypes ::testing::Types<INTEGER, char, UDTfT>
#define T_main typename T::main_
#define T_base typename T::base_

}

#endif
