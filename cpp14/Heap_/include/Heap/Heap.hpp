// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Heap

#ifndef __self_Heap
#define __self_Heap 1
#pragma once

#include "Utility/Utility.hpp"

namespace self
{

// T must be a copiable type(should support '=' operation)
// T must be a camparable type(should support '<' operation) or,
// please supply comparator class as TEMPLATE ARGUMENT compare_, which does the same.
template <typename T, bool inverse = false, typename compare_ = void>
class Heap
{
    const static INTEGER DEFAULT_CAPACITY = 16;
    template <typename T_, bool inverse_, typename compare__>
    class CompareClass
    {public:
        template<class Q = compare_>
        typename std::enable_if<
            std::is_same<Q, void>::value,
            bool
        >::type
        operator()(T_ a, T_ b) const {
            if (inverse_) {
                return a > b;
            } return a < b;
        }
        // ---
        template<class Q = compare_>
        typename std::enable_if<
            !std::is_same<Q, void>::value,
            bool
        >::type
        operator()(T_ a, T_ b) const {
            compare__ cmp;
            return cmp(a, b);
        }
    };

    INTEGER len, capacity;
    T* hp;
    CompareClass<T, inverse, compare_> campare;   
public:
    Heap() {
        len = 0;
        capacity = DEFAULT_CAPACITY;
        hp = new T[capacity];
    }
    void operator=(std::initializer_list<T> list)
    {
        capacity = list.size() * 2;
        delete [] hp;
        hp = new T[capacity];
        len = list.size();
        std::copy(list.begin(), list.end(), hp);
        
        for (INTEGER i = (len / 2) - 1; i >= 0; --i) {
            heapify(i);
        }
    }
    ~Heap() {
        delete [] hp;
        len = 0;
    }
private:
    void swap_(INTEGER a, INTEGER b) {
        T temp = hp[a];
        hp[a] = hp[b];
        hp[b] = temp;
    }
    static INTEGER getParentIndex(INTEGER curr) { return (curr != 0)? ((curr - 1) / 2) : -1; }
    static INTEGER getLeftIn(INTEGER curr) { return (2 * curr) + 1; }
    static INTEGER getRightIn(INTEGER curr) { return (2 * curr) + 2; }

    T getParent(INTEGER curr) { return hp[getParentIndex(curr)]; }
    T getLeft(INTEGER curr) { return hp[getLeftIn(curr)]; }
    T getRight(INTEGER curr) { return hp[getRightIn(curr)]; }

    bool isHeapInvariant(INTEGER index) {
        return (
            (getParentIndex(index) >= 0)? campare(
                getParent(index),
                hp[index]
            ): true
        ) && (
            (getLeftIn(index) < len)? campare(
                hp[index],
                getLeft(index)
            ): true
        ) && (
            (getRightIn(index) < len)? campare(
                hp[index],
                getRight(index)
            ): true
        );
    }

    void heapify(INTEGER index) {
        INTEGER largest = index;
        INTEGER l = getLeftIn(index), r = getRightIn(index);
        if (l < len && campare(getLeft(index), hp[largest])) {
            largest = l;
        }
        if (r < len && campare(getRight(index), hp[largest])) {
            largest = r;
        }
        if (largest != index) {
            swap_(index, largest);
            heapify(largest);
        }
    }
    INTEGER bubbleUp(INTEGER index) {
        swap_(index, getParentIndex(index));
        return getParentIndex(index);
    }
    INTEGER settleDown(INTEGER index) {
        INTEGER child;
        if (getRightIn(index) < len) {
            child = campare(getRight(index), getLeft(index))? getRightIn(index) : getLeftIn(index);
        } else {
            child = getLeftIn(index);
        }
        swap_(index, child);
        return child;
    }
    void balance(INTEGER index) {
        while (!isHeapInvariant(index)) {
            if (getParentIndex(index) >= 0 && campare(hp[index], getParent(index))) {
                index = bubbleUp(index);
            } else {
                index = settleDown(index);
            }
        }
    }
public:
    bool isEmpty() { return len == 0; }
    INTEGER size() { return len; }
    T top() {
        if (len == 0) {
            throw exception("Heap EMPTY");
        }
        return hp[0];
    }
    INTEGER find(T ele) {
        INTEGER ans = -1;
        for (INTEGER i = 0; i < len; ++i) {
            if (hp[i] == ele) {
                ans = i;
                break;
            }
        } return ans;
    }
    T removeAt(INTEGER index) {
        if (index >= len) {
            throw exception("Invalid Index for removeAt()");
        }
        T ele = hp[index];
        swap_(index, --len);
        balance(index);
        return ele;
    }
    bool remove(T ele) {
        INTEGER index = find(ele);
        if (index == -1) {
            throw exception("self::Heap::remove element not found.");
        } return removeAt(index) == ele;
    }
    T pop() { return removeAt(0); }
    void add(T ele) {
        if (len == capacity) {
            capacity *= 2;
            T* new_arr = new T[capacity];
            std::copy(hp, hp + len, new_arr);
            delete [] hp;
            hp = new T[capacity];
            std::copy(new_arr, new_arr + len, hp);
            delete [] new_arr;
        }
        hp[len] = ele;
        balance(len++);
    }
    bool isHeap(INTEGER index = 0) {
        bool l = (getLeftIn(index) >= 0 && getLeftIn(index) < len)? isHeap(getLeftIn(index)):true;
        bool r = (getRightIn(index) >= 0 && getRightIn(index) < len)? isHeap(getRightIn(index)):true;
        return l && r;
    }
    // ========================================================== ITERATOR CLASS ======================================================
    class iterator
    {
        T *hp_;
    public:
        iterator(T* hp__): hp_(hp__) {}
        iterator operator++() { ++hp_; return *this; }
        bool operator!=(const iterator & other) const { return hp_ != other.hp_; }
        const T operator*() const { return *hp_; }    
    };
    iterator begin() { return iterator(hp); }
    iterator end() { return iterator(hp + size()); }
    // ============================================================================================================================
};

}
#endif
