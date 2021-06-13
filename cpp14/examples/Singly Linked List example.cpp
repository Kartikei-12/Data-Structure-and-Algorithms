// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// SinglyLinkedList Example Application
#include <iostream>
#include "SinglyLinkedList/SinglyLinkedList.hpp"
using namespace std;

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
