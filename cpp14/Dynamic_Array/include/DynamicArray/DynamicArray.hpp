// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Dynamic Array

#ifndef __self_DynamicArray
#define __self_DynamicArray
#pragma once

#include <string>
#include "Utility_/Utility_.hpp"

namespace
{
const self::INTEGER DEFAULT_CAPACITY = 8;
}

namespace self
{

template <typename T>
class DynamicArray
{
    INTEGER len, capacity;
    T* arr;
public:
    DynamicArray(INTEGER cap = DEFAULT_CAPACITY): capacity(cap), len(0) {
        if (cap <= 0) { throw exception("Illegal Capacity: " + std::to_string(cap));  }
        arr = new T[cap];
    }
    DynamicArray(const std::initializer_list<T> &list): capacity(DEFAULT_CAPACITY) {
        if (list.size() > capacity) {
            capacity = list.size() * 2;
        }
        arr = new T[capacity];
        len = list.size();
        std::copy(list.begin(), list.end(), arr);
    }

    void increaseCapacity(INTEGER margin = -1) {
        if (margin == -1) { margin = capacity; }
        capacity += margin;
        T* arr_new = new T[capacity];
        std::copy(arr, arr + len, arr_new); // OLD_FIRST, OLD_LAST, NEW
        delete[] arr;
        arr = new T[capacity];
        std::copy(arr_new, arr_new + len, arr);
        delete[] arr_new;
    }

    INTEGER size() { return len; }
    bool isEmpty() { return (len == 0); }

    T get(INTEGER index) {
        if (index < 0) { index += size(); }
        if (index < 0 || index >= len) { throw exception("Illegal Index on length: " + std::to_string(len)); }
        return arr[index];
    }
    T operator[](INTEGER index) { return get(index); }
    void set(T elem, INTEGER index) {
        if (index < 0 || index >= len) { throw exception("Illegal Index on length: " + std::to_string(len)); }
        arr[index] = elem;
    }
    void add(T elem, INTEGER index) {
        if (index == -1) { index = len; }
        if (index < 0 || index > len) { throw exception("Illegal Index for insertion on length: " + std::to_string(len)); }
        if (len == capacity) { increaseCapacity(); }
        std::copy(arr + index, arr + len, arr + index + 1); // SHIFTING from arr[index, len) to arr[index + 1, len + 1)
        arr[index] = elem;
        ++len;
    }
    void append(T elem) { add(elem, -1); }
    
    INTEGER find(T elem) {
        for (INTEGER i = 0; i < len; ++i) {
            if (arr[i] == elem) {
                return i;
            }
        } return -  1;
    }
    bool contains(T elem) { return find(elem) != -1; }
    bool remove(T elem) {
        INTEGER index = find(elem);
        if (index == -1) {
            return false;
        }
        removeAt(index);
        return true;
    }
    T removeAt(INTEGER index) {
        if (index < 0 || index >= len) { throw exception("Illegal Index for deletion on length: " + std::to_string(len)); }
        T elem = arr[index];
        std::copy(arr + index + 1, arr + len, arr + index);
        --len;
        return elem;
    }
    void _delete() {
        len = 0;
        delete[] arr;
        arr = new T[DEFAULT_CAPACITY];
    }
    void operator delete(void* this_) { DynamicArray<T>(this_)._delete(); }
    // ========================================================== ITERATOR CLASS ======================================================
    class iterator
    {
        T *arr_;
    public:
        iterator(T* arr__): arr_(arr__) {}
        iterator operator++() { ++arr_; return *this; }
        bool operator!=(const iterator & other) const { return arr_ != other.arr_; }
        const T operator*() const { return *arr_; }    
    };
    iterator begin() { return iterator(arr); }
    iterator end() { return iterator(arr + len); }
    // ============================================================================================================================
};

}
#endif
