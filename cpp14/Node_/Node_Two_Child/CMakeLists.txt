project (Node_Two_Child
    VERSION 1.0
    DESCRIPTION "Implementaion of Node class with TWO child in C++"
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(self::NodeTwoChild ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
