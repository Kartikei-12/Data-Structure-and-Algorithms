/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Binary Search Tree tests.
 * @author Kartikei Mittal
*/

#include "gtest/gtest.h"
#include "Utility/Utility.hpp"
#include "BinarySearchTree/BinarySearchTree.hpp"
#include "HelpTest/HelpTest.hpp"

namespace self {

template <typename T>
class BinarySearchTreeTest : public ::testing::Test {
public:
    INTEGER size, height;
    T_main bst;
    T_base root; T_base obj_1;
    T_base objA; T_base base;
    T_base* pre; T_base* level;

    // INTEGER Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, BinarySearchTree<INTEGER>), void)
    initialize_dependent() {
        size = 15; height = 4;
        root = 8; base = 1;
        objA = 16; obj_1 = 15;
        bst = {8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
        pre =   new T_base[size]{8, 12, 14, 15, 13, 10, 11, 9, 4, 6, 7, 5, 2, 3, 1};
        level = new T_base[size]{8, 4, 12, 2, 6, 10, 14, 1, 3, 5, 7, 9, 11, 13, 15};
    }

    // char Case
    template<class Q = T_main>
    ENABLE_IF(IS_SAME(Q, BinarySearchTree<char>), void)
    initialize_dependent() {
        size = 7; height = 3;
        root = 'd'; base = 'a';
        objA = 'h'; obj_1 = 'g';
        bst = {'d', 'b', 'f', 'a', 'c', 'e', 'g'};
        pre =   new T_base[size]{'d', 'b', 'a', 'c', 'f', 'e', 'g'};
        level = new T_base[size]{'d', 'b', 'f', 'a', 'c', 'e', 'g'};
    }

    // User Defined Data Type for test Case
    template<class Q = T_main>
    ENABLE_IF(
        (std::is_same<Q, BinarySearchTree<UDTfT, ComparatorClass>>::value)
    , void)
    initialize_dependent() {
        size = 21; height = 5;
        root.set(15 + 1, 'a', 2.0); base.set(1, 'a', 2.0);
        objA.set(40, ' ', 5.0); obj_1.set(15, 'a', 2.0);

        bst.add(UDTfT(16, 'a', 2.0)); bst.add(UDTfT( 8, 'a', 2.0)); bst.add(UDTfT(20, 'a', 2.0));
        bst.add(UDTfT( 4, 'a', 2.0)); bst.add(UDTfT(12, 'a', 2.0)); bst.add(UDTfT(18, 'a', 2.0));
        bst.add(UDTfT(21, 'a', 2.0)); bst.add(UDTfT( 2, 'a', 2.0)); bst.add(UDTfT( 6, 'a', 2.0));
        bst.add(UDTfT(10, 'a', 2.0)); bst.add(UDTfT(14, 'a', 2.0)); bst.add(UDTfT(17, 'a', 2.0));
        bst.add(UDTfT(19, 'a', 2.0)); bst.add(UDTfT( 1, 'a', 2.0)); bst.add(UDTfT( 3, 'a', 2.0));
        bst.add(UDTfT( 5, 'a', 2.0)); bst.add(UDTfT( 7, 'a', 2.0)); bst.add(UDTfT( 9, 'a', 2.0));
        bst.add(UDTfT(11, 'a', 2.0)); bst.add(UDTfT(13, 'a', 2.0)); bst.add(UDTfT(15, 'a', 2.0));
        pre = new T_base[size]{
            UDTfT(16, 'a', 2.0), UDTfT( 8, 'a', 2.0), UDTfT( 4, 'a', 2.0),
            UDTfT( 2, 'a', 2.0), UDTfT( 1, 'a', 2.0), UDTfT( 3, 'a', 2.0),
            UDTfT( 6, 'a', 2.0), UDTfT( 5, 'a', 2.0), UDTfT( 7, 'a', 2.0),
            UDTfT(12, 'a', 2.0), UDTfT(10, 'a', 2.0), UDTfT( 9, 'a', 2.0),
            UDTfT(11, 'a', 2.0), UDTfT(14, 'a', 2.0), UDTfT(13, 'a', 2.0),
            UDTfT(15, 'a', 2.0), UDTfT(20, 'a', 2.0), UDTfT(18, 'a', 2.0),
            UDTfT(17, 'a', 2.0), UDTfT(19, 'a', 2.0), UDTfT(21, 'a', 2.0)
        };
        level = new T_base[size]{
            UDTfT(16, 'a', 2.0), UDTfT( 8, 'a', 2.0), UDTfT(20, 'a', 2.0),
            UDTfT( 4, 'a', 2.0), UDTfT(12, 'a', 2.0), UDTfT(18, 'a', 2.0),
            UDTfT(21, 'a', 2.0), UDTfT( 2, 'a', 2.0), UDTfT( 6, 'a', 2.0),
            UDTfT(10, 'a', 2.0), UDTfT(14, 'a', 2.0), UDTfT(17, 'a', 2.0),
            UDTfT(19, 'a', 2.0), UDTfT( 1, 'a', 2.0), UDTfT( 3, 'a', 2.0),
            UDTfT( 5, 'a', 2.0), UDTfT( 7, 'a', 2.0), UDTfT( 9, 'a', 2.0),
            UDTfT(11, 'a', 2.0), UDTfT(13, 'a', 2.0), UDTfT(15, 'a', 2.0)
        };
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
    void TearDown() override { delete pre; delete level; }
};
TYPED_TEST_SUITE_P(BinarySearchTreeTest);

TYPED_TEST_P(BinarySearchTreeTest, sizeTest) {
    EXPECT_EQ(this -> bst.size(), this -> size);
}
TYPED_TEST_P(BinarySearchTreeTest, containsTest) {
    EXPECT_TRUE(this -> bst.contains(this -> root));
    EXPECT_TRUE(this -> bst.contains(this -> obj_1));
    EXPECT_FALSE(this -> bst.contains(this -> objA));
}
TYPED_TEST_P(BinarySearchTreeTest, heightTest) {
    EXPECT_EQ(this -> bst.height(), this -> height);
}
TYPED_TEST_P(BinarySearchTreeTest, addTest) {
    EXPECT_FALSE(this -> bst.contains(this -> objA));
    this -> bst.add(this -> objA);
    EXPECT_TRUE(this -> bst.contains(this -> objA));
}
TYPED_TEST_P(BinarySearchTreeTest, removeTest) {
    EXPECT_TRUE(this -> bst.contains(this -> obj_1));
    this -> bst.remove(this -> obj_1);
    EXPECT_FALSE(this -> bst.contains(this -> obj_1));
}
TYPED_TEST_P(BinarySearchTreeTest, inOrderIteratorTest) {
    INTEGER ii = 0;
    for (typename TypeParam::main_::iterator i = this -> bst.begin("IN ORDER"); i != this -> bst.end(); ++i, ++ii) {
        EXPECT_EQ(*i, ((this -> base) + ii));
    }
}
TYPED_TEST_P(BinarySearchTreeTest, preOrderIteratorTest) {
    INTEGER ii = 0;
    for (typename TypeParam::main_::iterator i = this -> bst.begin("PRE ORDER"); i != this -> bst.end(); ++i, ++ii) {
        EXPECT_EQ(*i, this -> pre[ii]);
    }
}
TYPED_TEST_P(BinarySearchTreeTest, postOrderIteratorTest) {
    INTEGER ii = 0;
    for (typename TypeParam::main_::iterator i = this -> bst.begin("POST ORDER"); i != this -> bst.end(); ++i, ++ii) {
        EXPECT_EQ(*i, this -> pre[this -> size - ii - 1]);
    }
}
TYPED_TEST_P(BinarySearchTreeTest, levelOrderIteratorTest) {
    INTEGER ii = 0;
    for (typename TypeParam::main_::iterator i = this -> bst.begin("LEVEL ORDER"); i != this -> bst.end(); ++i, ++ii) {
        EXPECT_EQ(*i, this -> level[ii]);
    }
}
TYPED_TEST_P(BinarySearchTreeTest, iteratorInvalidationTest) {
    typename TypeParam::main_::iterator ii = this -> bst.begin("IN ORDER");
    this -> bst.add(this -> obj_1);
    EXPECT_THROW(ii != this -> bst.end(), self::exception);
}

REGISTER_TYPED_TEST_SUITE_P(BinarySearchTreeTest,
    sizeTest,
    containsTest,
    heightTest,
    addTest,
    removeTest,
    inOrderIteratorTest,
    preOrderIteratorTest,
    postOrderIteratorTest,
    levelOrderIteratorTest,
    iteratorInvalidationTest
);

using BinarySearchTreeTestTypes = ::testing::Types<
    Encapsulation<BinarySearchTree<INTEGER,            void>, INTEGER>,
    Encapsulation<BinarySearchTree<   char,            void>,    char>,
    Encapsulation<BinarySearchTree<  UDTfT, ComparatorClass>,   UDTfT>
>;
INSTANTIATE_TYPED_TEST_SUITE_P(BinarySearchTreeTestPrefix, BinarySearchTreeTest, BinarySearchTreeTestTypes);

} // namespace self
