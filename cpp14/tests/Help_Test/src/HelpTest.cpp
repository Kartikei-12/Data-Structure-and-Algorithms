// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Some Utility for testing purpose source

#include "HelpTest/HelpTest.hpp"

namespace self
{

UDTfT::UDTfT(int a_/* = 0*/, char b_/* = ' '*/, double c_/* = 1.5*/) { set(a_, b_, c_); }
UDTfT::UDTfT(const UDTfT& other) { a = other.a; b = other.b; c = other.c; }
void UDTfT::set(int a_, char b_, double c_) { a = a_; b = b_; c = c_; }
UDTfT operator+(const UDTfT& first, const UDTfT& other) {
    return UDTfT(first.a + other.a, first.b, first.c);
}
bool operator==(const UDTfT& first, const UDTfT& other) {
    return 
        first.a == other.a &&
        first.b == other.b &&
        first.c == other.c ;
}
bool operator!=(const UDTfT& first, const UDTfT& other) {
    return
        first.a != other.a ||
        first.b != other.b ||
        first.c != other.c ;
}
std::ostream& operator<<(std::ostream& os, const UDTfT& ob)
{
    os << "(" << ob.a << ", " << ob.b << ", " << ob.c << ")";
    return os;
}

bool ComparatorClass::operator()(UDTfT A, UDTfT B) { return A.a <= B.a; }
bool InverseComparatorClass::operator()(UDTfT A, UDTfT B) { return A.a >= B.a; }
}
