// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Stack

#ifndef __self_Stack
#define __self_Stack 1
#pragma once

#include "DynamicArray/DynamicArray.hpp"
#include "SinglyLinkedList/SinglyLinkedList.hpp"
#include "Utility/Utility.hpp"

namespace self
{

template <typename T>
class Stack
{
public:
    Stack() {;}
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    virtual INTEGER size() = 0;
    virtual bool isEmpty() = 0;
    virtual void push(T data) = 0;
    virtual T pop() = 0;
    virtual T top() = 0;
};

template <typename T>
class StackArray : public Stack<T>
{
    DynamicArray<T> st;
public:
    StackArray() { ; }
    ~StackArray() { ; }

    INTEGER size() { return st.size(); }
    bool isEmpty() { return st.isEmpty(); }
    void push (T data) { st.append(data); }

    T pop() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        T data = st.get(size() - 1);
        st.removeAt(size() - 1);
        return data;
    }
    T top() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        return st.get(size() - 1);
    }
    // ========================================================== ITERATOR CLASS ======================================================
    class iterator
    {
        typename DynamicArray<T>::iterator ptr_;
    public:
        iterator(typename DynamicArray<T>::iterator ptr): ptr_(ptr) {}
        iterator operator++() { ++ptr_; return *this; }
        bool operator!=(const iterator & other) const { return ptr_ != other.ptr_; }
        const T operator*() const { return *ptr_; }    
        };
    iterator begin() { return iterator(st.begin()); }
    iterator end() { return iterator(st.end()); }
    // ============================================================================================================================
};

template <typename T>
class StackLinkedList : public Stack<T>
{
    SinglyLinkedList<T> st;
public:
    StackLinkedList() { ; }
    ~StackLinkedList() { ; }

    INTEGER size() { return st.size(); }
    bool isEmpty() { return st.isEmpty(); }
    void push (T data) { st.append(data); }
    T pop() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        T data = st.get(st.size() - 1);
        st.removeLast();
        return data;
    }
    T top() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        return st.get(st.size() - 1);
    }
    // ========================================================== ITERATOR CLASS ======================================================
    class iterator
    {
        typename SinglyLinkedList<T>::iterator ptr_;
    public:
        iterator(typename SinglyLinkedList<T>::iterator ptr): ptr_(ptr) {}
        iterator operator++() { ++ptr_; return *this; }
        bool operator!=(const iterator & other) const { return ptr_ != other.ptr_; }
        const T operator*() const { return *ptr_; }    
        };
    iterator begin() { return iterator(st.begin()); }
    iterator end() { return iterator(st.end()); }
    // ============================================================================================================================
};

}
#endif
