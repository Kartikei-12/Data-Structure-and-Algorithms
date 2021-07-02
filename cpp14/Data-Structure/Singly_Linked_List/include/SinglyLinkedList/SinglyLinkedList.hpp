/**
 * @headerfile SinglyLinkedList.hpp
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Singly Linked List.
 * @author Kartikei Mittal
*/

#pragma once
#ifndef __self_SinglyLinkedList
#define __self_SinglyLinkedList 1

#include "Utility/Utility.hpp"
#include "NodeOneChild/NodeOneChild.hpp"

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self {

/**
 * @class SinglyLinkedList
 * @brief Singly Linked List Template Class.
 * @tparam T Type used for SinglyLinkedList
*/
template <typename T>
class SinglyLinkedList {
    typedef NodeOneChild<T>* SLL_Node_ptr;  /// Create Linked List Node Pointer
    INTEGER len;  /// Size of Linked List
    SLL_Node_ptr head; SLL_Node_ptr tail;  /// Pointer to head and tail

 public:
    /**
     * @brief Default Singly Linked List Counstructor.
    */
    SinglyLinkedList(): len(0), head(nullptr), tail(nullptr) { ; }
    /**
     * @brief Overload assignment operator.
     * @param list_ Brace enclosed list
    */
    void operator=(std::initializer_list<T> list_) {
        _clear();
        len = 0;
        if (list_.size() == 0) { return ; }
        ++len;
        head = tail = new NodeOneChild<T>(*list_.begin());
        for (
            typename std::initializer_list<T>::iterator i = list_.begin() + 1;
            i != list_.end();
            ++i, ++len
        ) {
            tail -> setNext(new NodeOneChild<T>(*i));
            tail = tail -> getNext();
        }
    }

    /// Delete Copy Counstructor
    SinglyLinkedList(const SinglyLinkedList&) = delete;
    /// Delete copy through assignment
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
    /// Destructor
    ~SinglyLinkedList() { _clear(); }
    /**
     * @brief Method to clear linked list data.
     * @throw exception If 'len' does not match number of nodes
    */
    void _clear() {
        bool attempt = false;
        while (len > 0) {
            attempt = removeLast();
            if (!attempt) { throw exception("Linked List Integrity Failed"); }
        }
    }

    /**
     * @brief Expose size of linked list.
     * @return int Number of elements in linked list
    */
    INTEGER size() { return len; }
    /**
     * @brief Checks for emptiness of linked list.
     * @return bool True if linked list empty, fals otherwise 
    */
    bool isEmpty() { return (len == 0); }

    /**
     * @brief Getter Method for linked list.
     * @param index Index of Element to access
     * @return T Element at given index
     * @throw exception If an invalid exception is recieved
    */
    T get(INTEGER index) {
        if (index < 0) { index += size(); }
        if (index < 0 || index >= len) {
            throw exception("Illegal Index on length: " + std::to_string(len));
        }
        SLL_Node_ptr curr = head;
        while (index--) {
            curr = curr -> getNext();
        }
        return curr -> getData();
    }
    /**
     * @brief Route Getter Method for [] opewrator overload.
     * @param index Index of Element to access
     * @return T Element at given index
     * @throw exception If an invalid index is recieved
    */
    T operator[](INTEGER index) { return get(index); }
    void set(T elem, INTEGER index) {
        if (index < 0 || index >= len) {
            throw exception("Illegal Index on length: " + std::to_string(len));
        }
        SLL_Node_ptr curr = head;
        while (index--) {
            curr = curr -> getNext();
        }
        curr -> setData(elem);
    }
    /**
     * @brief Add method.
     * @param elem Element to add
     * @param index Place to add new element
     * @throw exception If an invalid index is recieved
    */
    void add(T elem, INTEGER index) {
        if (index < 0 || index >= len) {
            throw exception("Illegal Index Insertion: " + std::to_string(len));
        }
        if (index == 0) {
            add_first(elem);
            return;
        }
        --index;
        SLL_Node_ptr inFrontOf = head;
        SLL_Node_ptr new_node = new NodeOneChild<T>(elem);
        while (index--) {
            inFrontOf = inFrontOf -> getNext();
        }
        new_node -> setNext(inFrontOf -> getNext());
        inFrontOf -> setNext(new_node);
        ++len;
    }
    /**
     * @brief Method to add element at head of linked list.
     * @param elem Element to add
    */
    void add_first(T elem) {
        SLL_Node_ptr new_head = new NodeOneChild<T>(elem);
        new_head -> setNext(head);
        head = new_head;
        if (tail == nullptr) { tail = head; }
        ++len;
    }
    /**
     * @brief Append method.
     * @param elem Element to append
    */
    void append(T elem) {
        ++len;
        if (tail == nullptr) {
            head = tail = new NodeOneChild<T>(elem);
        } else {
            tail -> setNext(new NodeOneChild<T>(elem));
            tail = tail -> getNext();
        }
    }
    /**
     * @brief Find function.
     * @param elem Element to search for
     * @return int Element index if found, -1 otherwise
    */
    INTEGER find(T elem) {
        INTEGER ans = -1;
        SLL_Node_ptr curr = head;
        for (
            INTEGER index = 0;
            index < len && curr != nullptr;
            ++index, curr = curr -> getNext()
        ) {
            if (curr -> getData() == elem) {
                ans = index;
                break;
            }
        } return ans;
    }
    /**
     * @brief Check for presence of given element.
     * @param elem Element to look for
     * @return bool True if element present
    */
    bool contains(T elem) { return (find(elem) != -1); }
    /**
     * @brief Element removal function.
     * @param elem Element to remove
     * @return bool If successfull removal 
    */
    bool remove(T elem) {
        if (head -> getData() == elem) { return removeFirst(); }  // Found Start
        if (tail -> getData() == elem) { return removeLast(); }  // Found End
        SLL_Node_ptr curr = head;
        SLL_Node_ptr curr_next = nullptr;
        while (curr -> getData() != elem && curr != nullptr) {
            curr = curr -> getNext();
        }
        if (curr == nullptr) { return false; }  // Not Found
        curr_next = curr -> getNext();
        curr -> setData(curr_next -> getData());
        curr -> setNext(curr_next -> getNext());
        curr_next -> setNext(nullptr);
        if (curr_next == tail) { tail = curr; }
        delete curr_next;
        --len;
        return true;
    }
    /**
     * @brief Remove last element.
     * @return bool If successfull removal 
    */
    bool removeLast() {
        if (tail == nullptr) { return false; }
        if (head == tail) {
            SLL_Node_ptr curr = head;
            head = tail = nullptr;
            len = 0;
            delete curr;
            return true;
        }
        SLL_Node_ptr curr = head;
        while (curr -> getNext() != tail) {
            curr = curr -> getNext();
        }
        tail = curr;
        tail -> setNext(nullptr);
        delete curr -> getNext();
        --len;
        return true;
    }
    /**
     * @brief Remove HEAD.
     * @return bool If successfull removal 
    */
    bool removeFirst() {
        if (head == nullptr) { return false; }
        if (head == tail) {
            SLL_Node_ptr curr = head;
            head = tail = nullptr;
            len = 0;
            delete curr;
            return true;
        }
        SLL_Node_ptr curr = head;
        head = head -> getNext();
        delete curr;
        --len;
        return true;
    }
    // ============================ ITERATOR CLASS ========================
    /**
     * @class SinglyLinkedList::iterator
     * @brief Singly Linked List iterator class.
    */
    class iterator {
        SLL_Node_ptr ptr_; SLL_Node_ptr end;  /// Pointer to current and end

     public:
        /**
         * @brief Iterator Counstructor
         * @param ptr Node Pointer
         * @param end_ Iterator to end
        */
        explicit iterator(SLL_Node_ptr ptr, SLL_Node_ptr end_ = NULL):
            ptr_(ptr), end(end_) { ; }
        /**
         * @brief Iterator increment overload defination.
         * @return iterator Incremented iterator
        */
        iterator operator++() { ptr_ = ptr_ -> getNext(); return *this; }
        /**
         * @brief Inequality != method overload.
         * @param other Other iterator to check inequality against
         * @return bool True if end of iteration is reached
         * @throw exception Iterator Invalidation exception
        */
        bool operator!=(const iterator & other) const {
            if (end != other.ptr_) {
                throw exception("Iterator Invalidation.");
            }
            return ptr_ != other.ptr_;
        }
        /**
         * @brief Element access overload method.
         * @return T Data at current pointer
        */
        const T operator*() const { return ptr_ -> getData(); }
    };
    /// Begin Iterator
    iterator begin() { return iterator(head, tail); }
    /// End Iterator
    iterator end() { return iterator(tail); }
    // ============================================================================================================================
};

}  // namespace self
#endif
