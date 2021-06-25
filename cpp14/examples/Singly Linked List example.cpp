/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Singly Linked List Example.
 * @author Kartikei Mittal
*/

#include <iostream>
#include "SinglyLinkedList/SinglyLinkedList.hpp"

int main(int argc, char const *argv[])
{
    std::cout << "Hello Singly Linked List!" << std::endl;
    self::SinglyLinkedList<int> singly_linked_list;
    singly_linked_list = {1, 2};
    singly_linked_list.append(25);
    for (int i:singly_linked_list) {
        std::cout << i << std::endl;
    }
    return 0;
}
