project (Queue_
    VERSION 1.0
    DESCRIPTION "My Implementaion of Queue in C++"
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(self::Queue ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} INTERFACE
    self::Utility
    self::DynamicArray
    self::SinglyLinkedList
)
