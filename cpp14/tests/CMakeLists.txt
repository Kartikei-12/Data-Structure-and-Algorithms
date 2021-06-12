project(${CMAKE_PROJECT_NAME}_tests)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Prevent installation of GTest with the project
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(INSTALL_GMOCK OFF CACHE BOOL "" FORCE)

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
