/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief Utilities to help in testing SOURCE.
 * @author Kartikei Mittal
*/

#include "HelpTest/HelpTest.hpp"

namespace self {

UDTfT::UDTfT(int a_/* = 0*/, char b_/* = ' '*/, double c_/* = 1.5*/) { set(a_, b_, c_); }
UDTfT::UDTfT(const UDTfT& other) { a = other.a; b = other.b; c = other.c; }
void UDTfT::set(int a_, char b_, double c_) { a = a_; b = b_; c = c_; }
UDTfT operator+(const UDTfT& first, const int other) {
    return UDTfT(first.a + other, first.b, first.c);
}
bool operator==(const UDTfT& first, const UDTfT& other) {
    return first.a == other.a && first.b == other.b && first.c == other.c;
}
bool operator!=(const UDTfT& first, const UDTfT& other) {
    return first.a != other.a || first.b != other.b || first.c != other.c;
}
std::ostream& operator<<(std::ostream& os, const UDTfT& ob) {
    os << "(" << ob.a << ", " << ob.b << ", " << ob.c << ")";
    return os;
}
int ComparatorClass::operator()(UDTfT A, UDTfT B) {
    if (A.a == B.a) { return 0; }
    return (A.a < B.a)? 1 : -1;
}
int InverseComparatorClass::operator()(UDTfT A, UDTfT B) {
    if (A.a == B.a) { return 0; }
    return (A.a < B.a)? -1 : 1;
}
// ----------------------------------------------------------------
ConfigurableEventListener::ConfigurableEventListener(
    TestEventListener* theEventListener,
    bool a, bool b, bool c, bool d, bool e
) : eventListener(theEventListener),
    showTestCases(a), showTestNames(b),
    showSuccesses(c), showInlineFailures(d),
    showEnvironment(e)
{ ; }
ConfigurableEventListener::~ConfigurableEventListener() { delete eventListener; }
void ConfigurableEventListener::OnTestProgramStart(const testing::UnitTest& unit_test) {
    eventListener -> OnTestProgramStart(unit_test);
}
void ConfigurableEventListener::OnTestIterationStart(const testing::UnitTest& unit_test, int iteration) {
    eventListener->OnTestIterationStart(unit_test, iteration);
}
void ConfigurableEventListener::OnEnvironmentsSetUpStart(const testing::UnitTest& unit_test) {
    if (showEnvironment) {
        eventListener -> OnEnvironmentsSetUpStart(unit_test);
    }
}
void ConfigurableEventListener::OnEnvironmentsSetUpEnd(const testing::UnitTest& unit_test) {
    if (showEnvironment) {
        eventListener -> OnEnvironmentsSetUpEnd(unit_test);
    }
}
void ConfigurableEventListener::OnTestCaseStart(const testing::TestCase& test_case) {
    if (showTestCases) {
        eventListener -> OnTestCaseStart(test_case);
    }
}
void ConfigurableEventListener::OnTestStart(const testing::TestInfo& test_info) {
    if (showTestNames) {
        eventListener -> OnTestStart(test_info);
    }
}
void ConfigurableEventListener::OnTestPartResult(const testing::TestPartResult& result) {
    eventListener -> OnTestPartResult(result);
}
void ConfigurableEventListener::OnTestEnd(const testing::TestInfo& test_info) {
    if ((showInlineFailures && test_info.result()->Failed()) || (showSuccesses && !test_info.result()->Failed())) {
        eventListener -> OnTestEnd(test_info);
    }
}
void ConfigurableEventListener::OnTestCaseEnd(const testing::TestCase& test_case) {
    if (showTestCases) {
        eventListener -> OnTestCaseEnd(test_case);
    }
}
void ConfigurableEventListener::OnEnvironmentsTearDownStart(const testing::UnitTest& unit_test) {
    if (showEnvironment) {
        eventListener -> OnEnvironmentsTearDownStart(unit_test);
    }
}
void ConfigurableEventListener::OnEnvironmentsTearDownEnd(const testing::UnitTest& unit_test) {
    if (showEnvironment) {
        eventListener -> OnEnvironmentsTearDownEnd(unit_test);
    }
}
void ConfigurableEventListener::OnTestIterationEnd(const testing::UnitTest& unit_test, int iteration) {
    eventListener -> OnTestIterationEnd(unit_test, iteration);
}
void ConfigurableEventListener::OnTestProgramEnd(const testing::UnitTest& unit_test) {
    eventListener -> OnTestProgramEnd(unit_test);
}
void ConfigurableEventListener::OnTestSuiteStart(const testing::TestSuite& test_suite) {
    std::cout << "[----------] " << test_suite.name() << std::endl;
    std::cout << "             "
                << test_suite.total_test_count() << " tests, "
                << test_suite.type_param() << std::endl;
}

} // namespace self
