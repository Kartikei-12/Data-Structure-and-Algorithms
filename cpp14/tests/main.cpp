/**
 * @copyright Copyright (C) 2021 by Kartikei Mittal. All Rights MIT Licensed.
 * @brief GTest test runner with MODIFIED output.
 * @author Kartikei Mittal
*/

#include "gtest/gtest.h"
#include "HelpTest/HelpTest.hpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    testing::TestEventListeners& listeners = testing::
        UnitTest::GetInstance()->listeners();
    auto default_printer = listeners.Release(
        listeners.default_result_printer());
    auto *listener = new self::ConfigurableEventListener(
        default_printer,
        false, false, false, true, true);
    listeners.Append(listener);
    return RUN_ALL_TESTS();
}
