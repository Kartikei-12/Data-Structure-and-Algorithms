# @author: Kartikei Mittal
# @email: kartikeimittal@gmail.com
# Singly Linked List Example

__author__ = "Kartikei Mittal"

from Data_Structure import SinglyLinkedList

if __name__ == "__main__":
    print("Hello Singly Linked List!")
    sll = SinglyLinkedList()
    sll += [1, 2, 4, 5, 6, 7, 8]
    sll.append(15)
    for i, element in enumerate(sll):
        print("({}, {}), ".format(i, element), end = '')
    print("\n####################################################################################")
