#include "utility test.hpp"

namespace self
{

UDTfT::UDTfT(int a_, char b_, double c_) { set(a_, b_, c_); }
UDTfT::UDTfT(const UDTfT& other) { a = other.a; b = other.b; c = other.c; }
void UDTfT::set(int a_, char b_, double c_) { a = a_; b = b_; c = c_; }
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

}
