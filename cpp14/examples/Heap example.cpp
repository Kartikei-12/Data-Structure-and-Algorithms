// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Heap Example Application
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
