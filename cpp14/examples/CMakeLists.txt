project(examples)

add_executable(${PROJECT_NAME}_DynamicArray "Dynamic Array example.cpp")
target_link_libraries(${PROJECT_NAME}_DynamicArray self::DynamicArray)

add_executable(${PROJECT_NAME}_SinglyLinkedList "Singly Linked List example.cpp")
target_link_libraries(${PROJECT_NAME}_SinglyLinkedList self::SinglyLinkedList)
