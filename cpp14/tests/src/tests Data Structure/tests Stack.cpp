/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Stack tests.
 * @author Kartikei Mittal
*/

#include "gtest/gtest.h"
#include "Utility/Utility.hpp"
#include "Stack/Stack.hpp"
#include "HelpTest/HelpTest.hpp"

namespace self
{

template <typename T>
class StackTest : public ::testing::Test
{
public:
    T_base objA; T_base objB;
    T_base* arr; T_base top1;
    T_main st;
    INTEGER size;

    // INTEGER Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, StackArray<INTEGER>) || IS_SAME(Q, StackLinkedList<INTEGER>), void)
    initialize_dependent() {
        objA = 12; objB = 16; top1 = 1;
        T_base _arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        size = sizeof(_arr) / sizeof(_arr[0]);
        arr = new T_base[size];
        std::copy(_arr, _arr + size, arr);
    }

    // char Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, StackArray<char>) || IS_SAME(Q, StackLinkedList<char>), void)
    initialize_dependent() {
        objA = 'n'; objB = 'p';
        T_base _arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
        size = sizeof(_arr) / sizeof(_arr[0]);
        arr = new T_base[size];
        std::copy(_arr, _arr + size, arr);
    }

    // UDTfT Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, StackArray<UDTfT>) || IS_SAME(Q, StackLinkedList<UDTfT>), void)
    initialize_dependent() {
        objA.set(51, 'z', 16.0); objB.set(25, 'y', 14.0);
        size = 8;
        arr = new T_base[size];
        for (INTEGER i = 0; i < size; ++i) {
            UDTfT obbj;
            obbj.set(i + 1, 'a' + i, double(double(i + 1) * 2.5));
            arr[i] = obbj;
        }
    }

    // Other Case
    template<class Q = T_main>
    ENABLE_IF(
        !IS_SAME(Q, StackArray<   char>) && !IS_SAME(Q, StackLinkedList<   char>) &&
        !IS_SAME(Q, StackArray<  UDTfT>) && !IS_SAME(Q, StackLinkedList<  UDTfT>) &&
        !IS_SAME(Q, StackArray<INTEGER>) && !IS_SAME(Q, StackLinkedList<INTEGER>)
    , void)
    initialize_dependent() {
        throw exception(
            "Unrecognized type for Stack Test:" +
            std::string(typeid(Q()).name()));
    }

    void initialize_independent() { ; }
    void SetUp() override { initialize_dependent(); initialize_independent(); }
    void TearDown() override { delete [] arr; }
};
TYPED_TEST_SUITE_P(StackTest);

TYPED_TEST_P(StackTest, sizeTest) {
    EXPECT_EQ(this -> st.size(), 0);
    this -> st.push(this -> objA);
    EXPECT_EQ(this -> st.size(), 1);
    this -> st.push(this -> objB);
    EXPECT_EQ(this -> st.size(), 2);
}
TYPED_TEST_P (StackTest, pushTest) {
    this -> st.push(this -> objA);
    EXPECT_EQ(this -> st.top(), this -> objA);
    this -> st.push(this -> objB);
    EXPECT_EQ(this -> st.top(), this -> objB);
}
TYPED_TEST_P (StackTest, popTest) {
    this -> st.push(this -> objA);
    this -> st.push(this -> objB);
    EXPECT_EQ(this -> st.top(), this -> objB);
    EXPECT_EQ(this -> st.pop(), this -> objB);
    EXPECT_EQ(this -> st.pop(), this -> objA);
}
TYPED_TEST_P (StackTest, iteratorTest) {
    INTEGER index = 0;
    for (INTEGER i = 0; i < this -> size; ++i) {
        this -> st.push(this -> arr[i]);
    }
    for (typename TypeParam::base_ elem : this -> st) {
        ASSERT_EQ(elem, this -> arr[index++]);
    }
}

REGISTER_TYPED_TEST_SUITE_P(
    StackTest,
    sizeTest,
    pushTest,
    popTest,
    iteratorTest
);

using StackTestTypes = ::testing::Types<
    Encapsulation<     StackArray<INTEGER>, INTEGER>,
    Encapsulation<StackLinkedList<INTEGER>, INTEGER>,
    Encapsulation<     StackArray<   char>,    char>,
    Encapsulation<StackLinkedList<   char>,    char>,
    Encapsulation<     StackArray<  UDTfT>,   UDTfT>,
    Encapsulation<StackLinkedList<  UDTfT>,   UDTfT>
>;
INSTANTIATE_TYPED_TEST_SUITE_P(StackTestPrefix, StackTest, StackTestTypes);

} // namespace self
