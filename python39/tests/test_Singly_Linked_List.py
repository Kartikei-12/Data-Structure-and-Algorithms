# @author: Kartikei Mittal
# @email: kartikeimittal@gmail.com
# Testing Singly Linked List

__author__ = "Kartikei Mittal"

import unittest
from parameterized import parameterized_class, parameterized
from utility import UDTfT
from Data_Structure import SinglyLinkedList

@parameterized_class([{
    "size": 8, "set_index": 7,
    "neg_index": -50, "large_index": 51,
    "type_": "INTEGER",
    "sll": [1, 2, 3, 4, 5, 6, 7, 8],
    "objA": 12,
    "obj0": 1, "obj2": 3,
    "obj_1": 8, "obj_2": 7
}, {
    "size": 4, "set_index": 3,
    "neg_index": -20, "large_index": 51,
    "type_": "char",
    "sll": ['a', 'b', 'c', 'd'],
    "objA": 'A',
    "obj0": 'a', "obj2": 'c',
    "obj_1": 'd', "obj_2": 'c'
}, {
    "size": 12, "set_index": 9,
    "neg_index": -20, "large_index": 51,
    "type_": "UDTfT",
    "sll": list(),
    "objA": UDTfT(51, '*', 16.5),
    "obj0": UDTfT(1, 'a', 2.5), "obj2": UDTfT(3, 'c', 7.5),
    "obj_1": UDTfT(12, 'l', 30.0), "obj_2": UDTfT(11, 'k', 27.5)
}], class_name_func = lambda cls, num, params_dict: cls.__name__ + '.' + parameterized.to_safe_name(params_dict["type_"]))
class SinglyLinkedListTest(unittest.TestCase):
    """Singly Linked List Test Class"""

    def setUp(self):
        """Singly Linked List Test Set Up"""
        self.sll_ = SinglyLinkedList()
        if self.type_ != "UDTfT":
            self.sll_ += self.sll
        else:
            for i in range(self.size):
                obj = UDTfT(i + 1, chr(97 + i), (i + 1) * 2.5)
                self.sll_.append(obj)
                self.sll.append(obj)
        self.size_ = self.size

    def test_size(self):
        """Size Test"""
        self.assertEqual(len(self.sll_), self.size_)
    def test_get(self):
        """Getter method Test"""
        self.assertEqual(self.sll_[0], self.obj0)
        self.assertEqual(self.sll_[2], self.obj2)
    def test_getNegativeIndex(self):
        """Getter Negative Index method Test"""
        self.assertEqual(self.sll_[-1], self.obj_1)
        self.assertEqual(self.sll_[-2], self.obj_2)
    def test_getInvalidIndex(self):
        """Getter Invalid Index method Test"""
        with self.assertRaises(ValueError) as _: self.sll_[self.neg_index]
        with self.assertRaises(ValueError) as _: self.sll_[self.large_index]
    def test_set(self):
        """Testing setter method"""
        self.sll_.setValue(self.set_index, self.objA)
        self.assertEqual(self.sll_[self.set_index], self.objA)
        with self.assertRaises(ValueError) as _: self.sll_.setValue(self.neg_index, self.objA)
        with self.assertRaises(ValueError) as _: self.sll_.setValue(self.large_index, self.objA)
    def test_append(self):
        """Testing append method"""
        self.sll_.append(self.objA)
        self.assertEqual(self.sll_[-1], self.objA)
        self.assertEqual(len(self.sll_), self.size_ + 1)
    def test_add_first(self):
        """Testing add first"""
        self.sll_.add_first(self.objA)
        self.assertEqual(self.sll_[0], self.objA)
        self.assertEqual(len(self.sll_), self.size_ + 1)
    def test_add(self):
        """Testing add method"""
        self.sll_.add(self.size_ - 1, self.objA)
        self.assertEqual(self.sll_[self.size_ - 1], self.objA)
        self.assertEqual(self.sll_[self.size_], self.obj_1)
        with self.assertRaises(ValueError) as _: self.sll_.add(self.neg_index, self.objA)
        with self.assertRaises(ValueError) as _: self.sll_.add(self.large_index, self.objA)
    def test_find(self):
        """Testing Find"""
        self.assertEqual(self.sll_.find(self.obj2), 2)
        self.assertEqual(self.sll_.find(self.objA), -1)
        self.assertTrue(self.sll_.contains(self.obj2))
        self.assertFalse(self.sll_.contains(self.objA))
    def test_remove(self):
        """Testing Remove"""
        self.assertTrue(self.sll_.contains(self.obj2))
        self.assertTrue(self.sll_.remove(self.obj2))
        self.assertFalse(self.sll_.contains(self.obj2))
        self.assertFalse(self.sll_.remove(self.objA))
    def test_iterator(self):
        """Iterator Test"""
        ii = 0
        for obj in self.sll_:
            self.assertEqual(obj, self.sll[ii])
            ii += 1
    def test_iteratorInvalidation(self):
        """Testing for Iterator Invalidation"""
        obj = iter(self.sll_)
        self.sll_.append(self.objA)
        with self.assertRaises(ValueError) as _: _ = next(obj)
    def tearDown(self):
        """Singly Linked List Test Tear Down"""
        del self.sll_
        del self.size_
