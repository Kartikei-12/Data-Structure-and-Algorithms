// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Testing Queue

#include "gtest/gtest.h"
#include "Utility/Utility.hpp"
#include "Queue/Queue.hpp"
#include "HelpTest/HelpTest.hpp"

namespace self
{

template <typename T>
class QueueTest : public ::testing::Test
{
public:
    T_base objA; T_base objB;
    T_base* arr;
    // All T object is independently defined because for same types T a, b placment,
    // may change meaning, for example pointer types
    T_main que;
    INTEGER size;

    // char Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, QueueArray<char>) || IS_SAME(Q, QueueLinkedList<char>))
    initialize_dependent() {
        objA = 'n'; objB = 'p';
        T_base _arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
        size = sizeof(_arr) / sizeof(_arr[0]);
        arr = new T_base[size];
        std::copy(_arr, _arr + size, arr);
    }

    // INTEGER Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, QueueArray<INTEGER>) || IS_SAME(Q, QueueLinkedList<INTEGER>))
    initialize_dependent() {
        objA = 12; objB = 16;
        T_base _arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        size = sizeof(_arr) / sizeof(_arr[0]);
        arr = new T_base[size];
        std::copy(_arr, _arr + size, arr);
    }

    // UDTfT Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, QueueArray<UDTfT>) || IS_SAME(Q, QueueLinkedList<UDTfT>))
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
        !IS_SAME(Q, QueueArray<   char>) && !IS_SAME(Q, QueueLinkedList<   char>) &&
        !IS_SAME(Q, QueueArray<  UDTfT>) && !IS_SAME(Q, QueueLinkedList<  UDTfT>) &&
        !IS_SAME(Q, QueueArray<INTEGER>) && !IS_SAME(Q, QueueLinkedList<INTEGER>)
    )
    initialize_dependent() {
        throw exception(
            "Unrecognized type for Queue Test:" +
            std::string(typeid(Q()).name())
        );
    }

    void initialize_independent() { ; }
    void SetUp() override { initialize_dependent(); initialize_independent(); }
    void TearDown() override { ; }
};
TYPED_TEST_SUITE_P(QueueTest);

TYPED_TEST_P(QueueTest, sizeTest) {
    EXPECT_EQ(this -> que.size(), 0);
    this -> que.push(this -> objA);
    EXPECT_EQ(this -> que.size(), 1);
    this -> que.push(this -> objB);
    EXPECT_EQ(this -> que.size(), 2);
}
TYPED_TEST_P (QueueTest, push_popTest) {
    this -> que.push(this -> objA);
    this -> que.push(this -> objB);
    EXPECT_EQ(this -> que.top(), this -> objA);
    EXPECT_EQ(this -> que.pop(), this -> objA);
    EXPECT_EQ(this -> que.top(), this -> objB);
}
TYPED_TEST_P (QueueTest, rotationTest) {
    this -> que.push(this -> objA);
    this -> que.push(this -> objB);
    for (INTEGER i = 0; i < (this -> size - 2); ++i) {
        this -> que.push(this -> arr[i]);
    }
    EXPECT_EQ(this -> que.pop(), this -> objA);
    EXPECT_EQ(this -> que.pop(), this -> objB);
    this -> que.push(this -> arr[this -> size - 2]);
    this -> que.push(this -> arr[this -> size - 1]);
    INTEGER index = 0;
    for (typename TypeParam::base_ elem : this -> que) {
        EXPECT_EQ(elem, this -> arr[index++]);
    }
}
TYPED_TEST_P (QueueTest, iteratorTest) {
    INTEGER index = 0;
    for (INTEGER i = 0; i < this -> size; ++i) {
        this -> que.push(this -> arr[i]);
    }
    for (typename TypeParam::base_ elem : this -> que) {
        EXPECT_EQ(elem, this -> arr[index++]);
    }
}

REGISTER_TYPED_TEST_SUITE_P(
    QueueTest,
    sizeTest,
    push_popTest,
    rotationTest,
    iteratorTest
);

using QueueTestTypes = ::testing::Types<
    Encapsulation<     QueueArray<INTEGER>, INTEGER>,
    Encapsulation<QueueLinkedList<INTEGER>, INTEGER>,
    Encapsulation<     QueueArray<   char>,    char>,
    Encapsulation<QueueLinkedList<   char>,    char>,
    Encapsulation<     QueueArray<  UDTfT>,   UDTfT>,
    Encapsulation<QueueLinkedList<  UDTfT>,   UDTfT>
>;
INSTANTIATE_TYPED_TEST_SUITE_P(QueueTestPrefix, QueueTest, QueueTestTypes);

}
