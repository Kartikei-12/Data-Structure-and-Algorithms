// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Example Application
#include <iostream>
#include "DynamicArray/DynamicArray.hpp"
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
