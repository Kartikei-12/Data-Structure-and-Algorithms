/**
 * @headerfile DynamicArray.hpp
 * @brief Dynamic Array.
 * @author Kartikei Mittal
*/

#pragma once
#ifndef __self_DynamicArray
#define __self_DynamicArray

#include <string>
#include "Utility/Utility.hpp"

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self
{

/**
 * @class DynamicArray
 * @brief Dynamic Array Template Class.
 * @tparam T Type used for Dynamic Array
*/
template <typename T>
class DynamicArray
{
    const static INTEGER DEFAULT_CAPACITY = 8; /// Default capacity of the array
    INTEGER len, capacity; /// Length and Capacity of the Dynamic Array
    T* arr; /// Dynamic Array
public:
    /**
     * @brief Dynamic Array Default Counstructor.
     * @param cap Capacity of array
     * @throw exception If 0 or negative capacity is supplied
    */
    DynamicArray(INTEGER cap = DEFAULT_CAPACITY): capacity(cap), len(0) {
        if (cap <= 0) { throw exception("Illegal Capacity: " + std::to_string(cap));  }
        arr = new T[cap];
    }
    /**
     * @brief Overload assignment operator.
     * @param list Brace enclosed list
    */
    void operator=(const std::initializer_list<T> &list) {
        delete [] arr;
        capacity = list.size() * 2;
        arr = new T[capacity];
        len = list.size();
        std::copy(list.begin(), list.end(), arr);
    }
    /// Destructor
    ~DynamicArray() { 
        len = 0;
        delete [] arr;
    }

    /**
     * @brief Method to increase capacity of the array.
     * @param margin Margin to increase capacity by
    */
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

    /**
     * @brief Expose size of array.
     * @return int Number of elements in array
    */
    INTEGER size() { return len; }
    /**
     * @brief Checks for emptiness of array.
     * @return bool True if array empty, fals otherwise 
    */
    bool isEmpty() { return (len == 0); }

    /**
     * @brief Getter Method for array.
     * @param index Index of Element to access
     * @return T Element at given index
     * @throw exception If an invalid exception is recieved
    */
    T& get(INTEGER index) {
        if (index < 0) { index += size(); }
        if (index < 0 || index >= len) { throw exception("Illegal Index on length: " + std::to_string(len)); }
        return arr[index];
    }
    /**
     * @brief Route Getter Method for [] opewrator overload.
     * @param index Index of Element to access
     * @return T Element at given index
     * @throw exception If an invalid index is recieved
    */
    T& operator[](INTEGER index) { return get(index); }
    /**
     * @brief Setter Method.
     * @param elem New element
     * @param index Index of Element to set
     * @throw exception If an invalid index is recieved
    */
    void set(T elem, INTEGER index) {
        if (index < 0 || index >= len) { throw exception("Illegal Index on length: " + std::to_string(len)); }
        arr[index] = elem;
    }
    /**
     * @brief Add method for Dynamic Array.
     * @param elem Element to add
     * @param index Place to add new element
     * @throw exception If an invalid index is recieved
    */
    void add(T elem, INTEGER index) {
        if (index == -1) { index = len; }
        if (index < 0 || index > len) { throw exception("Illegal Index for insertion on length: " + std::to_string(len)); }
        if (len == capacity) { increaseCapacity(); }
        std::copy(arr + index, arr + len, arr + index + 1); // SHIFTING from arr[index, len) to arr[index + 1, len + 1)
        arr[index] = elem;
        ++len;
    }
    /**
     * @brief Apend method for Dynamic Array.
     * @param elem Element to add
    */
    void append(T elem) { add(elem, -1); }
    /**
     * @brief Find function for Dynamic Array.
     * @param elem Element to search for
     * @return int Element index if found, -1 otherwise
    */
    INTEGER find(T elem) {
        for (INTEGER i = 0; i < len; ++i) {
            if (arr[i] == elem) {
                return i;
            }
        } return -  1;
    }
    /**
     * @brief Check for presence of given element.
     * @param elem Element to look for
     * @return bool True if element present
    */
    bool contains(T elem) { return find(elem) != -1; }
    /**
     * @brief Element removal function.
     * @param elem Element to remove
     * @return bool If successfull removal 
    */
    bool remove(T elem) {
        INTEGER index = find(elem);
        if (index == -1) {
            return false;
        }
        removeAt(index);
        return true;
    }
    /**
     * @brief Remove element at given index.
     * @param index Index to remove element from
     * @return T Removed element
     * @throw exception If an invalid index is recieved
    */
    T removeAt(INTEGER index) {
        if (index < 0 || index >= len) { throw exception("Illegal Index for deletion on length: " + std::to_string(len)); }
        T elem = arr[index];
        std::copy(arr + index + 1, arr + len, arr + index);
        --len;
        return elem;
    }
    // ========================================================== ITERATOR CLASS ======================================================
    /**
     * @class DynamicArray::iterator
     * @brief Dynamic Array iterator class.
    */
    class iterator
    {
        T *arr_; T *end; /// Array and End Pointer
    public:
        /**
         * @brief Iterator Counstructor
         * @param arr__ Array Pointer
         * @param end_ Iterator to end
        */
        iterator(T* arr__, T* end_ = nullptr): arr_(arr__), end(end_) { ; }
        /**
         * @brief Iterator increment overload defination.
         * @return iterator Incremented iterator
        */
        iterator operator++() { ++arr_; return *this; }
        /**
         * @brief Inequality != method overload.
         * @param other Other iterator to check inequality against
         * @return bool True if end of iteration is reached
         * @throw exception Iterator Invalidation exception
        */
        bool operator!=(const iterator & other) const {
            if (end != other.arr_) { throw exception("Iterator Invalidation."); }
            return arr_ != other.arr_; 
        }
        /**
         * @brief Element access overload method.
         * @return T Data at current pointer
        */
        const T operator*() const { return *arr_; }
    };
    /// Begin Iterator
    iterator begin() { return iterator(arr, arr + len); }
    /// End Iterator
    iterator end() { return iterator(arr + len); }
    // ============================================================================================================================
};

}
#endif
