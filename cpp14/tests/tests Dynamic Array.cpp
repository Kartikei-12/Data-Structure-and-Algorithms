// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Testing Dynamic Array

#include <ostream>
#include "gtest/gtest.h"
#include "Utility_/Utility_.hpp"
#include "DynamicArray/DynamicArray.hpp"
#include "utility test.hpp"

namespace self
{

template <typename T>
class DynamicArrayTest : public ::testing::Test
{
public:
    T obj0; T obj1; T obj2; T obj3;
    T obj_1; T obj_2; T objA;
    T* arr;
    // All T object is independently defined because for same types T a, b placment,
    // may change meaning, for example pointer types
    INTEGER size, setIndex, largeIndex = 100, negativeIndex = -16;
    self::DynamicArray<T> da;

    // char Case
    template<class Q = T>
    ENABLE_IF(IS_SAME(Q, char))
    initialize_dependent() {
        obj0 = 'a'; obj1 = 'b'; obj2 = 'c'; obj3 = 'd';
        obj_2 = 'k'; obj_1 = 'l';  objA = 'n';
        size = 12; setIndex = 5;
        da = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
        arr = new T[size];
        T _arr[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'};
        std::copy(_arr, _arr + size, arr);
    }

    // INTEGER Case
    template<class Q = T>
    ENABLE_IF(IS_SAME(Q, INTEGER))
    initialize_dependent() {
        obj0 = 1; obj1 = 2; obj2 = 3; obj3 = 4;
        obj_2 = 9; obj_1 = 10; objA = 12;
        size = 10; setIndex = 8;
        da = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        arr = new T[size];
        T _arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::copy(_arr, _arr + size, arr);
    }

    // UDTfT Case
    template<class Q = T>
    ENABLE_IF(IS_SAME(Q, UDTfT))
    initialize_dependent() {
        obj0.set(1, 'a', 2.5); obj1.set(2, 'b', 5.0);
        obj2.set(3, 'c', 7.5); obj3.set(4, 'd', 10.0);
        obj_2.set(7, 'g', 17.5); obj_1.set(8, 'h', 20.0);
        objA.set(51, 'z', 16.0);
        size = 8; setIndex = 5;
        arr = new T[size];
        for (INTEGER i = 0; i < size; ++i) {
            UDTfT obbj(i + 1, 'a' + i, double(double(i + 1) * 2.5));
            da.append(obbj);
            arr[i] = obbj;
        }
    }

    // Other Case
    template<class Q = T>
    ENABLE_IF(!IS_SAME(Q, char) && !IS_SAME(Q, INTEGER) && !IS_SAME(Q, UDTfT))
    initialize_dependent() {
        throw exception(
            "Unrecognized type for Dynamic Array Test:" + 
            std::string(typeid(Q()).name())
        );
    }

    void initialize_independent() { ; }
    void SetUp() override { initialize_dependent(); initialize_independent(); }
    void TearDown() override { da._delete(); }
};
TYPED_TEST_SUITE_P(DynamicArrayTest);

TYPED_TEST_P(DynamicArrayTest, constructorExceptionTest) {
    EXPECT_THROW(self::DynamicArray<int>(-1), exception);
}
TYPED_TEST_P(DynamicArrayTest, SizeTest) {
    EXPECT_EQ(this -> da.size(), this -> size);
}
// TYPED_TEST_P(DynamicArrayTest, isEmptyTest) {
//     EXPECT_EQ(this -> da.isEmpty(), this -> isEmpty);
// }
TYPED_TEST_P (DynamicArrayTest, getTest) {
    EXPECT_EQ(this -> da.get(0), this -> obj0);
    EXPECT_EQ(this -> da.get(2), this -> obj2);
}
TYPED_TEST_P (DynamicArrayTest, getSquareBracketTest) {
    EXPECT_EQ(this -> da[0], this -> obj0);
    EXPECT_EQ(this -> da[2], this -> obj2);
}
TYPED_TEST_P (DynamicArrayTest, getNegativeIndexTest) {
    EXPECT_EQ(this -> da.get(-1), this -> obj_1);
    EXPECT_EQ(this -> da.get(-2), this -> obj_2);
}
TYPED_TEST_P (DynamicArrayTest, getInvalidIndexTest) {
    EXPECT_THROW(this -> da.get(this -> negativeIndex), exception);
    EXPECT_THROW(this -> da.get(this -> largeIndex), exception);   
}
TYPED_TEST_P (DynamicArrayTest, setTest) {
    this -> da.set(this -> objA, this -> setIndex);
    EXPECT_EQ(this -> da.get(this -> setIndex), this -> objA);
    EXPECT_THROW(this -> da.set(this -> objA, this -> negativeIndex), exception);
    EXPECT_THROW(this -> da.set(this -> objA, this -> largeIndex), exception);
}
TYPED_TEST_P (DynamicArrayTest, addTest) {
    this -> da.add(this -> objA, (this -> size) - 1);
    EXPECT_EQ(this -> da.get((this -> size) - 1), this -> objA);
    EXPECT_EQ(this -> da.get(this -> size), this -> obj_1);
    EXPECT_THROW(this -> da.set(this -> objA, this -> negativeIndex), exception);
    EXPECT_THROW(this -> da.set(this -> objA, this -> largeIndex), exception);
}
TYPED_TEST_P (DynamicArrayTest, findTest) {
    EXPECT_EQ(this -> da.find(this -> obj1), 01);
    EXPECT_EQ(this -> da.find(this -> objA), -1);
    EXPECT_TRUE(this -> da.contains(this -> obj2));
    EXPECT_FALSE(this -> da.contains(this -> objA));
}
TYPED_TEST_P (DynamicArrayTest, removeTest) {
    EXPECT_TRUE(this -> da.contains(this -> obj3));
    EXPECT_TRUE(this -> da.remove(this -> obj3));
    EXPECT_FALSE(this -> da.contains(this -> obj3));
}
TYPED_TEST_P (DynamicArrayTest, iteratorTest) {
    INTEGER ii = 0;
    for (TypeParam ele:this -> da) {
        ASSERT_EQ(ele, this -> arr[ii++]);
    }
}

REGISTER_TYPED_TEST_SUITE_P(
    DynamicArrayTest,
    constructorExceptionTest,
    SizeTest,
    // isEmptyTest,
    getTest,
    getSquareBracketTest,
    getNegativeIndexTest,
    getInvalidIndexTest,
    setTest,
    addTest,
    findTest,
    removeTest,
    iteratorTest
);

using DynamicArrayTypes = ::testing::Types<INTEGER, char, UDTfT>;
INSTANTIATE_TYPED_TEST_SUITE_P(DynamicArrayTestPrefix, DynamicArrayTest, DynamicArrayTypes);

#undef ENABLE_IF 
#undef IS_SAME

}
