/**
 * @headerfile BinarySearchTree.hpp
 * @brief Binary Search Tree.
 * @author Kartikei Mittal
*/
#pragma once
#ifndef __self_BinarySearchTree
#define __self_BinarySearchTree 1

#include "NodeTwoChild/NodeTwoChild.hpp"
#include "BinaryTree/BinaryTree.hpp"

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self
{

/**
 * @class BinarySearchTree
 * @brief Template Class Which defines Binary Search Tree.
 * @tparam T Type of elements in Binary Search Tree.
 * @tparam comprator_ Comparator Class for type T.
*/
template <typename T, typename comprator_ = void>
class BinarySearchTree: public BinaryTree<T> {
    typedef NodeTwoChild<T>* TreeNodePtr; /// @typedef TreeNodePtr
    
    /**
     * @brief Comparator class enabled if comparator class supplied.
     * @tparam Q Used to route comprator_.
     * @param a First Element
     * @param b Second Element
     * @return bool True if a is less than b False otherwise
    */
    template <typename Q = comprator_>
    ENABLE_IF(!IS_SAME(Q, void), bool)
    comprator(T a, T b) {
        comprator_ comp;
        return comp(a, b);
    }
    /**
     * @brief Comparator class enabled if comparator class NOT supplied.
     * @tparam Q Used to route comprator_.
     * @param a First Element
     * @param b Second Element
     * @return bool True if a is less than b False otherwise
    */
    template <typename Q = comprator_>
    ENABLE_IF(IS_SAME(Q, void), bool)
    comprator(T a, T b) { return a < b; }

    /**
     * @brief Find function for Binary Search Tree.
     * @param element Element to search for
     * @param curr Current node to search
     * @return TreeNodePtr Pointer to node with required data
    */
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
    /**
     * @brief Find minimum child of given node.
     * @param curr Pointer to node whose minimum child is needed
     * @return TreeNodePtr Pointer to minimum child
    */
    TreeNodePtr findMinChild(TreeNodePtr curr) {
        while (curr -> getLeft() != nullptr) { curr = curr -> getLeft(); }
        return curr;
    }
    /**
     * @brief Find maximum child of given node.
     * @param curr Pointer to node whose maximum child is needed
     * @return TreeNodePtr Pointer to maximum child
    */
    TreeNodePtr findMaxChild(TreeNodePtr curr) {
        while (curr -> getRight() != nullptr) { curr = curr -> getRight(); }
        return curr;
    }
    /**
     * @brief Recursive function to remove given element.
     * @param curr Current node
     * @param element Element to remove
     * @return TreeNodePtr New child after removal 
    */
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
    BinarySearchTree(): BinaryTree<T>() { ; } /// Counstrunctor

    /**
     * @brief Overload assignment operator.
     * @param list Brace enclosed list
    */
    void operator=(std::initializer_list<T> list) {
        BinaryTree<T>::_delete(BinaryTree<T>::root);
        BinaryTree<T>::root = nullptr;
        for (T element: list) { add(element); }
    }
    /**
     * @brief Add method for Binary Search Tree
     * @param element Element to add
    */
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
    /**
     * @brief Remove Method for Binary Search Tree
     * @param element Element to remove
     * @return bool True if successful removal
    */
    bool remove(T element) {
        if (!BinaryTree<T>::contains(element)) { return false; }
        BinaryTree<T>::root = remove(BinaryTree<T>::root, element);
        --BinaryTree<T>::count;
        return true;
    }
};

}
#endif
