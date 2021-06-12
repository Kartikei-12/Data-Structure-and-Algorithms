// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Some Utility for testing purpose header

#ifndef __self_UtilityForTest
#define __self_UtilityForTest
#pragma once

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
// bool operator==(const UDTfT& first, const UDTfT& other);
// bool operator!=(const UDTfT& first, const UDTfT& other);

}
#define ENABLE_IF(condition) typename std::enable_if<condition>::type 
#define IS_SAME(a, b) std::is_same<a, b>::value

#endif