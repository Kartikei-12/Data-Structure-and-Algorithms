// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Some Utility for testing purpose header

#ifndef __self_HelpTest
#define __self_HelpTest
#pragma once

#include "gtest/gtest.h"

namespace self
{

class UDTfT // User Defined Data Type for Testing
{
    int a; char b; double c;
public:
    UDTfT(int a_ = 0, char b_ = ' ', double c_ = 1.5);
    UDTfT(const UDTfT& other);
    void set(int a_, char b_, double c_);
    friend bool operator==(const UDTfT& first, const UDTfT& other);
    friend bool operator!=(const UDTfT& first, const UDTfT& other);
};

typedef testing::TestEventListener TestEventListener;
typedef testing::UnitTest UnitTest;
typedef testing::TestCase TestCase;
typedef testing::TestInfo TestInfo;
typedef testing::TestPartResult TestPartResult;
typedef testing::TestSuite TestSuite;
class ConfigurableEventListener : public testing::TestEventListener
{
protected:
    TestEventListener* eventListener;
    bool showTestCases; // Show the names of each test case
    bool showTestNames; // Show the names of each test
    bool showSuccesses; // Show each success
    bool showInlineFailures; // Show each failure as it occurs. Also at the bottom after the full suite is run
    bool showEnvironment; // Show the setup of the global environment

public:    
    explicit ConfigurableEventListener(TestEventListener* theEventListener);

    virtual ~ConfigurableEventListener();
    virtual void OnTestProgramStart(const UnitTest& unit_test);
    virtual void OnEnvironmentsSetUpStart(const UnitTest& unit_test);
    virtual void OnEnvironmentsSetUpEnd(const UnitTest& unit_test);
    virtual void OnTestCaseStart(const TestCase& test_case);
    virtual void OnTestStart(const TestInfo& test_info);
    virtual void OnTestPartResult(const TestPartResult& result);
    virtual void OnTestEnd(const TestInfo& test_info);
    virtual void OnTestCaseEnd(const TestCase& test_case);
    virtual void OnEnvironmentsTearDownStart(const UnitTest& unit_test);
    virtual void OnEnvironmentsTearDownEnd(const UnitTest& unit_test);
    virtual void OnTestProgramEnd(const UnitTest& unit_test);
    virtual void OnTestIterationStart(const UnitTest& unit_test, int iteration);
    virtual void OnTestIterationEnd(const UnitTest& unit_test, int iteration);
    virtual void OnTestSuiteStart(const TestSuite& test_suite);
};

#define ENABLE_IF(condition) typename std::enable_if<condition>::type 
#define IS_SAME(a, b) std::is_same<a, b>::value
#define TestTypes ::testing::Types<INTEGER, char, UDTfT>

}

#endif
