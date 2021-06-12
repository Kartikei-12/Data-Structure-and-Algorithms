// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
#include "tests Dynamic Array.cpp"

using namespace testing;
class ConfigurableEventListener : public TestEventListener
{
protected: TestEventListener* eventListener;
public:
    bool showTestCases; // Show the names of each test case
    bool showTestNames; // Show the names of each test
    bool showSuccesses; // Show each success
    bool showInlineFailures; // Show each failure as it occurs. Also at the bottom after the full suite is run
    bool showEnvironment; // Show the setup of the global environment
    
    explicit ConfigurableEventListener(TestEventListener* theEventListener) : eventListener(theEventListener) {
        showTestCases = false;
        showTestNames = false;
        showSuccesses = false;
        showInlineFailures = true;
        showEnvironment = true;
    }

    virtual ~ConfigurableEventListener() { delete eventListener; }
    virtual void OnTestProgramStart(const UnitTest& unit_test) {
        eventListener->OnTestProgramStart(unit_test);
    }
    virtual void OnTestIterationStart(const UnitTest& unit_test, int iteration) {
        eventListener->OnTestIterationStart(unit_test, iteration);
    }
    virtual void OnEnvironmentsSetUpStart(const UnitTest& unit_test) {
        if(showEnvironment) {
            eventListener->OnEnvironmentsSetUpStart(unit_test);
        }
    }
    virtual void OnEnvironmentsSetUpEnd(const UnitTest& unit_test) {
        if(showEnvironment) {
            eventListener->OnEnvironmentsSetUpEnd(unit_test);
        }
    }
    virtual void OnTestCaseStart(const TestCase& test_case) {
        if(showTestCases) {
            eventListener->OnTestCaseStart(test_case);
        }
    }
    virtual void OnTestStart(const TestInfo& test_info) {
        if(showTestNames) {
            eventListener->OnTestStart(test_info);
        }
    }
    virtual void OnTestPartResult(const TestPartResult& result) {
        eventListener->OnTestPartResult(result);
    }
    virtual void OnTestEnd(const TestInfo& test_info) {
        if((showInlineFailures && test_info.result()->Failed()) || (showSuccesses && !test_info.result()->Failed())) {
            eventListener->OnTestEnd(test_info);
        }
    }
    virtual void OnTestCaseEnd(const TestCase& test_case) {
        if(showTestCases) {
            eventListener->OnTestCaseEnd(test_case);
        }
    }
    virtual void OnEnvironmentsTearDownStart(const UnitTest& unit_test) {
        if(showEnvironment) {
            eventListener->OnEnvironmentsTearDownStart(unit_test);
        }
    }
    virtual void OnEnvironmentsTearDownEnd(const UnitTest& unit_test) {
        if(showEnvironment) {
            eventListener->OnEnvironmentsTearDownEnd(unit_test);
        }
    }
    virtual void OnTestIterationEnd(const UnitTest& unit_test, int iteration) {
        eventListener->OnTestIterationEnd(unit_test, iteration);
    }   
    virtual void OnTestProgramEnd(const UnitTest& unit_test) {
        eventListener->OnTestProgramEnd(unit_test);
    }
};

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // remove the default listener
    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    auto default_printer = listeners.Release(listeners.default_result_printer());
    ConfigurableEventListener *listener = new ConfigurableEventListener(default_printer);
    listeners.Append(listener);
    return RUN_ALL_TESTS();
}