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
        """"""
        return self.len_ == 0
    def setValue(self, index, element):
        """"""
        if index < 0 or index >= self.len_: raise ValueError("Invalid SET index {}".format(index))
        curr = self.head
        while index > 0:
            curr = curr._next
            index -= 1
        curr.data = element
    def find(self, element):
        """"""
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
        """"""
        return self.find(element) != -1
    def add_first(self, element):
        """"""
        self.len_ += 1
        node = NodeOneChild(element)
        node._next = self.head
        self.head = node
        if self.tail == None: self.tail = self.head
    def append(self, elem):
        """Append Method"""
        self.len_ += 1
        if self.tail == None:
            node = NodeOneChild(elem)
            self.head = node
            self.tail = node
        else:
            self.tail._next = NodeOneChild(elem)
            self.tail = self.tail._next
    def add(self, index, element):
        """"""
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
        """"""
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
        """"""
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
        """"""
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
        """"""
        if index < 0: index += self.len_
        if index < 0 or index >= self.len_: raise ValueError("Invalid index {} for [] Linked List".format(index))
        curr = self.head
        while index > 0:
            curr = curr._next
            index -= 1
        return curr.data
    def __iadd__(self, attachment):
        """"""
        if len(attachment) == 0: return
        for element in attachment: self.append(element)
        return self
    def __len__(self):
        """"""
        return self.len_
    def __iter__(self):
        """"""
        self.expectedCount = self.len_
        self.iter_curr = self.head
        return self
    def __next__(self):
        """"""
        if self.expectedCount != self.len_: raise ValueError("Singly Linked List Iterator Invalidation")
        if self.iter_curr == None:
            raise StopIteration()
        result = self.iter_curr.data
        self.iter_curr = self.iter_curr._next
        return result
    def __del__(self):
        """Destructor"""
        while self.len_ > 0: self.remove_last()
