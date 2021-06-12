project(examples)

add_executable(${PROJECT_NAME}_DynamicArray "Dynamic Array example.cpp")
target_link_libraries(${PROJECT_NAME}_DynamicArray self::DynamicArray)
