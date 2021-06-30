# @author: Kartikei Mittal
# @email: kartikeimittal@gmail.com
# Dynamic Array

__author__ = "Kartikei Mittal"

class DynamicArray:
    """"""
    DEFAULT_CAPACITY = 8
    def __init__(self, cap = DEFAULT_CAPACITY):
        """Counstructor
        Args:
            cap (int): Initial Size of dynamic array
        Raises:
            ValueError: When value of argument cap is less than or equal to zero."""
        self.len_ = 0
        self.index_ = -1
        self.capacity = cap
        if cap <= 0: raise ValueError("Invalid Dynamic Array Capacity")
        self.arr = list()

    def size(self):
        """Size method for Dynamic array, provides current size of array
        Returns:
            int : Size of arra."""
        return self.len_
    def __len__(self):
        """Channels self.size method for len() overload
        Returns:
            int : Size of array"""
        return self.size()
    def isEmpty(self):
        """Check for array emptiness
        Returns:
            bool : Wheather array is empty"""
        return self.len_ == 0
    def __getitem__(self, index):
        """Overload for [] operator for element wise access
        Args:
            index (int): Index to fetch elemnet from
        Returns:
            type(self.arr[index]) : Value at given index
        Raises:
            valueError: If index not in [-len, len)"""
        if index < 0: index += self.len_
        if index < 0 or index >= self.len_: raise ValueError("Invalid GET Index")
        return self.arr[index]
    def setValue(self, index, element):
        """Method to set element value
        Args:
            index (int): Index to set element on
            element (): New Element value
        Raises:
            valueError: If index not in [0, len)"""
        if index < 0 or index >= self.len_: raise ValueError("Invalid SET index")
        self.arr[index] = element
    def __iadd__(self, attachment):
        """Overload for += operator to add elemnt from a iterable
        Args:
            attachment (iterable): Iterable object to attach to array
        Returns: self"""
        if self.len_ + len(attachment) >= self.capacity:
            self.capacity = (self.len_ + len(attachment)) * 2
        self.arr.extend(attachment)
        self.len_ += len(attachment)
        return self
    def add(self, index, element):
        """Adde method
        Args:
            index (int): Index to add element at
            element : Element to add to array
        Raises:
            valueError: If index not in [0, len)"""
        if index < 0 or index >= self.len_: raise ValueError("Invalid ADD index")
        self.arr.insert(index, element)
        self.len_ += 1
    def append(self, element):
        """Appens given element to the array
        Args:
            element : Element to append"""
        self.arr.append(element)
        self.len_ += 1
    def find(self, element):
        """Find Method
        Args:
            element : Element to look for
        Returns:
            int : Index of element if found else -1"""
        if element not in self.arr: return -1
        return self.arr.index(element)
    def contains(self, element):
        """Check presence of the given element
        Args:
            element : Element to check for
        Returns:
            bool : Wheather element present in array"""
        return self.find(element) != -1
    def remove(self, element):
        """Remove method
        Args:
            element : Element to remove from array
        Returns:
            bool : Wheather successfully removed"""
        if element not in self.arr: return False
        self.arr.remove(element)
        self.len_ -= 1
        return True
    def removeAt(self, index):
        """Remove element at given index
        Args:
            index (int): Index to remove element from"""
        if index < 0 or index >= self.len_: raise ValueError("Invalid Remove Ats index")
        del self.arr[index]
        self.len_ -= 1
    def __iter__(self):
        """Iterable Method"""
        self.expectedCount = self.len_
        self.index_ = -1
        return self
    def __next__(self):
        """Next method for Iterator"""
        if self.expectedCount != self.len_: raise ValueError("Dynamic Array Iterator Invalidation")
        self.index_ += 1
        if self.index_ >= self.len_:
            raise StopIteration()
        return self.arr[self.index_]
