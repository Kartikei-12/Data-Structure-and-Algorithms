/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Queue Example.
 * @author Kartikei Mittal
*/

#include <iostream>
#include "Queue/Queue.hpp"

int main(int argc, char const *argv[]) {
    std::cout << "Hello Queue Array!" << std::endl;
    self::QueueArray<int> que;
    for (int i = 1; i <= 10; ++i) {
        que.push(i);
    }
    while (!que.isEmpty()) {
        std::cout << que.pop() << ", ";
    } std::cout << std::endl;
    // -----------------------------------------------------------------------------------
    std::cout << "Hello Queue Linked List!" << std::endl;
    self::QueueLinkedList<int> que_;
    for (int i = 1; i <= 10; ++i) {
        que_.push(i);
    }
    while (!que_.isEmpty()) {
        std::cout << que_.pop() << ", ";
    } std::cout << std::endl;
    return 0;
}
