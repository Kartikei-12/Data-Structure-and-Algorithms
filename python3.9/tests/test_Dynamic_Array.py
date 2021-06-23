# @author: Kartikei Mittal
# @email: kartikeimittal@gmail.com
# Testing Dynamic Array

__author__ = "Kartikei Mittal"

import unittest
from parameterized import parameterized_class, parameterized
from utility import UDTfT 
from Data_Structure import DynamicArray

# def get_class_name(cls, num, params_dict):
#     """Create class name for test suite"""
#     return cls.__name__ + '.' + parameterized.to_safe_name(params_dict["type_"])
@parameterized_class([
    {"size":  8, "type_": "INTEGER", "arr": [1, 2, 3, 4, 5, 6, 7, 8],},
    {"size":  4, "type_": "char", "arr": ['a', 'b', 'c', 'd']},
    {"size": 12, "type_": "UDTfT", "arr": []}
], class_name_func = lambda cls, num, params_dict: cls.__name__ + '.' + parameterized.to_safe_name(params_dict["type_"]))
class DynamicArrayTest(unittest.TestCase):
    """Dynamic Array Test Class"""
    
    def setUp(self):
        """Dynamic Array Test Set Up"""
        self.arr_ = DynamicArray()
        if self.type_ != "UDTfT":
            self.arr_ += self.arr
        else:
            for i in range(self.size):
                self.arr_.append(UDTfT(i + 1, chr(97 + i), (i + 1) * 2.5))
        self.size_ = self.size

    def test_size(self):
        """Size Test"""
        self.assertEqual(len(self.arr_), self.size_)

    def tearDown(self):
        """Dynamic Array Test Tear Down"""
        del self.arr_
        del self.size_
