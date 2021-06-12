// @author: Kartikei Mittal
// @email: kartikeimittal@gmail.com
#include "tests Dynamic Array.cpp"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    // remove the default listener
    testing::TestEventListeners& listeners = testing::UnitTest::GetInstance()->listeners();
    auto default_printer = listeners.Release(listeners.default_result_printer());
    self::ConfigurableEventListener *listener = new self::ConfigurableEventListener(default_printer);
    listeners.Append(listener);
    return RUN_ALL_TESTS();
}