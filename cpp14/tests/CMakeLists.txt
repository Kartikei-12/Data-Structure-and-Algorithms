project(${CMAKE_PROJECT_NAME}_tests)

add_subdirectory(googletest)
file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false "tests *.cpp" "utility test.cpp")
add_executable(${PROJECT_NAME} ${TEST_SOURCES} main.cpp)

add_test(NAME ${PROJECT_NAME}_DynamicArray COMMAND ${PROJECT_NAME} "--gtest_filter=*DynamicArrayTest*")
target_link_libraries(${PROJECT_NAME} PUBLIC
    self::DynamicArray
    self::Utility
    gtest
)

add_custom_command(
    TARGET ${PROJECT_NAME}
    COMMENT "Running tests"
    POST_BUILD
    COMMAND ${PROJECT_NAME}
)
