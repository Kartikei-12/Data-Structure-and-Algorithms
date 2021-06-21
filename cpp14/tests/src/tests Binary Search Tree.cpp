// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Testing Binary Search Tree

#include "gtest/gtest.h"
#include "Utility/Utility.hpp"
#include "BinarySearchTree/BinarySearchTree.hpp"
#include "HelpTest/HelpTest.hpp"

namespace self
{

template <typename T>
class BinarySearchTreeTest : public ::testing::Test
{
public:
    INTEGER size;
    T_main bst;
    T_base root; T_base objA;
    
    // INTEGER Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, BinarySearchTree<INTEGER>), void)
    initialize_dependent() {
        size = 15; root = 8; objA = 16;
        bst = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
    }

    // char Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, BinarySearchTree<char>), void)
    initialize_dependent() {
        size = 7; root = 'd'; objA = 'h';
        bst = {'d', 'b', 'f', 'a', 'c', 'e', 'g'};
    }

    // User Defined Data Type for test Case
    template<class Q = T_main>
    ENABLE_IF(
        (std::is_same<Q, BinarySearchTree<UDTfT, ComparatorClass>>::value)
    , void)
    initialize_dependent() {
        size = 21; root.set(15 + 1, 'a', 2.0); objA.set(40, ' ', 5.0);

        bst.add(UDTfT(15 + 1, 'a', 2.0)); bst.add(UDTfT( 7 + 1, 'a', 2.0)); bst.add(UDTfT(23 + 1, 'a', 2.0));
        bst.add(UDTfT( 4 + 1, 'a', 2.0)); bst.add(UDTfT(12 + 1, 'a', 2.0)); bst.add(UDTfT(20 + 1, 'a', 2.0));
        bst.add(UDTfT(28 + 1, 'a', 2.0)); bst.add(UDTfT( 2 + 1, 'a', 2.0)); bst.add(UDTfT( 6 + 1, 'a', 2.0));
        bst.add(UDTfT(10 + 1, 'a', 2.0)); bst.add(UDTfT(14 + 1, 'a', 2.0)); bst.add(UDTfT(18 + 1, 'a', 2.0));
        bst.add(UDTfT(22 + 1, 'a', 2.0)); bst.add(UDTfT( 1 + 1, 'a', 2.0)); bst.add(UDTfT( 3 + 1, 'a', 2.0));
        bst.add(UDTfT( 5 + 1, 'a', 2.0)); bst.add(UDTfT( 7 + 1, 'a', 2.0)); bst.add(UDTfT( 9 + 1, 'a', 2.0));
        bst.add(UDTfT(11 + 1, 'a', 2.0)); bst.add(UDTfT(13 + 1, 'a', 2.0)); bst.add(UDTfT(15 + 1, 'a', 2.0));        
    }

    // Other Case
    template<class Q = T_main>
    ENABLE_IF(
        !IS_SAME(Q, BinarySearchTree<INTEGER>) &&
        !IS_SAME(Q, BinarySearchTree<   char>) &&
        !(std::is_same<Q, BinarySearchTree<UDTfT, ComparatorClass>>::value)
    , void)
    initialize_dependent() {
        throw exception(
            "Unrecognized type for Binary Search Tree Test: " +
            std::string(typeid(Q()).name())
        );
    }

    void initialize_independent() { ; }
    void SetUp() override {
        initialize_dependent();
        initialize_independent();
    }
    void TearDown() override { ; }
};
TYPED_TEST_SUITE_P(BinarySearchTreeTest);

TYPED_TEST_P(BinarySearchTreeTest, sizeTest) {
    EXPECT_EQ(this -> bst.size(), this -> size);
}
TYPED_TEST_P(BinarySearchTreeTest, containsTest) {
    EXPECT_TRUE(this -> bst.contains(this -> root));
    EXPECT_FALSE(this -> bst.contains(this -> objA));
}

REGISTER_TYPED_TEST_SUITE_P(BinarySearchTreeTest,
    sizeTest,
    containsTest
);

using BinarySearchTreeTestTypes = ::testing::Types<
    Encapsulation<BinarySearchTree<INTEGER,            void>, INTEGER>,
    Encapsulation<BinarySearchTree<   char,            void>,    char>,
    Encapsulation<BinarySearchTree<  UDTfT, ComparatorClass>,   UDTfT>
>;
INSTANTIATE_TYPED_TEST_SUITE_P(BinarySearchTreeTestPrefix, BinarySearchTreeTest, BinarySearchTreeTestTypes);

}
