// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Singly Linked List

#ifndef __self_SinglyLinkedList
#define __self_SinglyLinkedList 1
#pragma once

// #include <string>
#include "Utility/Utility.hpp"

namespace self
{

template <typename T>
class SinglyLinkedList
{
    // ========================================================== NODE CLASS ======================================================
    class Node
    {
        T data;
        Node* next;
    public:
        Node(T elem): data(elem), next(NULL) { ; }
        T getData() { return data; }
        void setData(T elem) { data = elem; }
        friend SinglyLinkedList<T>;
    };
    typedef Node* SLL_Node_ptr;
    // ============================================================================================================================
    INTEGER len;
    SLL_Node_ptr head; SLL_Node_ptr tail;
public:
    SinglyLinkedList(): len(0), head(NULL), tail(NULL) { ; }
    void operator=(std::initializer_list<T> list_) {
        _delete();
        len = 0;
        head = tail = NULL;
        if (list_.size() == 0) { return ; }
        ++len;
        head = tail = new Node(*list_.begin());
        for (typename std::initializer_list<T>::iterator i = list_.begin() + 1; i != list_.end(); ++i, ++len) {
            tail -> next = new Node(*i);
            tail = tail -> next;
        }
    }
    SinglyLinkedList(const SinglyLinkedList&) = delete; // no copy operations
    SinglyLinkedList& operator=(const SinglyLinkedList&) = delete;
    ~SinglyLinkedList() { _delete(); }

    INTEGER size() { return len; }
    bool isEmpty() { return (len == 0); }

    T get(INTEGER index) {
        if (index < 0) { index += size(); }
        if (index < 0 || index >= len) { throw exception("Illegal Index on length: " + std::to_string(len)); }
        SLL_Node_ptr curr = head;
        while (index--) {
            curr = curr -> next;
        } return curr -> getData();
    }
    T at(INTEGER index) { return get(index); }
    T operator[](INTEGER index) { return get(index); }
    void set(T elem, INTEGER index) {
        if (index < 0 || index >= len) { throw exception("Illegal Index on length: " + std::to_string(len)); }
        SLL_Node_ptr curr = head;
        while (index--) {
            curr = curr -> next;
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
        SLL_Node_ptr new_node = new Node(elem);
        while(index--) {
            inFrontOf = inFrontOf -> next;
        }
        new_node -> next = inFrontOf -> next;
        inFrontOf -> next = new_node;
        ++len;
    }
    void add_first(T elem) {
        SLL_Node_ptr new_head = new Node(elem);
        new_head -> next = head;
        head = new_head;
        if (tail == NULL) { tail = head; }
        ++len;
    }
    void append(T elem) {
        ++len;
        if (tail == NULL) {
            head = tail = new Node(elem);
        } else {
            tail -> next = new Node(elem);
            tail = tail -> next;
        }
    }
    INTEGER find(T elem) {
        SLL_Node_ptr curr = head;
        for (INTEGER index = 0; index < len && curr != NULL; ++index, curr = curr -> next) {
            if (curr -> getData() == elem) {
                return index;
            }
        } return -1;
    }
    bool contains(T elem) { return (find(elem) != -1); }
    bool remove(T elem) {
        if (head -> getData() == elem) { return removeFirst(); }// Found at Start
        if (tail -> getData() == elem) { return removeLast(); }// Found at End
        SLL_Node_ptr curr = head;
        SLL_Node_ptr curr_next = NULL;
        while (curr -> getData() != elem && curr != NULL) {
            curr = curr -> next;
        }
        if (curr == NULL) { return false; } // Not Found
        curr_next = curr -> next;
        curr -> setData(curr_next -> getData());
        curr -> next = curr_next -> next;
        curr_next -> next = NULL;
        if (curr_next == tail) { tail = curr; }
        delete curr_next;
        --len;
        return true;
    }
    bool removeLast() {
        if (tail == NULL) { return false; }
        if (head == tail) {
            SLL_Node_ptr curr = head;
            head = tail = NULL;
            len = 0;
            delete curr;
            return true;
        }
        SLL_Node_ptr curr = head;
        while (curr -> next != tail) {
            curr = curr -> next;
        }
        tail = curr;
        tail -> next = NULL;
        delete curr -> next;
        --len;
        return true;
    }
    bool removeFirst() {
        if (head == NULL) { return false; }
        if (head == tail) {
            SLL_Node_ptr curr = head;
            head = tail = NULL;
            len = 0;
            delete curr;
            return true;
        }
        SLL_Node_ptr curr = head;
        head = head -> next;
        delete curr;
        --len;
        return true;
    }
    void _delete() {
        bool attempt = false;
        while(len > 0) {
            attempt = removeLast();
            if (!attempt) { throw exception("Linked List integrity on destruction failed"); }
        }
    }
    void operator delete(void* this_) { SinglyLinkedList<T>(this_)._delete(); }
    // ========================================================== ITERATOR CLASS ======================================================
    class iterator
    {
        SLL_Node_ptr ptr_;
    public:
        iterator(SLL_Node_ptr ptr): ptr_(ptr) {}
        iterator operator++() { ptr_ = ptr_ -> next; return *this; }
        bool operator!=(const iterator & other) const { return ptr_ != other.ptr_; }
        const T operator*() const { return ptr_ -> getData(); }    
        };
        iterator begin() { return iterator(head); }
        iterator end() { return iterator(tail); }
    // ============================================================================================================================
};

}
#endif
