/**
 * @headerfile Heap.hpp
 * @brief Heap.
 * @author Kartikei Mittal
*/

#pragma once
#ifndef __self_Heap
#define __self_Heap 1

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
 * @note
 * T must be a copiable type(should support '=' operation)
 * T must be a camparable type(should support '<' operation) or,
 * Supply comparator class as TEMPLATE ARGUMENT compare_, which does the same.
 * @tparam T Type used for Heap
 * @tparam inverse True for MaxHeap, false for MinHeap
 * @tparam compare_ Compare class to be used instead of defallt less than operator
*/
template <typename T, bool inverse = false, typename compare_ = void>
class Heap
{
    const static INTEGER DEFAULT_CAPACITY = 16; /// Default capacity of the Heap
    
    /**
     * @brief Comparator class enabled if comparator class NOT supplied.
     * @tparam Q Used to route Compare Class.
     * @param a First Element
     * @param b Second Element
     * @return int Comparasion value
     * @retval 0 If a is equal to b
     * @retval 1 If a is less than b
     * @retval -1 If a is greater than b
    */
    template<typename Q = compare_>
    ENABLE_IF(IS_SAME(Q, void), INTEGER)
    campare(T a, T b) const {
        if (a == b) { return 0; }
        if (inverse) {
            return (a < b)? -1 : 1;
        }
        return (a < b)? 1 : -1;
    }
    /**
     * @brief Comparator class enabled if comparator class supplied.
     * @tparam Q Used to route comprator_.
     * @param a First Element
     * @param b Second Element
     * @return int Comparasion value
     * @retval 0 If a is equal to b
     * @retval 1 If a is less than b
     * @retval -1 If a is greater than b
    */
    template<typename Q = compare_>
    ENABLE_IF(!IS_SAME(Q, void), INTEGER)
    campare(T a, T b) const {
        compare_ cmp;
        return cmp(a, b);
    }

    INTEGER len, capacity; /// Length and Capacity of the Dynamic Array
    T* hp; /// Heap
public:
    /**
     * @brief Heap Default Counstructor.
    */
    Heap(): len(0), capacity(DEFAULT_CAPACITY), hp(new T[capacity]) { ; }
    /**
     * @brief Overload assignment operator.
     * @param list Brace enclosed list
    */
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
    /// Destructor
    ~Heap() { delete [] hp; len = 0; }
private:
    /**
     * @brief Element Swap method.
     * @param a Index of first element
     * @param b Index of the second element
    */
    void swap_(INTEGER a, INTEGER b) {
        T temp = hp[a];
        hp[a] = hp[b];
        hp[b] = temp;
    }
    /**
     * @brief Static Method to get paraent index.
     * @param curr Index of member
     * @return int Returns paraent index
     * @retval -1 If no paraent
     * @retval (curr-1)/2 If paraent 
    */
    static INTEGER getParentIndex(INTEGER curr) { return (curr != 0)? ((curr - 1) / 2) : -1; }
    /**
     * @brief Static Method to get Left Child index.
     * @param curr Index of member
     * @return int Returns Left Child Index
     * @retval (2*curr)+1 Left Child Index 
    */
    static INTEGER getLeftIn(INTEGER curr) { return (2 * curr) + 1; }
    /**
     * @brief Static Method to get Right Child index.
     * @param curr Index of member
     * @return int Returns Right Child Index
     * @retval (2*curr)+2 Right Child Index 
    */
    static INTEGER getRightIn(INTEGER curr) { return (2 * curr) + 2; }

    /**
     * @brief Method to get Paraent.
     * @param curr Index of member
     * @return T Returns Paraent 
    */
    T getParent(INTEGER curr) { return hp[getParentIndex(curr)]; }
    /**
     * @brief Method to get Left Child.
     * @param curr Index of member
     * @return T Returns Left Child
    */
    T getLeft(INTEGER curr) { return hp[getLeftIn(curr)]; }
    /**
     * @brief Method to get Right Child.
     * @param curr Index of member
     * @return T Returns Right Child
    */
    T getRight(INTEGER curr) { return hp[getRightIn(curr)]; }

    /**
     * @brief Check Heap Invariant for the supplied index.
     * @param int Index to check invariant
     * @return bool True if Heap Invariant is satisfied
    */
    bool isHeapInvariant(INTEGER index) {
        bool   par = (getParentIndex(index) >= 0  )? (campare(getParent(index), hp[index]      ) >= 0): true;
        bool  left = (     getLeftIn(index) <  len)? (campare(hp[index]       , getLeft(index) ) >= 0): true;
        bool right = (    getRightIn(index) <  len)? (campare(hp[index]       , getRight(index)) >= 0): true;
        return par && left && right;
    }
    /**
     * @brief Heapify supplied index.
     * @param index Index to heapify
    */
    void heapify(INTEGER index) {
        INTEGER largest = index;
        INTEGER l = getLeftIn(index), r = getRightIn(index);
        if (l < len && campare(getLeft(index), hp[largest]) >= 0) {
            largest = l;
        }
        if (r < len && campare(getRight(index), hp[largest]) >= 0) {
            largest = r;
        }
        if (largest != index) {
            swap_(index, largest);
            heapify(largest);
        }
    }
    /**
     * @brief Method to raise current element to paraent.
     * @param index Index to raise
     * @return int New Index of element
    */
    INTEGER bubbleUp(INTEGER index) {
        swap_(index, getParentIndex(index));
        return getParentIndex(index);
    }
    /**
     * @brief Method to swap current element with it's child.
     * @param index Index to swap
     * @return int New Index of element
    */
    INTEGER settleDown(INTEGER index) {
        INTEGER child;
        if (getRightIn(index) < len) {
            child = (campare(getRight(index), getLeft(index))>= 0)? getRightIn(index) : getLeftIn(index);
        } else {
            child = getLeftIn(index);
        }
        swap_(index, child);
        return child;
    }
    /**
     * @brief Method to relocate element to proper place in the heap
     * @param index Index of element to balance
    */
    void balance(INTEGER index) {
        while (!isHeapInvariant(index)) {
            if (getParentIndex(index) >= 0 && campare(hp[index], getParent(index)) >= 0) {
                index = bubbleUp(index);
            } else {
                index = settleDown(index);
            }
        }
    }
public:
    /**
     * @brief Checks for emptiness of Heap.
     * @return bool True if array empty, fals otherwise 
    */
    bool isEmpty() { return len == 0; }
    /**
     * @brief Expose size of heap.
     * @return int Number of elements in heap
    */
    INTEGER size() { return len; }
    /**
     * @brief Expose element at top of heap.
     * @return T Element at top of the heap
    */
    T top() {
        if (len == 0) { throw exception("Heap EMPTY"); }
        return hp[0];
    }
    /**
     * @brief Find function for heap.
     * @param ele Element to search for
     * @return int Element index if found, -1 otherwise
    */
    INTEGER find(T ele) {
        INTEGER ans = -1;
        for (INTEGER i = 0; i < len; ++i) {
            if (hp[i] == ele) {
                ans = i;
                break;
            }
        } return ans;
    }
    /**
     * @brief Remove element at given index.
     * @param index Index to remove element from
     * @return T Removed element
     * @throw exception If an invalid index is recieved
    */
    T removeAt(INTEGER index) {
        if (index >= len) {
            throw exception("Invalid Index for removeAt()");
        }
        T ele = hp[index];
        swap_(index, --len);
        balance(index);
        return ele;
    }
    /**
     * @brief Element removal function.
     * @param ele Element to remove
     * @return bool If successfull removal 
    */
    bool remove(T ele) {
        INTEGER index = find(ele);
        if (index == -1) {
            throw exception("self::Heap::remove element not found.");
        } return removeAt(index) == ele;
    }
    /**
     * @brief Expose element at top of heap and remove it.
     * @return T Element at top of the heap
    */
    T pop() { return removeAt(0); }
    /**
     * @brief Add method for Heap.
     * @param ele Element to add
    */
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
    /**
     * @brief Method to check wheather heap(this) satisfy Heap Invariant
     * @return bool True Heap Invariant satisfied
    */
    bool isHeap(INTEGER index = 0) {
        bool l = (getLeftIn(index) >= 0 && getLeftIn(index) < len)? isHeap(getLeftIn(index)):true;
        bool r = (getRightIn(index) >= 0 && getRightIn(index) < len)? isHeap(getRightIn(index)):true;
        return l && r;
    }
    // ========================================================== ITERATOR CLASS ======================================================
    /**
     * @class Heap::iterator
     * @brief Heap iterator class.
    */
    class iterator
    {
        T *hp_; T *end; /// Current and End Pointer
    public:
        /**
         * @brief Iterator Counstructor
         * @param hp__ Heap Pointer
         * @param end_ Iterator to end
        */
        iterator(T* hp__, T* end_ = nullptr): hp_(hp__), end(end_) {}
        /**
         * @brief Iterator increment overload defination.
         * @return iterator Incremented iterator
        */
        iterator operator++() { ++hp_; return *this; }
        /**
         * @brief Inequality != method overload.
         * @param other Other iterator to check inequality against
         * @return bool True if end of iteration is reached
         * @throw exception Iterator Invalidation exception
        */
        bool operator!=(const iterator & other) const {
            if (end != other.hp_) { throw exception("Iterator Invalidation."); }
            return hp_ != other.hp_;
        }
        /**
         * @brief Element access overload method.
         * @return T Data at current pointer
        */
        const T operator*() const { return *hp_; }    
    };
    /// Begin Iterator
    iterator begin() { return iterator(hp, hp + size()); }
    /// End Iterator
    iterator end() { return iterator(hp + size()); }
    // ============================================================================================================================
};

}
#endif
