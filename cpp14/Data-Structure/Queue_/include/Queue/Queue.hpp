/**
 * @headerfile Queue.hpp
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Queue.
 * @author Kartikei Mittal
*/

#pragma once
#ifndef __self_Queue
#define __self_Queue 1

#include <algorithm>
#include "DynamicArray/DynamicArray.hpp"
#include "SinglyLinkedList/SinglyLinkedList.hpp"
#include "Utility/Utility.hpp"

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self {

/**
 * @class Queue
 * @brief Queue Template Class.
 * @tparam T Type used for Queue
*/
template <typename T> class Queue {
public:
    // Queue() {;}  Counstructor
    virtual INTEGER size() = 0; /// Size of Queue
    virtual bool isEmpty() = 0; /// Is Queue Empty
    virtual void push(T data) = 0; /// Add Element to the queue
    virtual T pop() = 0; /// Pop Element from queue
    virtual T top() = 0; /// Top Elelement of queue
};

/**
 * @class QueueArray
 * @brief Queue Template Class, Using Array Implementation.
 * @tparam T Type used for Queue
*/
template <typename T> class QueueArray : public Queue<T> {
    static const INTEGER DEFAULT_CAPACITY = 8; /// Default Capacity of Queue
    INTEGER front; /// Place to remove element from
    INTEGER back; /// Place of NEXT element
    INTEGER len, capacity; /// Length and Capacity of the Queue
    T* st; /// Pointer to Queue Array
public:
    /**
     * @brief Queue using Array Default Counstuctor.
    */
    QueueArray():
        front(0), back(0), len(0),
        capacity(DEFAULT_CAPACITY), st(new T[DEFAULT_CAPACITY]) { ; }
    /// Destructor
    ~QueueArray() { len = back = front = 0; delete [] st; }
    /**
     * @brief Expose size of Queue.
     * @return int Number of elements in Queue
    */
    INTEGER size() { return len; }
    /**
     * @brief Checks for emptiness of QueueArray.
     * @return bool True if QueueArray empty, fals otherwise 
    */
    bool isEmpty() { return (len == 0); }
    /**
     * @brief Push Function to add elements to the back of QueueArray.
     * @param data Element to add to the QueueArray
    */
    void push(T data) {
        if (len == capacity) {
            T* new_arr = new T[capacity * 2];
            INTEGER index = 0;
            for (INTEGER i = front; i < capacity; ++i) {
                new_arr[index++] = st[i];
            }
            if (front > back) {
                for (INTEGER i = 0; i < back; ++i) {
                    new_arr[index++] = st[i];
                }
            }
            delete [] st;
            st = new T[capacity * 2];
            std::copy(new_arr, new_arr + len, st);
            capacity *= 2;
            front = 0;
            back = len;
        }
        ++len;
        st[back] = data;
        back = (back + 1) % capacity;
    }
    /**
     * @brief Pop Function to remove elements from the back of QueueArray.
     * @return T Element to popped from the QueueArray
     * @throw exception Queue underflow
    */
    T pop() {
        if (len == 0) { throw exception("Queue Underflow."); }
        --len;
        T data = st[front];
        front = (front + 1) % capacity;
        return data;
    }
    /**
     * @brief Provides element at top of the QueueArray.
     * @return T Element at top of the Queue
     * @throw exception Queue underflow
    */
    T top() {
        if (len == 0) { throw exception("Queue Underflow."); }
        return st[front];
    }
    // ========================================================== ITERATOR CLASS ======================================================
    /**
     * @class QueueArray::iterator
     * @brief QueueArray iterator class.
    */
    class iterator {
        bool traversed; /// Flag to mark traversal in empty queue
        T *ptr; /// Pointer to Current element
        T *begin_; /// Pointer to first element
        T *end_; /// Pointer to last element
    public:
        /**
         * @brief Iterator Counstructor function.
         * @param ptr_ Pointer for Iterator
         * @param b Pointer to begin
         * @param e Pointer to end
         * @param len_ Length of Queue
        */
        iterator(
            T *ptr_,
            T *b = NULL,
            T *e = NULL,
            INTEGER len_ = 0
        ): ptr(ptr_), begin_(b), end_(e) { traversed = (len_ != 0); }
        /**
         * @brief Iterator increment overload defination.
         * @return iterator Incremented iterator
        */
        iterator operator++() {
            if (ptr == end_ - 1) {
                ptr = begin_;
            } else {
                ++ptr;
            } return *this;
        }
        /**
         * @brief Inequality != method overload.
         * @param other Other iterator to check inequality against
         * @return bool True if end of iteration is reached
        */
        bool operator!=(const iterator &other) {
            if (traversed) {
                traversed = false;
                return true;
            } return ptr != other.ptr;
        }
        /**
         * @brief Element access overload method.
         * @return T Data at current pointer
        */
        const T operator*() const { return *ptr; }
    };
    /// Begin Iterator
    iterator begin() { return iterator(st + front, st, st + capacity, len); }
    /// End Iterator
    iterator end() { return iterator(st + back); }
    // ============================================================================================================================
};

/**
 * @class QueueLinkedList
 * @brief Queue Template Class, Using Linked List Implementation.
 * @tparam T Type used for Queue
*/
template <typename T> class QueueLinkedList : public Queue<T> {
    SinglyLinkedList<T> st; /// Linked List Member
public:
    QueueLinkedList() = default; /// Default Counstructor
    /**
     * @brief Expose size of Queue.
     * @return int Number of elements in Queue
    */
    INTEGER size() { return st.size(); }
    /**
     * @brief Checks for emptiness of QueueLinkedList.
     * @return bool True if QueueLinkedList empty, fals otherwise 
    */
    bool isEmpty() { return st.isEmpty(); }
    /**
     * @brief Push Function to add elements to the back of QueueLinkedList.
     * @param data Element to add to the QueueLinkedList
    */
    void push(T data) { st.append(data); }
    /**
     * @brief Pop Function to remove elements from the back of QueueLinkedList.
     * @return T Element to popped from the QueueLinkedList
     * @throw exception Queue Underflow
    */
    T pop() {
        if (st.isEmpty()) { throw exception("Queue Underflow."); }
        T data = st.get(0);
        st.removeFirst();
        return data;
    }
    /**
     * @brief Provides element at top of the QueueLinkedList.
     * @return T Element at top of the Queue
     * @throw exception Queue Underflow
    */
    T top() {
        if (st.isEmpty()) { throw exception("Queue Underflow."); }
        return st.get(0);
    }
    // ========================================================== ITERATOR CLASS ======================================================
    /**
     * @class QueueLinkedList::iterator
     * @brief QueueLinkedList iterator class.
    */
    class iterator {
        typename SinglyLinkedList<T>::iterator ptr; /// Linked List Iterator
    public:
        /**
         * @brief Iterator counstructor.
         * @param ptr Linked List Iterator
        */
        explicit iterator(typename SinglyLinkedList<T>::iterator ptr): ptr(ptr) { ; }
        /**
         * @brief Iterator Increment operator
         * @return iterator Incremented Iterator
        */
        iterator operator++() { ++ptr; return *this; }
        /**
         * @brief Inequality != method overload.
         * @param other Other iterator to check inequality against
         * @return bool True if end of iteration is reached
        */
        bool operator!=(const iterator &other) const { return ptr != other.ptr; }
        /**
         * @brief Element access overload method.
         * @return T Data at current pointer
        */
        const T operator*() const { return *ptr; }
    };
    /// Begin Iterator
    iterator begin() { return iterator(st.begin()); }
    /// End Iterator
    iterator end() { return iterator(st.end()); }
    // ============================================================================================================================
};

} // namespace self
#endif
