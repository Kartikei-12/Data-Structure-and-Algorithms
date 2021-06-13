// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Testing Heap

#include "gtest/gtest.h"
#include "Utility/Utility.hpp"
#include "Heap/Heap.hpp"
#include "HelpTest/HelpTest.hpp"

namespace self
{

template <typename T>
class HeapTest : public ::testing::Test
{
public:
    INTEGER size;
    typename T::main_ hp;

    // INTEGER Case
    template<class Q = typename T::main_>
    typename std::enable_if<std::is_same<Q, Heap<INTEGER, false>>::value, void>::type
    initialize_dependent() {
        size = 10;
        hp = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    }

    // Other Case
    template<class Q = typename T::main_>
    typename std::enable_if<!std::is_same<Q, Heap<INTEGER, false>>::value, void>::type
    initialize_dependent() {
        throw exception(std::string("Unrecognized type for Heap Test:") + std::string(typeid(Q()).name()));
    }

    void initialize_independent() { ; }
    void SetUp() override {
        initialize_dependent();
        initialize_independent();
    }
    void TearDown() override { hp._delete(); }
};
TYPED_TEST_SUITE_P(HeapTest);

TYPED_TEST_P(HeapTest, isEmptyTest) {
    EXPECT_FALSE(this -> hp.isEmpty());
}

REGISTER_TYPED_TEST_SUITE_P(HeapTest,
    isEmptyTest
);

using HeapTestTypes = ::testing::Types<
    Encapsulation<Heap<INTEGER, false>, INTEGER>
>;
INSTANTIATE_TYPED_TEST_SUITE_P(HeapTestPrefix, HeapTest, HeapTestTypes);

}
