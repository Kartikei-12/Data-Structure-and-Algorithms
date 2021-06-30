/**
 * @headerfile HelpTest.hpp
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Utilities to help in testing.
 * @author Kartikei Mittal
*/

#pragma once
#ifndef __self_HelpTest
#define __self_HelpTest

#include <iostream>
#include "gtest/gtest.h"

/**
 * @namespace self
 * @brief Project Namespace.
*/
namespace self {
/**
 * @class UDTft
 * @brief User Defined Data Type for Testing.
*/
class UDTfT {
    int a; /// int a
    char b; /// char b
    double c; /// char c
public:
    /// Counstructor
    UDTfT(int a_ = 0, char b_ = ' ', double c_ = 1.5);
    /// Copy Counstructor
    UDTfT(const UDTfT& other);
    /**
     * @brief Setter method.
     * @param a_ Integer
     * @param b_ Chracter
     * @param c_ Double
    */
    void set(int a_, char b_, double c_);
    /**
     * @brief Addition + operator overload.
     * @param first First element
     * @param other Second Element
    */
    friend UDTfT operator+(const UDTfT& first, const int other);
    /**
     * @brief Equality == operator overload.
     * @param first First element
     * @param other Second Element
    */
    friend bool operator==(const UDTfT& first, const UDTfT& other);
    /**
     * @brief Inequality != operator overload.
     * @param first First element
     * @param other Second Element
    */
    friend bool operator!=(const UDTfT& first, const UDTfT& other);
    /// Comparator class
    friend struct ComparatorClass;
    /// Inverse Comparator class
    friend struct InverseComparatorClass;
    /**
     * @brief Put to << operator overload.
     * @param os ostream object
     * @param ob Data
    */
    friend std::ostream& operator<<(std::ostream& os, const UDTfT& ob);
};

/**
 * @class ComparatorClass
 * @brief Comparator class for user defined type.
*/
struct ComparatorClass {
    /**
     * @brief Operator () overload
     * @param A First user defined type
     * @param B Second user defined type
    */
    int operator()(UDTfT A, UDTfT B);
};
/**
 * @class InverseComparatorClass
 * @brief Inverse Comparator class for user defined type.
*/
struct InverseComparatorClass {
    /**
     * @brief Operator () overload
     * @param A First user defined type
     * @param B Second user defined type
    */
    int operator()(UDTfT A, UDTfT B);
};

/**
 * @class Encapsulation
 * @brief Class used to package types and data for GoogleTest Type Parameterized Test.
 * @tparam A Primary type
 * @tparam B Secondary type
 * @tparam inverse_ Wheather to inverse comparator
 * @tparam comparator_ Coustom comparatoe
*/
template<typename A, typename B, bool inverse_ = false, typename comparator_ = void>
struct Encapsulation {
    typedef A main_;
    typedef B base_;
    static const bool inverse = inverse_;
    typedef comparator_ CompClass;
};

#define TestTypes ::testing::Types<INTEGER, char, UDTfT>
#define T_main typename T::main_
#define T_base typename T::base_

class ConfigurableEventListener : public testing::TestEventListener {
protected:
    TestEventListener* eventListener;
    bool showTestCases;
    bool showTestNames;
    bool showSuccesses;
    bool showInlineFailures;
    bool showEnvironment;
public:
    explicit ConfigurableEventListener(
        TestEventListener* theEventListener,
        bool a, bool b, bool c, bool d, bool e
    );
    virtual ~ConfigurableEventListener();
    virtual void OnTestProgramStart(const testing::UnitTest& unit_test);
    virtual void OnTestIterationStart(const testing::UnitTest& unit_test, int iteration);
    virtual void OnEnvironmentsSetUpStart(const testing::UnitTest& unit_test);
    virtual void OnEnvironmentsSetUpEnd(const testing::UnitTest& unit_test);
    virtual void OnTestCaseStart(const testing::TestCase& test_case);
    virtual void OnTestStart(const testing::TestInfo& test_info);
    virtual void OnTestPartResult(const testing::TestPartResult& result);
    virtual void OnTestEnd(const testing::TestInfo& test_info);
    virtual void OnTestCaseEnd(const testing::TestCase& test_case);
    virtual void OnEnvironmentsTearDownStart(const testing::UnitTest& unit_test);
    virtual void OnEnvironmentsTearDownEnd(const testing::UnitTest& unit_test);
    virtual void OnTestIterationEnd(const testing::UnitTest& unit_test, int iteration);
    virtual void OnTestProgramEnd(const testing::UnitTest& unit_test);
    virtual void OnTestSuiteStart(const testing::TestSuite& test_suite);
};

} // namespace self
#endif
