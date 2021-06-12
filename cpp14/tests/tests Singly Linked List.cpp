// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Testing Dynamic Array

#include <ostream>
#include "gtest/gtest.h"
#include "Utility_/Utility_.hpp"
#include "SinglyLinkedList/SinglyLinkedList.hpp"
#include "utility test.hpp"

namespace self
{

template <typename T>
class SinglyLinkedListTest : public ::testing::Test
{
public:
    T obj0; T obj1; T obj2; T obj3;
    T obj_1; T obj_2; T objA; T objB;
    T* arr;
    // All T object is independently defined because for same types T a, b placment,
    // may change meaning, for example pointer types
    INTEGER size, setIndex, largeIndex = 100, negativeIndex = -16;
    self::SinglyLinkedList<T> sll;

    // INTEGER Case
    template<class Q = T>
    ENABLE_IF(IS_SAME(Q, INTEGER))
    initialize_dependent() {
        obj0 = 1; obj1 = 2; obj2 = 3; obj3 = 4;
        obj_2 = 9; obj_1 = 10; objA = 12; objB = 16;
        size = 10; setIndex = 8;
        sll = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        arr = new T[size];
        T _arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::copy(_arr, _arr + size, arr);
    }

    // char Case
    template<class Q = T>
    ENABLE_IF(IS_SAME(Q, char))
    initialize_dependent() {
        obj0 = 'a'; obj1 = 'b'; obj2 = 'c'; obj3 = 'd';
        obj_2 = 'k'; obj_1 = 'l';  objA = 'n'; objB = 'p';
        size = 12; setIndex = 5;
        sll = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
        arr = new T[size];
        T _arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
        std::copy(_arr, _arr + size, arr);
    }

    // UDTfT Case
    template<class Q = T>
    ENABLE_IF(IS_SAME(Q, UDTfT))
    initialize_dependent() {
        obj0.set(1, 'a', 2.5); obj1.set(2, 'b', 5.0);
        obj2.set(3, 'c', 7.5); obj3.set(4, 'd', 10.0);
        obj_2.set(7, 'g', 17.5); obj_1.set(8, 'h', 20.0);
        objA.set(51, 'z', 16.0); objB.set(25, 'y', 14.0);
        size = 8; setIndex = 5;
        arr = new T[size];
        for (INTEGER i = 0; i < size; ++i) {
            UDTfT obbj;
            obbj.set(i + 1, 'a' + i, double(double(i + 1) * 2.5));
            sll.append(obbj);
            arr[i] = obbj;
        }
    }
    
    // Other Case
    template<class Q = T>
    ENABLE_IF(!IS_SAME(Q, char) && !IS_SAME(Q, INTEGER) && !IS_SAME(Q, UDTfT))
    initialize_dependent() {
        throw exception(
            std::string("Unrecognized type for Singly Linked List Test:") +
            std::string(typeid(Q()).name())
        );
    }

    void initialize_independent() { ; }
    void SetUp() override { initialize_dependent(); initialize_independent(); }
    void TearDown() override { sll._delete(); }
};
TYPED_TEST_SUITE_P(SinglyLinkedListTest);

TYPED_TEST_P(SinglyLinkedListTest, SizeTest) {
    EXPECT_EQ(this -> sll.size(), this -> size);
    this -> sll.append(this -> objA);
    EXPECT_EQ(this -> sll.size(), this -> size + 1);
}
// TYPED_TEST_P(SinglyLinkedListTest, isEmptyTest) {
//     EXPECT_EQ(this -> sll.isEmpty(), this -> isEmpty);
//     this -> sll.append(this -> objB);
//     EXPECT_FALSE(this -> sll.isEmpty());
// }
TYPED_TEST_P (SinglyLinkedListTest, getTest) {
    EXPECT_EQ(this -> sll.get(0), this -> obj0);
    EXPECT_EQ(this -> sll.get(2), this -> obj2);
}
TYPED_TEST_P (SinglyLinkedListTest, getSquareBracketTest) {
    EXPECT_EQ(this -> sll[0], this -> obj0);
    EXPECT_EQ(this -> sll[2], this -> obj2);
}
TYPED_TEST_P (SinglyLinkedListTest, getNegativeIndexTest) {
    EXPECT_EQ(this -> sll.get(-1), this -> obj_1);
    EXPECT_EQ(this -> sll.get(-2), this -> obj_2);
}
TYPED_TEST_P (SinglyLinkedListTest, getInvalidIndexTest) {
    EXPECT_THROW(this -> sll.get(this -> negativeIndex), exception);
    EXPECT_THROW(this -> sll.get(this -> largeIndex), exception);   
}
TYPED_TEST_P (SinglyLinkedListTest, setTest) {
    this -> sll.set(this -> objA, this -> setIndex);
    EXPECT_EQ(this -> sll.get(this -> setIndex), this -> objA);
    EXPECT_THROW(this -> sll.set(this -> objA, this -> negativeIndex), exception);
    EXPECT_THROW(this -> sll.set(this -> objA, this -> largeIndex), exception);
}
TYPED_TEST_P (SinglyLinkedListTest, addInvalidIndexTest) {
    EXPECT_THROW(this -> sll.add(this -> objA, this -> negativeIndex), exception);
    EXPECT_THROW(this -> sll.add(this -> objA, this -> largeIndex), exception);
}
TYPED_TEST_P (SinglyLinkedListTest, addTest) {
    this -> sll.add(this -> objA, this -> setIndex);
    EXPECT_EQ(this -> sll.get(this -> setIndex), this -> objA);
}
TYPED_TEST_P (SinglyLinkedListTest, appendTest) {
    this -> sll.append(this -> objA);
    EXPECT_EQ(this -> sll.get(this -> size), this -> objA);
}
TYPED_TEST_P (SinglyLinkedListTest, addFirstTest) {
    this -> sll.add_first(this -> objA);
    EXPECT_EQ(this -> sll.get(0), this -> objA);
}
TYPED_TEST_P (SinglyLinkedListTest, findTest) {
    EXPECT_EQ(this -> sll.find(this -> obj1), 01);
    EXPECT_EQ(this -> sll.find(this -> objA), -1);
    EXPECT_TRUE(this -> sll.contains(this -> obj2));
    EXPECT_FALSE(this -> sll.contains(this -> objA));
}
TYPED_TEST_P (SinglyLinkedListTest, removeTest) {
    EXPECT_TRUE(this -> sll.contains(this -> obj3));
    EXPECT_TRUE(this -> sll.remove(this -> obj3));
    EXPECT_FALSE(this -> sll.contains(this -> obj3));
}
TYPED_TEST_P (SinglyLinkedListTest, iteratorTest) {
    INTEGER ii = 0;
    for (TypeParam ele:this -> sll) {
        ASSERT_EQ(ele, this -> arr[ii++]);
    }
}

REGISTER_TYPED_TEST_SUITE_P(
    SinglyLinkedListTest,
    SizeTest,
    // isEmptyTest,
    getTest,
    getSquareBracketTest,
    getNegativeIndexTest,
    getInvalidIndexTest,
    setTest,
    addInvalidIndexTest,
    addTest,
    appendTest,
    addFirstTest,
    findTest,
    removeTest,
    iteratorTest
);
INSTANTIATE_TYPED_TEST_SUITE_P(SinglyLinkedListTestPrefix, SinglyLinkedListTest, TestTypes);

}
