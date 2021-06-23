# @author: Kartikei Mittal
# @email: kartikeimittal@gmail.com
# Dynamic Array

__author__ = "Kartikei Mittal"

class DynamicArray:
    """"""
    DEFAULT_CAPACITY = 8
    def __init__(self, cap = DEFAULT_CAPACITY):
        """Counstructor"""
        self.len = 0
        self._index = -1
        self.capacity = cap
        if cap <= 0: raise ValueError("Invalid Dynamic Array Capacity")
        self.arr = list()

    def size(self):
        """"""
        return self.len
    def __len__(self):
        """"""
        return self.size()
    def isEmpty(self):
        """"""
        return self.len == 0
    def __getitem__(self, index):
        """"""
        if index < 0: index += self.len
        if index < 0 or index >= self.len: raise ValueError("Invalid GET Index")
        return self.arr[index]
    def setValue(self, index, element):
        """"""
        if index < 0 or index >= self.len: raise ValueError("Invalid SET index")
        self.arr[index] = element
    def __iadd__(self, attachment):
        """"""
        if self.len + len(attachment) >= self.capacity:
            self.capacity = (self.len + len(attachment)) * 2
        self.arr.extend(attachment)
        self.len += len(attachment)
        return self
    def add(self, index, element):
        """"""
        if index < 0 or index >= self.len: raise ValueError("Invalid ADD index")
        self.arr.insert(index, element)
        self.len += 1
    def append(self, element):
        """"""
        self.arr.append(element)
        self.len += 1
    def find(self, element):
        """"""
        if element not in self.arr: return -1
        return self.arr.index(element)
    def contains(self, element):
        """"""
        return self.find(element) != -1
    def remove(self, element):
        """"""
        if element not in self.arr: return False
        self.arr.remove(element)
        self.len -= 1
        return True
    def removeAt(self, index):
        """"""
        if index < 0 or index >= self.len: raise ValueError("Invalid Remove Ats index")
        del self.arr[index]
        self.len -= 1
    def __iter__(self):
        """Iterable Method"""
        self.expectedCount = self.len
        return self
    def __next__(self):
        """Next method for Iterator"""
        if self.expectedCount != self.len: raise ValueError("Dynamic Array Iterator Invalidation")
        self._index += 1
        if self._index >= self.len:
            self._index = -1
            raise StopIteration()
        else: return self.arr[self._index]
