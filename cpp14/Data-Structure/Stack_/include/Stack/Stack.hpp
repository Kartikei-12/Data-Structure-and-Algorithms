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
namespace self {

template <typename T, Imple_Type impl_type>
class Stack {
    using Object = std::conditional_t<
            impl_type == Array, DynamicArray<T>,
          std::conditional_t<
            impl_type == LinkedList, SinglyLinkedList<T>,
    void>>;
    Object st;
    template<Imple_Type Q = impl_type>
    ENABLE_IF(Q == Array, void) pop_() { st.removeAt(size() - 1); }
    template<Imple_Type Q = impl_type>
    ENABLE_IF(Q == LinkedList, void) pop_() { st.removeLast(); }

 public:
    Stack() = default;
    INTEGER size() { return this -> st.size(); }
    bool isEmpty() { return this -> st.isEmpty(); }
    void push(T data) { st.append(data); }
    T top() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        return st.get(st.size() - 1);
    }
    T pop() {
        if (st.isEmpty()) { throw exception("Stack Underflow."); }
        T data = st.get(st.size() - 1);
        pop_(); return data;
    }
    // ============================ ITERATOR CLASS ========================
    class iterator {
        typename Object::iterator ptr_;  /// Object Iterator

     public:
        explicit iterator(typename Object::iterator ptr): ptr_(ptr) {}
        iterator operator++() { ++ptr_; return *this; }
        bool operator!=(const iterator& other) const {
            return ptr_ != other.ptr_; }
        const T operator*() const { return *ptr_; }
    };
    iterator begin() { return iterator(st.begin()); }
    iterator end() { return iterator(st.end()); }
    // ====================================================================
};

}  // namespace self
#endif
