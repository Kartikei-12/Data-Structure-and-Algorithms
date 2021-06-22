// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Implementation of Queue

#pragma once
#ifndef __self_Queue
#define __self_Queue 1

#include "DynamicArray/DynamicArray.hpp"
#include "SinglyLinkedList/SinglyLinkedList.hpp"
#include "Utility/Utility.hpp"

namespace self
{

template <typename T> class Queue
{public:
    Queue() {;}
    virtual INTEGER size() = 0;
    virtual bool isEmpty() = 0;
    virtual void push(T data) = 0;
    virtual T pop() = 0;
    virtual T top() = 0;
};

template <typename T>
class QueueArray : public Queue<T>
{
    const static INTEGER DEFAULT_CAPACITY = 8;
    INTEGER front; // Place to remove element from
    INTEGER back; // Place of NEXT element
    INTEGER len, capacity;
    T* st;
public:
    QueueArray():
        front(0), back(0), len(0),
        capacity(DEFAULT_CAPACITY), st(new T[DEFAULT_CAPACITY]) { ; }
    ~QueueArray() {
        len = back = front = 0;
        delete [] st;
    }

    INTEGER size() { return len; }
    bool isEmpty() { return (len == 0); }
    void push (T data) { 
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
    T pop() {
        if (len == 0) { throw exception("Queue Underflow."); }
        --len;
        T data = st[front];
        front = (front + 1) % capacity;
        return data;
    }
    T top() {
        if (len == 0) { throw exception("Queue Underflow."); }
        return st[front];
    }
    // ========================================================== ITERATOR CLASS ======================================================
    class iterator
    {
        bool traversed;
        T *ptr;
        T *begin_;
        T *end_;
    public:
        iterator(
            T *ptr_,
            T *b = NULL,
            T *e = NULL,
            INTEGER len_ = 0
        ): ptr(ptr_), begin_(b), end_(e) { traversed = (len_ != 0); }
        iterator operator++() {
            if (ptr == end_ - 1) {
                ptr = begin_;
            } else {
                ++ptr;
            } return *this;
        }
        bool operator!=(const iterator &other) {
            if (traversed) {
                traversed = false; return true;
            } return ptr != other.ptr;
        }
        const T operator*() const { return *ptr; }
    };
    iterator begin() { return iterator(st + front, st, st + capacity, len); }
    iterator end() { return iterator(st + back); }
    // ============================================================================================================================
};

template <typename T>
class QueueLinkedList : public Queue<T>
{
    SinglyLinkedList<T> st;
public:
    QueueLinkedList() {;}
    ~QueueLinkedList() { ; }

    INTEGER size() { return st.size(); }
    bool isEmpty() { return st.isEmpty(); }
    void push (T data) { st.append(data); }
    T pop() {
        if (st.isEmpty()) { throw exception("Queue Underflow."); }
        T data = st.get(0);
        st.removeFirst();
        return data;
    }
    T top() {
        if (st.isEmpty()) { throw exception("Queue Underflow."); }
        return st.get(0);
    }
    // ========================================================== ITERATOR CLASS ======================================================
    class iterator
    {
        typename SinglyLinkedList<T>::iterator ptr;
    public:
        iterator(typename SinglyLinkedList<T>::iterator ptr): ptr(ptr) {}
        iterator operator++() { ++ptr; return *this; }
        bool operator!=(const iterator &other) const { return ptr != other.ptr; }
        const T operator*() const { return *ptr; }
    };
    iterator begin() { return iterator(st.begin()); }
    iterator end() { return iterator(st.end()); }
    // ============================================================================================================================
};

}
#endif
