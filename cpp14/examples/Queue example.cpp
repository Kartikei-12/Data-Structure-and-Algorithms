// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Stack Example Application
#include <iostream>
#include "Queue/Queue.hpp"

int main(int argc, char const *argv[])
{
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
