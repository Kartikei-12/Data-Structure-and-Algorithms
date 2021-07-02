"""@author: Kartikei Mittal
@email: kartikeimittal@gmail.com
Testing Dynamic Array"""

__author__ = "Kartikei Mittal"

import unittest
from parameterized import parameterized_class, parameterized
from Data_Structure import Heap
from utility import UDTfT, Comparator, InverseComparator

@parameterized_class([{
    "type_": "INTEGER",
    "heap": [1, 2, 3, 4, 5, 6, 7, 8],
    "objA": 12, "objB": 16,
}, {
    "type_": "INTEGER Inverse",
    "heap": [1, 2, 3, 4, 5, 6, 7, 8],
    "objA": 12, "objB": 16,
}, {
    "type_": "char",
    "heap": ['a', 'b', 'c', 'd'],
    "objA": 'g', "objB": 'h',
}, {
    "type_": "char Inverse",
    "heap": ['a', 'b', 'c', 'd'],
    "objA": 'g', "objB": 'h',
}, {
    "type_": "UDTfT",
    "heap": [
        UDTfT(1, 'a', 1.5), UDTfT(2, 'b', 3.0), UDTfT(3, 'c', 4.5),
        UDTfT(4, 'd', 6.0), UDTfT(5, 'e', 7.5), UDTfT(6, 'f', 9.0),
    ],
    "objA": UDTfT(51, 'A', 16.5), "objB": UDTfT(61, 'B', 19.3)
}, {
    "type_": "UDTfT Inverse",
    "heap": [
        UDTfT(1, 'a', 1.5), UDTfT(2, 'b', 3.0), UDTfT(3, 'c', 4.5),
        UDTfT(4, 'd', 6.0), UDTfT(5, 'e', 7.5), UDTfT(6, 'f', 9.0),
    ],
    "objA": UDTfT(51, 'A', 16.5), "objB": UDTfT(61, 'B', 19.3),
}], class_name_func = lambda cls, num, params_dict:
    cls.__name__ + '.' +
    parameterized.to_safe_name(params_dict["type_"])
)
class HeapTest(unittest.TestCase):
    """Heap Test Class"""
    def setUp(self):
        """Heap Test Set Up"""
        inv = True if "Inverse" in self.type_ else False
        if "UDTfT" in self.type_:
            comp = InverseComparator if "Inverse" in self.type_ else Comparator
        else:
            comp = None
        self.heap_ = Heap(inverse = inv, compare_ = comp)
        self.heap_ += self.heap
        self.size_ = len(self.heap)
        self.top1 = self.heap[0] if "Inverse" not in self.type_ else self.heap[-1]
        self.top2 = self.heap[1] if "Inverse" not in self.type_ else self.heap[-2]

    def test_isHeap(self):
        """Testing is Heap"""
        self.assertTrue(self.heap_.isHeap())
    def test_size(self):
        """Testing size"""
        self.assertEqual(len(self.heap_), self.size_)
    def test_top(self):
        """Testing top"""
        self.assertEqual(self.heap_.top(), self.top1)
    def test_add(self):
        """Testing Add"""
        self.heap_.add(self.objA)
        if "Inverse" not in self.type_:
            self.assertEqual(self.heap_.top(), self.top1)
        else:
            self.assertEqual(self.heap_.top(), self.objA)

# TYPED_TEST_P(HeapTest, addTest) {
#     this -> hp.add(this -> objA);
#     if (TypeParam::inverse) {
#         EXPECT_EQ(this -> hp.top(), this -> top1);
#     } else {
#         EXPECT_EQ(this -> hp.top(), this -> objA);
#     }
#     EXPECT_EQ(this -> hp.size(), this -> size + 1);
# }
# TYPED_TEST_P(HeapTest, popTest) {
# EXPECT_EQ(this -> hp.pop(), this -> top1);
# EXPECT_EQ(this -> hp.pop(), this -> top2);
# EXPECT_EQ(this -> hp.size(), this -> size - 2);
# }
# TYPED_TEST_P(HeapTest, removeTest) {
# EXPECT_TRUE(this -> hp.find(this -> top2));
# EXPECT_TRUE(this -> hp.remove(this -> top2));
# EXPECT_EQ(this -> hp.find(this -> top2), -1);
# EXPECT_EQ(this -> hp.size(), this -> size - 1);
# }
# TYPED_TEST_P(HeapTest, iteratorTest) {
# INTEGER index = 0;
# for (typename TypeParam::base_ elem : this -> hp) {
#     EXPECT_EQ(elem, this -> arr[index++]);
# }
# }
# TYPED_TEST_P(HeapTest, iteratorInvalidationTest) {
# typename TypeParam::main_::iterator ii = this -> hp.begin();
# this -> hp.add(this -> top1);
# EXPECT_THROW(ii != this -> hp.end(), self::exception);
# }
