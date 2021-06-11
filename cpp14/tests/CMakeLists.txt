project(${CMAKE_PROJECT_NAME}_tests)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false "tests *.cpp")
add_executable(${PROJECT_NAME} ${TEST_SOURCES} main.cpp)

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC self::DynamicArray gtest)
