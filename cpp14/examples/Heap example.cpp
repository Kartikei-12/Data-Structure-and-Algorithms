/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Heap Example.
 * @author Kartikei Mittal
*/

#include <iostream>
#include "Heap/heap.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "Hello Heap!" << std::endl;
    self::Heap<int> hp;
    hp = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    hp.add(25);
    while (!hp.isEmpty()) {
        std::cout << hp.pop() << ", ";
    } std::cout << std::endl;
    return 0;
}
