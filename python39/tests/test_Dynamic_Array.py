# @author: Kartikei Mittal
# @email: kartikeimittal@gmail.com
# Testing Dynamic Array

__author__ = "Kartikei Mittal"

import unittest
from parameterized import parameterized_class, parameterized
from utility import UDTfT
from Data_Structure import DynamicArray

@parameterized_class([{
    "size": 8, "set_index": 7,
    "neg_index": -5, "large_index": 51,
    "type_": "INTEGER",
    "arr": [1, 2, 3, 4, 5, 6, 7, 8],
    "objA": 12,
    "obj0": 1, "obj2": 3,
    "obj_1": 8, "obj_2": 7
}, {
    "size": 4, "set_index": 3,
    "neg_index": -2, "large_index": 51,
    "type_": "char",
    "arr": ['a', 'b', 'c', 'd'],
    "objA": 'A',
    "obj0": 'a', "obj2": 'c',
    "obj_1": 'd', "obj_2": 'c'
}, {
    "size": 12, "set_index": 9,
    "neg_index": -10, "large_index": 51,
    "type_": "UDTfT",
    "arr": list(),
    "objA": UDTfT(51, '*', 16.5),
    "obj0": UDTfT(1, 'a', 2.5), "obj2": UDTfT(3, 'c', 7.5),
    "obj_1": UDTfT(12, 'l', 30.0), "obj_2": UDTfT(11, 'k', 27.5)    
}], class_name_func = lambda cls, num, params_dict: cls.__name__ + '.' + parameterized.to_safe_name(params_dict["type_"]))
class DynamicArrayTest(unittest.TestCase):
    """Dynamic Array Test Class"""
    
    def setUp(self):
        """Dynamic Array Test Set Up"""
        self.arr_ = DynamicArray()
        if self.type_ != "UDTfT":
            self.arr_ += self.arr
        else:
            for i in range(self.size):
                obj = UDTfT(i + 1, chr(97 + i), (i + 1) * 2.5)
                self.arr_.append(obj)
                self.arr.append(obj)
        self.size_ = self.size

    def test_counstructorException(self):
        """Counstructor Exceptuion Test"""
        with self.assertRaises(ValueError) as _: DynamicArray(-1)
    def test_size(self):
        """Size Test"""
        self.assertEqual(len(self.arr_), self.size_)
    def test_get(self):
        """Getter method Test"""
        self.assertEqual(self.arr_[0], self.obj0)
        self.assertEqual(self.arr_[2], self.obj2)
    def test_getNegativeIndex(self):
        """Getter Negative Index method Test"""
        self.assertEqual(self.arr_[-1], self.obj_1)
        self.assertEqual(self.arr_[-2], self.obj_2)
    def test_set(self):
        """Testing setter method"""
        self.arr_.setValue(self.set_index, self.objA)
        self.assertEqual(self.arr_[self.set_index], self.objA)
        with self.assertRaises(ValueError) as _: self.arr_.setValue(self.neg_index, self.objA)
        with self.assertRaises(ValueError) as _: self.arr_.setValue(self.large_index, self.objA)
    def test_add(self):
        """Testing add method"""
        self.arr_.add(self.size_ - 1, self.objA)
        self.assertEqual(self.arr_[self.size_ - 1], self.objA)
        self.assertEqual(self.arr_[self.size_], self.obj_1)
        with self.assertRaises(ValueError) as _: self.arr_.add(self.neg_index, self.objA)
        with self.assertRaises(ValueError) as _: self.arr_.add(self.large_index, self.objA)
    def test_find(self):
        """Testing Find"""
        self.assertEqual(self.arr_.find(self.obj2),  2)
        self.assertEqual(self.arr_.find(self.objA),  -1)
        self.assertTrue(self.arr_.contains(self.obj2))
        self.assertFalse(self.arr_.contains(self.objA))
    def test_remove(self):
        """Testing Remove"""
        self.assertTrue(self.arr_.contains(self.obj2))
        self.assertTrue(self.arr_.remove(self.obj2))
        self.assertFalse(self.arr_.contains(self.obj2))
        self.assertFalse(self.arr_.remove(self.objA))
    def test_iterator(self):
        """Iterator Test"""
        ii = 0
        for obj in self.arr_:
            self.assertEqual(obj, self.arr[ii])
            ii += 1
    def test_iteratorInvalidation(self):
        """Testing for Iterator Invalidation"""
        obj = iter(self.arr_)
        self.arr_.append(self.objA)
        with self.assertRaises(ValueError) as _: _ = next(obj)
    
    def tearDown(self):
        """Dynamic Array Test Tear Down"""
        del self.arr_
        del self.size_
