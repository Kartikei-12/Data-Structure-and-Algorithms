# Sub Project, Your Class
project (Dynamic_Array
    VERSION 1.0
    DESCRIPTION "My Implementaion of Dynamic Array in C++"
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE) # Initiating your library as header only(INTERFACE)
add_library(self::DynamicArray ALIAS ${PROJECT_NAME}) # Add alias, seprate actual and what others use 

target_include_directories(${PROJECT_NAME} # Tell where to find actual code
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
target_link_libraries(${PROJECT_NAME} # Dependencies
    INTERFACE self::Utility
)
