project (Binary_Search_Tree
    VERSION 1.0
    DESCRIPTION "My Implementaion of Binary Search Tree in C++"
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(self::BinarySearchTree ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} INTERFACE
    self::NodeTwoChild
    self::BinaryTree
    self::Utility
)
