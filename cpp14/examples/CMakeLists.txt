project(examples)

macro(ADD_Example Class Name_)
    add_executable(${PROJECT_NAME}_${Class} "${Name_} example.cpp")
    target_link_libraries(${PROJECT_NAME}_${Class} self::${Class})
endmacro(ADD_Example)

ADD_Example(DynamicArray "Dynamic Array")
ADD_Example(SinglyLinkedList "Singly Linked List")
ADD_Example(Heap "Heap")
ADD_Example(Stack "Stack")
ADD_Example(Queue "Queue")
