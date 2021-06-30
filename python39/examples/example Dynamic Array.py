# @author: Kartikei Mittal
# @email: kartikeimittal@gmail.com
# Dynamic Array Example

__author__ = "Kartikei Mittal"

from Data_Structure import DynamicArray

if __name__ == "__main__":
    print("Hello Dynamic Array!")
    da = DynamicArray(cap = 16)
    da += [1, 2, 4, 5, 6, 7, 8]
    da.append(15)
    for i, element in enumerate(da):
        print("({}, {}), ".format(i, element), end = '')
    print("\n####################################################################################")
