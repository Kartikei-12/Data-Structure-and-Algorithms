/**
 * @headerfile Stack.hpp
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Stack.
 * @author Kartikei Mittal
*/

#pragma once
#ifndef __self_Stack
#define __self_Stack 1

#include "DynamicArray/DynamicArray.hpp"
#include "SinglyLinkedList/SinglyLinkedList.hpp"
#include "Utility/Utility.hpp"

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self
{

/**
 * @class Stack
 * @brief Stack Template Class.
 * @tparam T Type used for Stack
*/
template <typename T> class Stack
{
public:
    // Stack() {;}
    virtual INTEGER size() = 0; /// Size of stack
    virtual bool isEmpty() = 0; /// Is Stack Empty
    virtual void push(T data) = 0; /// Add element to stack 
    virtual T pop() = 0; /// Pop element from stack
    virtual T top() = 0; /// Get top element of stack
};

/**
 * @class StackArray
 * @brief Stack Template Class, Using Array Implementation.
 * @tparam T Type used for Stack
*/
template <typename T> class StackArray : public Stack<T>
{
    DynamicArray<T> st; /// Array object for stack
public:
    /// Default Counstructor
    StackArray() = default;

    /**
     * @brief Expose size of Stack.
     * @return int Number of elements in Stack
    */
    INTEGER size() { return st.size(); }
    /**
     * @brief Checks for emptiness of StackArray.
     * @return bool True if StackArray empty, fals otherwise 
    */
    bool isEmpty() { return st.isEmpty(); }
    /**
     * @brief Push Function to add elements to the top of StackArray.
     * @param data Element to add to the StackArray
    */
    void push (T data) { st.append(data); }
    /**
     * @brief Pop Function to remove elements from StackArray.
     * @return T Element to popped from the StackArray
     * @throw exception Stack underflow
    */
    T pop() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        T data = st.get(size() - 1);
        st.removeAt(size() - 1);
        return data;
    }
    /**
     * @brief Provides element at top of the StackArray.
     * @return T Element at top of the Stack
     * @throw exception Stack underflow
    */
    T top() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        return st.get(size() - 1);
    }
    // ========================================================== ITERATOR CLASS ======================================================
    /**
     * @class StackArray::iterator
     * @brief StackArray iterator class.
    */
    class iterator
    {
        typename DynamicArray<T>::iterator ptr_; /// Dynamic Array Iterator
    public:
        /**
         * @brief Iterator Counstructor function.
         * @param ptr Dynamic Array Iterator
        */
        iterator(typename DynamicArray<T>::iterator ptr): ptr_(ptr) {}
        /**
         * @brief Iterator increment overload defination.
         * @return iterator Incremented iterator
        */
        iterator operator++() { ++ptr_; return *this; }
        /**
         * @brief Inequality != method overload.
         * @param other Other iterator to check inequality against
         * @return bool True if end of iteration is reached
        */
        bool operator!=(const iterator & other) const { return ptr_ != other.ptr_; }
        /**
         * @brief Element access overload method.
         * @return T Data at current pointer
        */
        const T operator*() const { return *ptr_; }    
    };
    /// Begin Iterator
    iterator begin() { return iterator(st.begin()); }
    /// End Iterator
    iterator end() { return iterator(st.end()); }
    // ============================================================================================================================
};

/**
 * @class StackLinkedList
 * @brief Stack Template Class, Using Linked List Implementation.
 * @tparam T Type used for Stack
*/
template <typename T> class StackLinkedList : public Stack<T>
{
    SinglyLinkedList<T> st; /// Linked List Memeber
public:
    StackLinkedList() = default;

    /**
     * @brief Expose size of Stack.
     * @return int Number of elements in Stack
    */
    INTEGER size() { return st.size(); }
    /**
     * @brief Checks for emptiness of StackLinkedList.
     * @return bool True if StackLinkedList empty, fals otherwise 
    */
    bool isEmpty() { return st.isEmpty(); }
    /**
     * @brief Push Function to add elements to the StackLinkedList.
     * @param data Element to add to the StackLinkedList
    */
    void push (T data) { st.append(data); }
    /**
     * @brief Pop Function to remove elements from the StackLinkedList.
     * @return T Element to popped from the StackLinkedList
     * @throw exception Stack Underflow
    */
    T pop() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        T data = st.get(st.size() - 1);
        st.removeLast();
        return data;
    }
    /**
     * @brief Provides element at top of the StackLinkedList.
     * @return T Element at top of the Stack
     * @throw exception Stack Underflow
    */
    T top() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        return st.get(st.size() - 1);
    }
    // ========================================================== ITERATOR CLASS ======================================================
    /**
     * @class StackLinkedList::iterator
     * @brief StackLinkedList iterator class.
    */
    class iterator
    {
        INTEGER len_; /// Length of Stack
        typename SinglyLinkedList<T>::iterator ptr_; // Linked List Iterator
    public:
        /**
         * @brief Iterator counstructor.
         * @param ptr Linked List Iterator
         * @param size_ Size of Stack
        */
        iterator(typename SinglyLinkedList<T>::iterator ptr, INTEGER size_): ptr_(ptr), len_(size_) {}
        /**
         * @brief Iterator Increment operator
         * @return iterator Incremented Iterator
        */
        iterator operator++() { ++ptr_; return *this; }
        /**
         * @brief Inequality != method overload.
         * @param other Other iterator to check inequality against
         * @return bool True if end of iteration is reached
         * @throw exception Stack Iterator Invalidation
        */
        bool operator!=(const iterator & other) const {
            if (len_ != other.len_) { throw exception("Stack Iterator Invalidation"); };
            return ptr_ != other.ptr_;
        }
        /**
         * @brief Element access overload method.
         * @return T Data at current pointer
        */
        const T operator*() const { return *ptr_; }
    };
    /// Begin Iterator
    iterator begin() { return iterator(st.begin(), size()); }
    /// End Iterator
    iterator end() { return iterator(st.end(), size()); }
    // ============================================================================================================================
};

} // namespace self
#endif
