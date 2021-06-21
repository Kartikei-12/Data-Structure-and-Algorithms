project (Node_One_Child
    VERSION 1.0
    DESCRIPTION "Implementaion of Node class with one child in C++"
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(self::NodeOneChild ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
