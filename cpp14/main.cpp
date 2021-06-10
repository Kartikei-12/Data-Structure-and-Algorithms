#include <iostream>
#include "Dynamic Array/Dynamic Array.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
    std::cout << "Hello World!" << std::endl;
    self::DynamicArray<int> aa = {1, 2};
    for (int i:aa) {
        std::cout << i << std::endl;
    }
    return 0;
}
