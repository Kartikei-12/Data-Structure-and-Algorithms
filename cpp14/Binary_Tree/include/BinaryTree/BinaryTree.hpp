// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Binary Tree

#pragma once
#ifndef __self_BinaryTree
#define __self_BinaryTree 1

#include "Utility/Utility.hpp"
#include "NodeTwoChild/NodeTwoChild.hpp"
#include "Stack/Stack.hpp"
#include "Queue/Queue.hpp"

namespace self
{

template <typename T>
class BinaryTree
{protected:
    typedef NodeTwoChild<T>* TreeNodePtr;
    INTEGER count;
    TreeNodePtr root;

    virtual TreeNodePtr find(T& element, TreeNodePtr curr) {
        if (curr -> getData() == element) {
            return curr;
        }
        TreeNodePtr temp = nullptr;
        temp = find(element, curr -> getLeft());
        if (temp != nullptr) { return temp; }
        temp = find(element, curr -> getRight());
        if (temp != nullptr) { return temp; }
        return nullptr;
    }
    void _delete(TreeNodePtr curr) {
        if (curr != nullptr) {
            _delete(curr -> getLeft());
            _delete(curr -> getRight());
            delete curr;
        }
    }
public:
    BinaryTree(): count(0), root(nullptr) { ; }
    ~BinaryTree() { _delete(root); count = 0;}
    
    bool isEmpty() { return (count == 0); }
    INTEGER size() { return count; }
    bool contains(T element) { return find(element, root) != nullptr; }    
    INTEGER height(TreeNodePtr curr = nullptr) {
        if (curr == nullptr) { curr = root; }
        if (curr == nullptr) { return 0; }
        INTEGER ans = 0, nodeCount = 1;
        QueueLinkedList<TreeNodePtr> que;
        que.push(curr);
        while (!que.isEmpty()) {
            nodeCount = que.size(); // Nodes in current Level
            ++ans;
            while (nodeCount--) {
            // For all nodes of Current Level, Remove them, Add their children if any(millennials you know)
                curr = que.pop();
                if (curr -> getLeft() != nullptr) { que.push(curr -> getLeft()); }
                if (curr -> getRight() != nullptr) { que.push(curr -> getRight()); }
            }
        }
        return ans;
    }

    virtual void add(T element) = 0;
    virtual bool remove(T element) = 0;
    virtual void operator=(std::initializer_list<T> list) = 0;
    // =================================================   ITERATOR CLASSS    =================================================
    // =================================================  INN ORDER ITERATOR  =================================================
    // =================================================  PRE ORDER ITERATOR  =================================================
    // ================================================= POST ORDER ITERATOR  =================================================
    // ================================================= LEVEL ORDER ITERATOR =================================================
    class iterator
    {
        INTEGER nodeCount;
        std::string itype;
        StackArray<TreeNodePtr> stack;
        QueueArray<TreeNodePtr> que;
    public:
        iterator(
            INTEGER nodeCount_,
            TreeNodePtr curr = nullptr,
            std::string itype_ = "END"
        ):
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
        iterator operator++() {
            TreeNodePtr curr;
            if (itype == "IN ORDER") {
                curr = stack.pop() -> getRight();
                while (curr != nullptr) {
                    stack.push(curr); curr = curr -> getLeft();
                }
            } else if (itype == "PRE ORDER") {
                curr = stack.pop();
                if (curr -> getLeft() != nullptr) { stack.push(curr -> getLeft()); }
                if (curr -> getRight() != nullptr) { stack.push(curr -> getRight()); }
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
                if (curr -> getLeft() != nullptr) { que.push(curr -> getLeft()); }
                if (curr -> getRight() != nullptr) { que.push(curr -> getRight()); }
            }
            return *this;
        }
        bool isEnd() {
            if (itype == "END") { return true; }
            if (itype == "LEVEL ORDER") { return que.isEmpty(); }
            return stack.isEmpty();
        }
        bool operator!=(const iterator & other) {
            if (nodeCount != other.nodeCount) {
                throw exception("Binary Search Tree Iterator Invalidation.");
            } return isEnd();
        }
        const T operator*() {
            if (itype == "LEVEL ORDER") { return que.top() -> getData(); }
            return stack.top() -> getData();
        }    
    };
    iterator begin(std::string itype) { return iterator(count, root, itype); }
    iterator end() { return iterator(count); }
    // ======================================================================================================================
};

}
#endif
