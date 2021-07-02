/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Binary Search Tree Example.
 * @author Kartikei Mittal
*/

#include <iostream>
#include "BinarySearchTree/BinarySearchTree.hpp"

int main(int argc, char const *argv[]) {
    std::cout << "Hello Binary Search Tree!" << std::endl;
    self::BinarySearchTree<int> tree;
    int arr[] = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
    int size = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < size; ++i) {
        tree.add(arr[i]);
    }
    std::cout << std::endl
              << "------------------------------------------------------------"
              << std::endl;
    std::cout << "IN order" << std::endl;
    for (auto i = tree.begin("IN ORDER"); !i.isEnd(); ++i) {
        std::cout << *i << ", ";
    }
    std::cout << std::endl
              << "------------------------------------------------------------"
              << std::endl;
    std::cout << "PRE order" << std::endl;
    for (auto i = tree.begin("PRE ORDER"); !i.isEnd(); ++i) {
        std::cout << *i << ", ";
    }
    std::cout << std::endl
              << "------------------------------------------------------------"
              << std::endl;
    std::cout << "POST order" << std::endl;
    for (auto i = tree.begin("POST ORDER"); !i.isEnd(); ++i) {
        std::cout << *i << ", ";
    }
    std::cout << std::endl
              << "------------------------------------------------------------"
              << std::endl;
    std::cout << "LEVEL order" << std::endl;
    for (auto i = tree.begin("LEVEL ORDER"); !i.isEnd(); ++i) {
        std::cout << *i << ", ";
    }
    std::cout << std::endl
              << "------------------------------------------------------------"
              << std::endl;

    std::cout << "Count: " << tree.size() << std::endl;
    std::cout << "Contains 1: " << tree.contains(1) << std::endl;
    std::cout << "Contains 22: " << tree.contains(22) << std::endl;
    std::cout << "Height: " << tree.height() << std::endl;


    tree.remove(8);
    std::cout << std::endl
              << "------------------------------------------------------------"
              << std::endl;
    std::cout << "IN order" << std::endl;
    for (auto i = tree.begin("IN ORDER"); !i.isEnd(); ++i) {
        std::cout << *i << ", ";
    }
    std::cout << std::endl
              << "------------------------------------------------------------"
              << std::endl;
    std::cout << "PRE order" << std::endl;
    for (auto i = tree.begin("PRE ORDER"); !i.isEnd(); ++i) {
        std::cout << *i << ", ";
    }
    std::cout << std::endl
              << "------------------------------------------------------------"
              << std::endl;
    std::cout << "POST order" << std::endl;
    for (auto i = tree.begin("POST ORDER"); !i.isEnd(); ++i) {
        std::cout << *i << ", ";
    }
    std::cout << std::endl
              << "------------------------------------------------------------"
              << std::endl;

    std::cout << "Count: " << tree.size() << std::endl;
    std::cout << "Contains 1: " << tree.contains(1) << std::endl;
    std::cout << "Contains 22: " << tree.contains(22) << std::endl;
    std::cout << "Height: " << tree.height() << std::endl;
    return 0;
}
