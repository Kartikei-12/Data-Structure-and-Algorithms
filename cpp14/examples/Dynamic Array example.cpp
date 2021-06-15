// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Dynamic Array Example Application
#include <iostream>
#include "DynamicArray/DynamicArray.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "Hello Dynamic Array!" << std::endl;
    self::DynamicArray<int> dynamic_array;
    dynamic_array = {1, 2};
    dynamic_array.append(25);
    for (int i:dynamic_array) {
        std::cout << i << std::endl;
    }
    return 0;
}
