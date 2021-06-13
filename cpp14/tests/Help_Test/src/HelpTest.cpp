// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
// Some Utility for testing purpose source

#include "HelpTest/HelpTest.hpp"

namespace self
{

UDTfT::UDTfT(int a_/* = 0*/, char b_/* = ' '*/, double c_/* = 1.5*/) { set(a_, b_, c_); }
UDTfT::UDTfT(const UDTfT& other) { a = other.a; b = other.b; c = other.c; }
void UDTfT::set(int a_, char b_, double c_) { a = a_; b = b_; c = c_; }
bool operator==(const UDTfT& first, const UDTfT& other) {
    return 
        first.a == other.a &&
        first.b == other.b &&
        first.c == other.c ;
}
bool operator!=(const UDTfT& first, const UDTfT& other) {
    return
        first.a != other.a ||
        first.b != other.b ||
        first.c != other.c ;
}

ConfigurableEventListener::ConfigurableEventListener(TestEventListener* theEventListener) {
    eventListener = theEventListener;
    showTestCases = false;
    showTestNames = false;
    showSuccesses = false;
    showInlineFailures = true;
    showEnvironment = true;
}
ConfigurableEventListener::~ConfigurableEventListener() { delete eventListener; }
void ConfigurableEventListener::OnTestProgramStart(const UnitTest& unit_test) {
    eventListener->OnTestProgramStart(unit_test);
}
void ConfigurableEventListener::OnEnvironmentsSetUpStart(const UnitTest& unit_test) {
    if(showEnvironment) {
        eventListener->OnEnvironmentsSetUpStart(unit_test);
    }
}
void ConfigurableEventListener::OnEnvironmentsSetUpEnd(const UnitTest& unit_test) {
    if(showEnvironment) {
        eventListener->OnEnvironmentsSetUpEnd(unit_test);
    }
}
void ConfigurableEventListener::OnTestCaseStart(const TestCase& test_case) {
    if(showTestCases) {
        eventListener->OnTestCaseStart(test_case);
    }
}
void ConfigurableEventListener::OnTestStart(const TestInfo& test_info) {
    if(showTestNames) {
        eventListener->OnTestStart(test_info);
    }
}
void ConfigurableEventListener::OnTestPartResult(const TestPartResult& result) {
    eventListener->OnTestPartResult(result);
}
void ConfigurableEventListener::OnTestEnd(const TestInfo& test_info) {
    if((showInlineFailures && test_info.result()->Failed()) || (showSuccesses && !test_info.result()->Failed())) {
        eventListener->OnTestEnd(test_info);
    }
}
void ConfigurableEventListener::OnTestCaseEnd(const TestCase& test_case) {
    if(showTestCases) {
        eventListener->OnTestCaseEnd(test_case);
    }
}
void ConfigurableEventListener::OnEnvironmentsTearDownStart(const UnitTest& unit_test) {
    if(showEnvironment) {
        eventListener->OnEnvironmentsTearDownStart(unit_test);
    }
}
void ConfigurableEventListener::OnEnvironmentsTearDownEnd(const UnitTest& unit_test) {
    if(showEnvironment) {
        eventListener->OnEnvironmentsTearDownEnd(unit_test);
    }
}
void ConfigurableEventListener::OnTestProgramEnd(const UnitTest& unit_test) {
    eventListener->OnTestProgramEnd(unit_test);
}
void ConfigurableEventListener::OnTestIterationStart(const UnitTest& unit_test, int iteration) {
    eventListener->OnTestIterationStart(unit_test, iteration);
}
void ConfigurableEventListener::OnTestIterationEnd(const UnitTest& unit_test, int iteration) {
    eventListener->OnTestIterationEnd(unit_test, iteration);
}
void ConfigurableEventListener::OnTestSuiteStart(const TestSuite& test_suite) {
    std::cout << "[----------] Running "
        << test_suite.name() << " "
        << test_suite.type_param()
        << std::endl;
}

}
