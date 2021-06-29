/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Stack Example.
 * @author Kartikei Mittal
*/

#include <iostream>
#include "Stack/Stack.hpp"

int main(int argc, char const *argv[]) {
    std::cout << "Hello Stack Array!" << std::endl;
    self::StackArray<int> st;
    for (int i = 1; i <= 10; ++i) {
        st.push(i);
    }
    while (!st.isEmpty()) {
        std::cout << st.pop() << ", ";
    } std::cout << std::endl;
    // -----------------------------------------------------------------------------------
    std::cout << "Hello Stack Linked List!" << std::endl;
    self::StackLinkedList<int> st_;
    for (int i = 1; i <= 10; ++i) {
        st_.push(i);
    }
    while (!st_.isEmpty()) {
        std::cout << st_.pop() << ", ";
    } std::cout << std::endl;
    return 0;
}
