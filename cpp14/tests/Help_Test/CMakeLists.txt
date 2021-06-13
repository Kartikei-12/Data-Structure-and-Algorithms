project (HelpTest
    VERSION 1.0
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} src/HelpTest.cpp)
add_library(self::HelpTest ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME}
    PUBLIC gtest
)
