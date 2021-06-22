// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Singly Linked List

#pragma once
#ifndef __self_BinarySearchTree
#define __self_BinarySearchTree 1

#include "NodeTwoChild/NodeTwoChild.hpp"
#include "BinaryTree/BinaryTree.hpp"

namespace self
{

template <typename T, typename comprator_ = void>
class BinarySearchTree: public BinaryTree<T> {
    typedef NodeTwoChild<T>* TreeNodePtr;
    
    template <typename Q = comprator_>
    ENABLE_IF(!IS_SAME(Q, void), bool)
    comprator(T a, T b) {
        comprator_ comp;
        return comp(a, b);
    }

    template <typename Q = comprator_>
    ENABLE_IF(IS_SAME(Q, void), bool)
    comprator(T a, T b) { return a < b; }

    TreeNodePtr find(T& element, TreeNodePtr curr) {
        curr = BinaryTree<T>::root;
        while (curr != nullptr) {
            if (element == curr -> getData()) {
                return curr;
            } // Wally FOUND
            if (comprator(element, curr -> getData())) {
                curr = curr -> getLeft();
            } // Move Left
            else {
                curr = curr -> getRight();
            } // Move Right
        }
        return nullptr; // NOT Found
    }
    TreeNodePtr findMinChild(TreeNodePtr curr) {
        while (curr -> getLeft() != nullptr) { curr = curr -> getLeft(); }
        return curr;
    }
    TreeNodePtr findMaxChild(TreeNodePtr curr) {
        while (curr -> getRight() != nullptr) { curr = curr -> getRight(); }
        return curr;
    }
    TreeNodePtr remove(TreeNodePtr curr, T element) {
        if (curr == nullptr) { return nullptr; }
        if (curr -> getData() == element) {
            if (curr -> getLeft() == nullptr) { return curr -> getRight(); }
            if (curr -> getRight() == nullptr) { return curr -> getLeft(); }
            
            INTEGER leftHeight = BinaryTree<T>::height(curr -> getLeft());
            INTEGER rightHeight = BinaryTree<T>::height(curr -> getRight());
            TreeNodePtr temp;
            if (leftHeight < rightHeight) {
                temp = findMinChild(curr -> getRight());
                curr -> setData(temp -> getData());
                curr -> setRight(
                    remove(curr -> getRight(), curr -> getData())
                );
            } else {
                temp = findMaxChild(curr -> getLeft());
                curr -> setData(temp -> getData());
                curr -> setLeft(remove(curr -> getLeft(), curr -> getData()));
            }
        } else if (comprator(element, curr -> getData())) {
            curr -> setLeft(remove(curr -> getLeft(), element));
        } else {
            curr -> setRight(remove(curr -> getRight(), element));
        } return curr;
    }
public:
    BinarySearchTree(): BinaryTree<T>() { ; }
    void operator=(std::initializer_list<T> list) {
        BinaryTree<T>::_delete(BinaryTree<T>::root);
        BinaryTree<T>::root = nullptr;
        for (T element: list) { add(element); }
    }
    void add(T element) {
        ++BinaryTree<T>::count;
        if (BinaryTree<T>::root == nullptr) {
            BinaryTree<T>::root = new NodeTwoChild<T>(element); return;
        }
        TreeNodePtr curr = BinaryTree<T>::root;
        while (true) {
            if (comprator(element, curr -> getData())) {
                if (curr -> getLeft() == nullptr) {
                    curr -> setLeft(new NodeTwoChild<T>(element));
                    break;
                }
                curr = curr -> getLeft();
            } else {
                if (curr -> getRight() == nullptr) {
                    curr -> setRight(new NodeTwoChild<T>(element));
                    break;
                }
                curr = curr -> getRight();
            }
        }
    }
    bool remove(T element) {
        if (!BinaryTree<T>::contains(element)) { return false; }
        BinaryTree<T>::root = remove(BinaryTree<T>::root, element);
        --BinaryTree<T>::count;
        return true;
    }
};

}
#endif
