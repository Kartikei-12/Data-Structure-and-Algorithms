/**
 * @headerfile BinaryTree.hpp
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Binary tree.
 * @author Kartikei Mittal
*/

#pragma once
#ifndef __self_BinaryTree
#define __self_BinaryTree 1

#include <string>
#include "Utility/Utility.hpp"
#include "NodeTwoChild/NodeTwoChild.hpp"
#include "Stack/Stack.hpp"
#include "Queue/Queue.hpp"

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self {

/**
 * @class BinaryTree
 * @brief Binary Tree Template Class.
 * @tparam T Type used for Binary Tree
*/
template <typename T>
class BinaryTree
{protected:
    typedef NodeTwoChild<T>* TreeNodePtr;  /// @typedef TreeNodePtr
    INTEGER count;  /// count Number of nodes in binary tree
    TreeNodePtr root;  /// Node Pointer to root
    /**
     * @brief Default find member function.
     * @param element Element to look for
     * @param curr Current node to search
     * @return Node data found at
    */
    virtual TreeNodePtr find(const T& element, TreeNodePtr curr) {
        if (curr -> getData() == element) { return curr; }
        TreeNodePtr temp = nullptr;
        temp = find(element, curr -> getLeft());
        if (temp != nullptr) { return temp; }
        temp = find(element, curr -> getRight());
        if (temp != nullptr) { return temp; }
        return nullptr;
    }
    /**
     * @brief Recusive delete function.
     * @param curr Current Node to delete
    */
    void _delete(TreeNodePtr curr) {
        if (curr != nullptr) {
            _delete(curr -> getLeft());
            _delete(curr -> getRight());
            delete curr;
        }
    }

 public:
    BinaryTree(): count(0), root(nullptr) { ; }  /// Default Counstructor
    ~BinaryTree() { _delete(root); count = 0;}  /// Destructor
    /**
     * @brief Checks for emptiness of binary tree.
     * @return bool True if tree empty, fals otherwise 
    */
    bool isEmpty() { return (count == 0); }
    /**
     * @brief Expose size of binary tree.
     * @return int Number of nodes in tree
    */
    INTEGER size() { return count; }
    /**
     * @brief Check for presence of given element.
     * @param element Element to look for
     * @return bool True if element present
    */
    bool contains(T element) { return find(element, root) != nullptr; }
    /**
     * @brief Calculate height of the tree.
     * @param curr Node to start from
     * @return int Height of tree
    */
    INTEGER height(TreeNodePtr curr = nullptr) {
        if (curr == nullptr) { curr = root; }
        if (curr == nullptr) { return 0; }
        INTEGER ans = 0, nodeCount = 1;
        QueueLinkedList<TreeNodePtr> que;
        que.push(curr);
        while (!que.isEmpty()) {
            nodeCount = que.size();  // Nodes in current Level
            ++ans;
            while (nodeCount--) {
            // For all nodes of Current Level, Remove them,
            // Add their children if any(millennials you know)
                curr = que.pop();
                if (curr -> getLeft()) { que.push(curr -> getLeft()); }
                if (curr -> getRight()) { que.push(curr -> getRight()); }
            }
        }
        return ans;
    }

    /// Pure virtual function add
    virtual void add(T element) = 0;
    /// Pure virtual function remove
    virtual bool remove(T element) = 0;
    /// Pure virtual function overload assignment = operator
    virtual void operator=(std::initializer_list<T> list) = 0;
    // =========================   ITERATOR CLASSS    =========================
    // =========================  INN ORDER ITERATOR  =========================
    // =========================  PRE ORDER ITERATOR  =========================
    // ========================= POST ORDER ITERATOR  =========================
    // ========================= LEVEL ORDER ITERATOR =========================
    /**
     * @class BinaryTree::iterator
     * @brief Binary Tree iterator class.
    */
    class iterator {
        INTEGER nodeCount;  /// Expected node count of tree
        std::string itype;  /// Type of iterator
        Stack<TreeNodePtr, Array> stack;  /// Stack
        QueueArray<TreeNodePtr> que;  /// Queue

     public:
        /**
         * @brief Iterator class counstructor function.
         * @param nodeCount_ Initial node count of the tree
         * @param curr Root node
         * @param itype_ Type of iterator
         * @throw exception When iterator type is unknown
        */
        explicit iterator(
            INTEGER nodeCount_,
            TreeNodePtr curr = nullptr,
            std::string itype_ = "END"):
            itype(itype_), nodeCount(nodeCount_) {
            if (itype == "IN ORDER") {
                while (curr != nullptr) {
                    stack.push(curr); curr = curr -> getLeft();
                }
            } else if (itype == "PRE ORDER") {
                stack.push(curr);
            } else if (itype == "POST ORDER") {
                while (curr != nullptr) {
                    stack.push(curr); curr = curr -> getLeft();
                }
            } else if (itype == "LEVEL ORDER") {
                que.push(curr);
            } else if (itype == "END") { ; } else {
                throw exception("Unknown iterator type: " + itype);
            }
        }
        /**
         * @brief Iterator increment overload defination.
         * @return iterator Incremented iterator
        */
        iterator operator++() {
            TreeNodePtr curr;
            if (itype == "IN ORDER") {
                curr = stack.pop() -> getRight();
                while (curr != nullptr) {
                    stack.push(curr); curr = curr -> getLeft();
                }
            } else if (itype == "PRE ORDER") {
                curr = stack.pop();
                if (curr -> getLeft()) { stack.push(curr -> getLeft()); }
                if (curr -> getRight()) { stack.push(curr -> getRight()); }
            } else if (itype == "POST ORDER") {
                curr = stack.pop();
                if (stack.size() != 0 && curr != stack.top() -> getRight()) {
                    curr = stack.top() -> getRight();
                    while (curr != nullptr) {
                        stack.push(curr);
                        curr = curr -> getLeft();
                    }
                }
            } else if (itype == "LEVEL ORDER") {
                curr = que.pop();
                if (curr -> getLeft()) { que.push(curr -> getLeft()); }
                if (curr -> getRight()) { que.push(curr -> getRight()); }
            }
            return *this;
        }
        /**
         * @brief Function to check for end of iteratation.
         * @return bool True if iteration end
        */
        bool isEnd() {
            if (itype == "END") { return true; }
            return (itype == "LEVEL ORDER")? que.isEmpty():stack.isEmpty();
        }
        /**
         * @brief Inequality != method overload.
         * @param other Other iterator to check inequality against
         * @return bool True if end of iteration is reached
         * @throw exception Iterator Invalidation exception
        */
        bool operator!=(const iterator & other) {
            if (itype == "END") { return false; }
            if (nodeCount != other.nodeCount) {
                throw exception("BST Iterator Invalidation.");
            }
            return isEnd();
        }
        /**
         * @brief Element access overload method.
         * @return T Data at top of stack or queue
         * @throw exception Accessing End iterator data
        */
        const T operator*() {
            if (itype == "END") { throw exception("End iterator data"); }
            if (itype == "LEVEL ORDER") { return que.top() -> getData(); }
            return stack.top() -> getData();
        }
    };
    /// Begin Iterator
    iterator begin(std::string itype) { return iterator(count, root, itype); }
    /// End Iterator
    iterator end() { return iterator(count); }
    // ======================================================================================================================
};

}  // namespace self
#endif
