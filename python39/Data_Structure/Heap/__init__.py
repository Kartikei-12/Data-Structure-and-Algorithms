"""@author: Kartikei Mittal
@email: kartikeimittal@gmail.com
Heap"""

__author__ = "Kartikei Mittal"

import copy
import types

class Heap:
    """Heap Class
    Args:
        inverse (bool): True -> Max Heap, False -> Min Heap
        compare_ (types.FunctionType): Coustom function to use for comparasion"""
    def __init__(self, inverse = False, compare_ = None):
        """"""
        if compare_ is not None:
            if not isinstance(compare_, types.FunctionType):
                raise TypeError("compare_ Must be callable function if not None")
            self.compare = compare_
        else:
            # a == b ->  0 , # a < b  -> -1 , # a > b  ->  1
            if inverse:
                self.compare = lambda a, b: 0 if a == b else -1 if a < b else 1
            else:
                self.compare = lambda a, b: 0 if a == b else 1 if a < b else -1
        self.len_ = 0
        self.hp_ = list()
        self.getParentIdx = lambda curr: int((curr - 1) / 2)
        self.getLeftIdx  = lambda curr: (curr * 2) + 1
        self.getRightIdx = lambda curr: (curr * 2) + 2

    def __iadd__(self, attachment):
        """"""
        self.len_ += len(attachment)
        self.hp_.extend(attachment)
        for i in range(int(self.len_ / 2), -1, -1):
            self.heapify(i)
        return self
    def swap_(self, a, b):
        """"""
        self.hp_[a], self.hp_[b] = self.hp_[b], self.hp_[a]
    def getParent(self, curr):
        """"""
        return self.hp_[self.getParentIdx(curr)]
    def getLeft(self, curr):
        """"""
        return self.hp_[self.getLeftIdx(curr)]
    def getRight(self, curr):
        """"""
        return self.hp_[self.getRightIdx(curr)]
    def isHeapInvariant(self, idx):
        """"""
        parent = self.compare(self.getParent(idx), self.hp_[idx]) >= 0 \
            if self.getParentIdx(idx) >= 0 else True
        left  = self.compare(self.hp_[idx],  self.getLeft(idx)) >= 0 \
            if self.getLeftIdx(idx) < self.len_ else True
        right = self.compare(self.hp_[idx], self.getRight(idx)) >= 0 \
            if self.getRightIdx(idx) < self.len_ else True
        return parent and left and right
    def heapify(self, idx):
        """"""
        largest = idx
        l = self.getLeftIdx(idx)
        r = self.getRightIdx(idx)
        if l < self.len_ and self.compare(self.getLeft(idx), self.hp_[largest]) >= 0:
            largest = l
        if r < self.len_ and self.compare(self.getRight(idx), self.hp_[largest]) >= 0:
            largest = r
        if largest != idx:
            self.swap_(idx, largest)
            self.heapify(largest)
    def bubbleUp(self, idx):
        """"""
        self.swap_(idx, self.getParentIdx(idx))
        return self.getParentIdx(idx)
    def settleDown(self, idx):
        """"""
        if self.getRightIdx(idx) < self.len_:
            child = self.getRightIdx(idx) \
                if self.compare(self.getRight(idx), self.getLeft(idx)) >= 0 \
                else self.getLeftIdx(idx)
        else:
            child = self.getLeftIdx(idx)
        self.swap_(idx, child)
        return child
    def balance(self, idx):
        """"""
        while not self.isHeapInvariant(idx):
            idx = self.bubbleUp(idx) \
                if self.getParentIdx(idx) >= 0 and \
                   self.compare(self.hp_[idx], self.getParent(idx)) >= 0 \
                else self.settleDown(idx)
    def isEmpty(self):
        """"""
        return self.len_ == 0
    def __len__(self):
        """"""
        return self.len_
    def top(self):
        """"""
        if self.len_ == 0:
            raise ValueError("HEAP Empty")
        return self.hp_[0]
    def find(self, element):
        """"""
        ans = -1
        for i, ele in enumerate(self.hp_):
            if ele == element:
                ans = i
                break
        return ans
    def removeAt(self, idx):
        """"""
        if idx >= self.len_:
            raise ValueError("Invalid index for removeAt")
        element = self.hp_[idx]
        self.len_ -= 1
        self.swap_(idx, self.len_)
        self.balance(idx)
        return element
    def remove(self, element):
        """"""
        idx = self.find(element)
        if idx == -1:
            raise ValueError("Heap remove element not find")
        return self.removeAt(idx) == element
    def pop(self):
        """"""
        return self.removeAt(0)
    def add(self, element):
        """"""
        self.hp_.append(element)
        self.len_ += 1
        self.balance(self.len_ - 1)
    def isHeap(self, idx = 0):
        """"""
        l = self.isHeap(self.getLeftIdx(idx)) \
            if self.getLeftIdx(idx) >= 0 and self.getLeftIdx(idx) < self.len_ \
            else True
        r = self.isHeap(self.getRightIdx(idx)) \
            if self.getRightIdx(idx) >= 0 and self.getRightIdx(idx) < self.len_ \
            else True
        return l and r
    def copy(self):
        """"""
        return copy.deepcopy(self)
    class iterator:
        """Iterator Class
        Args:
            heap (Heap): The Heap iterator is for."""
        def __init__(self, heap):
            """Iterator Counstructor"""
            self.heap = heap
            self.heap_toUse = heap.copy()
            self.expectedCount = len(heap)
        def __next__(self):
            """"""
            if self.expectedCount != len(self.heap):
                raise ValueError("Heap Iterator Invalidation")
            if len(self.heap_toUse) == 0:
                raise StopIteration()
            return self.heap_toUse.pop()
