# @author: Kartikei Mittal
# @email: kartikeimittal@gmail.com
# Singly Linked Lists

__author__ = "Kartikei Mittal"

from Node import NodeOneChild

class SinglyLinkedList:
    """Singly Linked List Class"""
    def __init__(self):
        """Counstructor"""
        self.iter_curr = None
        self.head = None
        self.tail = None
        self.len_ = 0

    def isEmpty(self):
        """Check for Linked List emptiness
        Returns:
            bool : Wheather Linked List is empty"""
        return self.len_ == 0
    def setValue(self, index, element):
        """Method to set element value
        Args:
            index (int): Index to set element on
            element (): New Element value
        Raises:
            valueError: If index not in [0, len)"""
        if index < 0 or index >= self.len_: raise ValueError("Invalid SET index {}".format(index))
        curr = self.head
        while index > 0:
            curr = curr._next
            index -= 1
        curr.data = element
    def find(self, element):
        """Find Method
        Args:
            element : Element to look for
        Returns:
            int : Index of element if found else -1"""
        ii = 0
        ans = -1
        curr = self.head
        while curr != None:
            if curr.data == element:
                ans = ii
                break
            curr = curr._next
            ii += 1
        return ans
    def contains(self, element):
        """Check presence of the given element
        Args:
            element : Element to check for
        Returns:
            bool : Wheather element present"""
        return self.find(element) != -1
    def add_first(self, element):
        """Add first method
        Args:
            element : Element to be new head of linked list"""
        self.len_ += 1
        node = NodeOneChild(element)
        node._next = self.head
        self.head = node
        if self.tail == None: self.tail = self.head
    def append(self, elem):
        """Append given element
        Args:
            element : Element to append"""
        self.len_ += 1
        if self.tail == None:
            node = NodeOneChild(elem)
            self.head = node
            self.tail = node
        else:
            self.tail._next = NodeOneChild(elem)
            self.tail = self.tail._next
    def add(self, index, element):
        """Add method
        Args:
            index (int): Index to add element at
            element : Element to add
        Raises:
            ValueError: If index not in [0, len)"""
        if index < 0 or index >= self.len_: raise ValueError("Invalid ADD index {}".format(index))
        if index == 0:
            self.add_first(element)
            return
        self.len_ += 1
        index -= 1
        in_front_of = self.head
        node = NodeOneChild(element)
        while index > 0:
            in_front_of = in_front_of._next
            index -= 1
        node._next = in_front_of._next
        in_front_of._next = node
    def remove_first(self):
        """Remove method for first element of the linked list
        Returns:
            bool : Wheather successfully removed"""
        if self.head == None: return False
        if self.head == self.tail:
            self.head = None
            self.tail = None
            self.len_ = 0
            return True
        self.head = self.head._next
        self.len_ -= 1
        return True
    def remove_last(self):
        """Remove method for the last element of the linked list
        Returns:
            bool : Wheather successfully removed"""
        if self.tail == None: return False
        if self.head == self.tail:
            self.head = None
            self.tail = None
            self.len_ = 0
            return True
        curr = self.head
        while curr._next != self.tail: curr = curr._next
        self.tail = curr
        self.tail._next = None
        self.len_ -= 1
        return True
    def remove(self, element):
        """Remove method
        Args:
            element : Element to remove
        Returns:
            bool : Wheather successfully removed"""
        if self.len_ <= 0: return False
        if self.head.data == element: return self.remove_first()
        if self.tail.data == element: return self.remove_last()
        curr = self.head
        while curr != None and curr.data != element: curr = curr._next
        if curr == None: return False
        curr_next = curr._next
        curr.data = curr_next.data
        curr._next = curr_next._next
        curr_next._next = None
        if curr_next == self.tail: self.tail = curr
        self.len_ -= 1
        return True
    def __getitem__(self, index):
        """Overload for [] operator for element wise access
        Args:
            index (int): Index to fetch elemnet from
        Returns:
            type(self.arr[index]) : Value at given index
        Raises:
            valueError: If index not in [-len, len)"""
        if index < 0: index += self.len_
        if index < 0 or index >= self.len_: raise ValueError("Invalid index {} for [] Linked List".format(index))
        curr = self.head
        while index > 0:
            curr = curr._next
            index -= 1
        return curr.data
    def __iadd__(self, attachment):
        """Overload for += operator to add elemnt from a iterable
        Args:
            attachment (iterable): Iterable object to attach
        Returns: self"""
        if len(attachment) == 0: return
        for element in attachment: self.append(element)
        return self
    def __len__(self):
        """Channels self.len_ method for len() overload
        Returns:
            int : Size of Linked List"""
        return self.len_
    def __iter__(self):
        """Iterable Method
        Returns:
            self : Return self object"""
        self.expectedCount = self.len_
        self.iter_curr = self.head
        return self
    def __next__(self):
        """Next method for Iterator
        Returns:
            () : Element at appropriate position"""
        if self.expectedCount != self.len_: raise ValueError("Singly Linked List Iterator Invalidation")
        if self.iter_curr == None:
            raise StopIteration()
        result = self.iter_curr.data
        self.iter_curr = self.iter_curr._next
        return result
    def __del__(self):
        """Destructor"""
        while self.len_ > 0: self.remove_last()
