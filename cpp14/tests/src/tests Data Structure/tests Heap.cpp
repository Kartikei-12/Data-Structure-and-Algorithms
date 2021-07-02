/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Heap tests.
 * @author Kartikei Mittal
*/

#include "gtest/gtest.h"
#include "Utility/Utility.hpp"
#include "Heap/Heap.hpp"
#include "HelpTest/HelpTest.hpp"

namespace self {

template <typename T>
class HeapTest : public ::testing::Test {
 public:
    INTEGER size;
    T_main hp;
    T_base *arr;
    T_base top1; T_base top2;
    T_base objA; T_base objB;

    // char Case
    template<class Q = T_main>
    ENABLE_IF(
        (std::is_same<Q, Heap<char, false>>::value) ||
        (std::is_same<Q, Heap<char,  true>>::value)
    , void)
    initialize_dependent() {
        size = 16;
        top1 = (T::inverse)? 'p':'a';
        top2 = (T::inverse)? 'o':'b';
        objA = 'A'; objB = 'B';
        hp = {
            'j', 'k', 'a', 'e',
            'f', 'g', 'h', 'i',
            'b', 'c', 'd', 'l',
            'm', 'n', 'o', 'p'};
        if (T::inverse) {
            arr = new T_base[size]
                {'p', 'k', 'o', 'j',
                'f', 'm', 'n', 'i',
                'b', 'c', 'd', 'l',
                'g', 'a', 'h', 'e'};
        } else {
            arr = new T_base[size]
                {'a', 'b', 'g', 'e',
                'c', 'j', 'h', 'i',
                'k', 'f', 'd', 'l',
                'm', 'n', 'o', 'p'};
        }
    }

    // INTEGER Case
    template<class Q = T_main>
    ENABLE_IF(
        (std::is_same<Q, Heap<INTEGER, false>>::value) ||
        (std::is_same<Q, Heap<INTEGER,  true>>::value)
    , void)
    initialize_dependent() {
        size = 10;
        top1 = (T::inverse)? 10:1;
        top2 = (T::inverse)?  9:2;
        objA = -1; objB = -2;
        hp = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        if (T::inverse) {
            arr = new T_base[size]{10, 9, 7, 8, 5, 6, 3, 1, 4, 2};
        } else {
            arr = new T_base[size]{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        }
    }

    // User Defined Data Type for test Case
    template<class Q = T_main>
    ENABLE_IF(
        (std::is_same<Q, Heap<UDTfT, false,        ComparatorClass>>::value) ||
        (std::is_same<Q, Heap<UDTfT,  true, InverseComparatorClass>>::value)
    , void)
    initialize_dependent() {
        size = 8;
        (T::inverse)? top1.set(8, 'h', 12.0):top1.set(1, 'a', 1.5);
        (T::inverse)? top2.set(7, 'g', 10.5):top2.set(2, 'b', 3.0);
        objA.set(-1, 'A', 3.5); objB.set(-2, 'B', 6.5);
        arr = new T_base[size];
        T_base *arr_ = new T_base[size];
        UDTfT obj;
        for (INTEGER i = 0; i < size; ++i) {
            obj.set(i + 1, 'a' + i, static_cast<double>(i + 1) * 1.5);
            hp.add(obj);
            arr_[i] = arr[i] = obj;
        }
        if (T::inverse) {
            arr[0] = arr_[7]; arr[1] = arr_[6];
            arr[2] = arr_[5]; arr[3] = arr_[3];
            arr[4] = arr_[2]; arr[5] = arr_[1];
            arr[6] = arr_[4]; arr[7] = arr_[0];
        }
        delete [] arr_;
    }

    // Other Case
    template<class Q = T_main>
    ENABLE_IF(
      !(std::is_same<Q, Heap<INTEGER, false  /*                 */>>::value) &&
      !(std::is_same<Q, Heap<INTEGER,  true  /*                 */>>::value) &&
      !(std::is_same<Q, Heap<   char, false  /*                 */>>::value) &&
      !(std::is_same<Q, Heap<   char,  true  /*                 */>>::value) &&
      !(std::is_same<Q, Heap<  UDTfT, false,       ComparatorClass>>::value) &&
      !(std::is_same<Q, Heap<  UDTfT,  true, InverseComparatorClass>>::value)
    , void)
    initialize_dependent() {
        throw exception(
            "Unrecognized type for Heap Test: " +
            std::string(typeid(Q()).name()));
    }

    void initialize_independent() { ; }
    void SetUp() override {
        initialize_dependent();
        initialize_independent();
    }
    void TearDown() override { delete [] arr; }
};
TYPED_TEST_SUITE_P(HeapTest);

TYPED_TEST_P(HeapTest, isHeapTest) {
    EXPECT_TRUE(this -> hp.isHeap());
}
TYPED_TEST_P(HeapTest, sizeTest) {
    EXPECT_EQ(this -> hp.size(), this -> size);
}
TYPED_TEST_P(HeapTest, topTest) {
    EXPECT_EQ(this -> hp.top(), this -> top1);
}
TYPED_TEST_P(HeapTest, addTest) {
    this -> hp.add(this -> objA);
    if (TypeParam::inverse) {
        EXPECT_EQ(this -> hp.top(), this -> top1);
    } else {
        EXPECT_EQ(this -> hp.top(), this -> objA);
    }
    EXPECT_EQ(this -> hp.size(), this -> size + 1);
}
TYPED_TEST_P(HeapTest, popTest) {
    EXPECT_EQ(this -> hp.pop(), this -> top1);
    EXPECT_EQ(this -> hp.pop(), this -> top2);
    EXPECT_EQ(this -> hp.size(), this -> size - 2);
}
TYPED_TEST_P(HeapTest, removeTest) {
    EXPECT_TRUE(this -> hp.find(this -> top2));
    EXPECT_TRUE(this -> hp.remove(this -> top2));
    EXPECT_EQ(this -> hp.find(this -> top2), -1);
    EXPECT_EQ(this -> hp.size(), this -> size - 1);
}
TYPED_TEST_P(HeapTest, iteratorTest) {
    INTEGER index = 0;
    for (typename TypeParam::base_ elem : this -> hp) {
        EXPECT_EQ(elem, this -> arr[index++]);
    }
}
TYPED_TEST_P(HeapTest, iteratorInvalidationTest) {
    typename TypeParam::main_::iterator ii = this -> hp.begin();
    this -> hp.add(this -> top1);
    EXPECT_THROW(ii != this -> hp.end(), self::exception);
}

REGISTER_TYPED_TEST_SUITE_P(HeapTest,
    isHeapTest,
    sizeTest,
    topTest,
    addTest,
    popTest,
    removeTest,
    iteratorTest,
    iteratorInvalidationTest
);

using HeapTestTypes = ::testing::Types<
    Encapsulation<
        Heap<INTEGER, false>, INTEGER, false>,
    Encapsulation<
        Heap<INTEGER, true>, INTEGER, true>,
    Encapsulation<
        Heap<char, false >, char, false >,
    Encapsulation<
        Heap<char, true >, char, true>,
    Encapsulation<
        Heap<UDTfT, false, ComparatorClass>, UDTfT, false, ComparatorClass>,
    Encapsulation<
        Heap<UDTfT, true, InverseComparatorClass>,
        UDTfT, true, InverseComparatorClass>
>;
INSTANTIATE_TYPED_TEST_SUITE_P(HeapTestPrefix, HeapTest, HeapTestTypes);

}  // namespace self
