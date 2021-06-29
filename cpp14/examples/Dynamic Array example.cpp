/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Dynamic Array Example.
 * @author Kartikei Mittal
*/

#include <iostream>
#include "DynamicArray/DynamicArray.hpp"

int main(int argc, char const *argv[]) {
    std::cout << "Hello Dynamic Array!" << std::endl;
    self::DynamicArray<int> dynamic_array;
    dynamic_array = {1, 2};
    dynamic_array.append(25);
    for (int i:dynamic_array) {
        std::cout << i << std::endl;
    }
    return 0;
}
