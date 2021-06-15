project(${CMAKE_PROJECT_NAME}_tests)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Prevent installation of GTest with the project
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(INSTALL_GMOCK OFF CACHE BOOL "" FORCE)
set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)

add_subdirectory(googletest)
add_subdirectory(Help_Test)

# Seprate executable for Different Structure
macro(Test_Macro DStructure File Dependencies Count)
    add_executable(${PROJECT_NAME}_${DStructure} "src/${File}" main.cpp)
    target_link_libraries(${PROJECT_NAME}_${DStructure} PUBLIC
        ${Dependencies}
        self::${DStructure}
        self::Utility
        self::HelpTest
        gtest
    )
    foreach(i RANGE 0 ${Count})
        add_test(
            NAME ${PROJECT_NAME}_${DStructure}${i}
            COMMAND ${PROJECT_NAME}_${DStructure} --gtest_filter=*${DStructure}Test/${i}*
        )
    endforeach(i)
    add_custom_command(
        TARGET ${PROJECT_NAME}_${DStructure}
        COMMENT "Running tests"
        POST_BUILD
        COMMAND ${PROJECT_NAME}_${DStructure}
    )
endmacro(Test_Macro)

Test_Macro(DynamicArray "tests Dynamic Array.cpp" "" 2)
Test_Macro(SinglyLinkedList "tests Singly Linked List.cpp" "" 2)
Test_Macro(Heap "tests Heap.cpp" "" 5)
