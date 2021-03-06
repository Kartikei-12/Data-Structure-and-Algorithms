"""@author: Kartikei Mittal
@email: kartikeimittal@gmail.com
Testing Utility"""

__author__ = "Kartikei Mittal"

class UDTfT:
    """User Defined Type for Testing"""
    def __init__(self, a = 0, b = ' ', c = 1.5):
        """Counstructor"""
        self.a = a
        self.b = b
        self.c = c
    def __eq__(self, other):
        """Overload == Operator"""
        return self.a == other.a and self.b == other.b and self.c == other.c
    def __ne__(self, other):
        """Overload != Operator"""
        return self.a != other.a or self.b != other.b or self.c != other.c
    def __repr__(self):
        """Support print"""
        return "UDTfT({}, {}, {})".format(self.a, self.b, self.c)

Comparator = lambda A, B: 0 if A.a == B.a else 1 if A.a < B.a else -1
InverseComparator = lambda A, B: 0 if A.a == B.a else -1 if A.a < B.a else 1
