project (Dynamic_Array
    VERSION 1.0
    DESCRIPTION "My Implementaion of Dynamic Array in C++"
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(self::DynamicArray ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE
        ${PROJECT_SOURCE_DIR}/include
)