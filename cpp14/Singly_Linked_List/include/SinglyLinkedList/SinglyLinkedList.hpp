// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Singly Linked List

#pragma once
#ifndef __self_SinglyLinkedList
#define __self_SinglyLinkedList 1

#include "Utility/Utility.hpp"
#include "NodeOneChild/NodeOneChild.hpp"

namespace self
{

template <typename T>
class SinglyLinkedList
{
    typedef NodeOneChild<T>* SLL_Node_ptr;
    INTEGER len;
    SLL_Node_ptr head; SLL_Node_ptr tail;
public:
    SinglyLinkedList(): len(0), head(nullptr), tail(nullptr) { ; }
    void operator=(std::initializer_list<T> list_) {
        _clear();
        len = 0;
        if (list_.size() == 0) { return ; }
        ++len;
        head = tail = new NodeOneChild<T>(*list_.begin());
        for (typename std::initializer_list<T>::iterator i = list_.begin() + 1; i != list_.end(); ++i, ++len) {
            tail -> setNext(new NodeOneChild<T>(*i));
            tail = tail -> getNext();
        }
    }
    SinglyLinkedList(const SinglyLinkedList&) = delete; // no copy operations
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
    ~SinglyLinkedList() { _clear(); }
    void _clear() {
        bool attempt = false;
        while(len > 0) {
            attempt = removeLast();
            if (!attempt) { throw exception("Linked List integrity on destruction failed"); }
        }
    }

    INTEGER size() { return len; }
    bool isEmpty() { return (len == 0); }

    T get(INTEGER index) {
        if (index < 0) { index += size(); }
        if (index < 0 || index >= len) { throw exception("Illegal Index on length: " + std::to_string(len)); }
        SLL_Node_ptr curr = head;
        while (index--) {
            curr = curr -> getNext();
        }
        return curr -> getData();
    }
    T operator[](INTEGER index) { return get(index); }
    void set(T elem, INTEGER index) {
        if (index < 0 || index >= len) { throw exception("Illegal Index on length: " + std::to_string(len)); }
        SLL_Node_ptr curr = head;
        while (index--) {
            curr = curr -> getNext();
        }
        curr -> setData(elem);
    }
    void add(T elem, INTEGER index) {
        if (index < 0 || index >= len) { throw exception("Illegal Index for insertion on length: " + std::to_string(len)); }
        if (index == 0) {
            add_first(elem);
            return ;
        }
        --index;
        SLL_Node_ptr inFrontOf = head;
        SLL_Node_ptr new_node = new NodeOneChild<T>(elem);
        while(index--) {
            inFrontOf = inFrontOf -> getNext();
        }
        new_node -> setNext(inFrontOf -> getNext());
        inFrontOf -> setNext(new_node);
        ++len;
    }
    void add_first(T elem) {
        SLL_Node_ptr new_head = new NodeOneChild<T>(elem);
        new_head -> setNext(head);
        head = new_head;
        if (tail == nullptr) { tail = head; }
        ++len;
    }
    void append(T elem) {
        ++len;
        if (tail == nullptr) {
            head = tail = new NodeOneChild<T>(elem);
        } else {
            tail -> setNext(new NodeOneChild<T>(elem));
            tail = tail -> getNext();
        }
    }
    INTEGER find(T elem) {
        SLL_Node_ptr curr = head;
        for (INTEGER index = 0; index < len && curr != nullptr; ++index, curr = curr -> getNext()) {
            if (curr -> getData() == elem) {
                return index;
            }
        } return -1;
    }
    bool contains(T elem) { return (find(elem) != -1); }
    bool remove(T elem) {
        if (head -> getData() == elem) { return removeFirst(); } // Found at Start
        if (tail -> getData() == elem) { return removeLast(); } // Found at End
        SLL_Node_ptr curr = head;
        SLL_Node_ptr curr_next = nullptr;
        while (curr -> getData() != elem && curr != nullptr) {
            curr = curr -> getNext();
        }
        if (curr == nullptr) { return false; } // Not Found
        curr_next = curr -> getNext();
        curr -> setData(curr_next -> getData());
        curr -> setNext(curr_next -> getNext());
        curr_next -> setNext(nullptr);
        if (curr_next == tail) { tail = curr; }
        delete curr_next;
        --len;
        return true;
    }
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
    // ========================================================== ITERATOR CLASS ======================================================
    class iterator
    {
        SLL_Node_ptr ptr_; SLL_Node_ptr end;
    public:
        iterator(SLL_Node_ptr ptr, SLL_Node_ptr end_ = NULL): ptr_(ptr), end(end_) { ; }
        iterator operator++() { ptr_ = ptr_ -> getNext(); return *this; }
        bool operator!=(const iterator & other) const {
            if (end != other.ptr_) { throw exception("Iterator Invalidation."); }
            return ptr_ != other.ptr_;
        }
        const T operator*() const { return ptr_ -> getData(); }    
        };
        iterator begin() { return iterator(head, tail); }
        iterator end() { return iterator(tail); }
    // ============================================================================================================================
};

}
#endif
