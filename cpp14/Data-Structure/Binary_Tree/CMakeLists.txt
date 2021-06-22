project (Binary_Tree
    VERSION 1.0
    DESCRIPTION "My Binary Tree Interface in C++"
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(self::BinaryTree ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} INTERFACE
    self::Stack
    self::Queue
    self::Utility
)

add_subdirectory(Binary_Search_Tree)
