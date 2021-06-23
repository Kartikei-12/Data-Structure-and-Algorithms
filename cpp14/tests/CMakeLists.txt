project(tests)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
# Prevent installation of GTest with the project
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(INSTALL_GMOCK OFF CACHE BOOL "" FORCE)

# ------------------------------------------------------------------------------------------------------------------------------
add_subdirectory(Help_Test)
set(AllTestFiles "")
set(AllLibraryFiles "")
# Seprate executable for Different Structure
macro(Test_Macro DStructure File Count)
    add_executable(${PROJECT_NAME}_${DStructure} "src/tests Data Structure/${File}" main.cpp)
    target_link_libraries(${PROJECT_NAME}_${DStructure} PUBLIC
        self::${DStructure}
        self::Utility
        self::HelpTest
        gtest_main
    )
    list(APPEND AllTestFiles "src/tests Data Structure/${File}")
    list(APPEND AllLibraryFiles "self::${DStructure}")
    foreach(i RANGE 0 ${Count})
        add_test(
            NAME ${PROJECT_NAME}_${DStructure}${i}
            COMMAND ${PROJECT_NAME}_${DStructure} --gtest_filter=*${DStructure}Test/${i}*
        )
    endforeach(i)
    # add_custom_command(
    #     TARGET ${PROJECT_NAME}_${DStructure}
    #     COMMENT "Running ${File} tests"
    #     POST_BUILD
    #     COMMAND ${PROJECT_NAME}_${DStructure}
    # )
endmacro(Test_Macro)

Test_Macro(DynamicArray "tests Dynamic Array.cpp" 2)
Test_Macro(SinglyLinkedList "tests Singly Linked List.cpp" 2)
Test_Macro(Heap "tests Heap.cpp" 5)
Test_Macro(Stack "tests Stack.cpp" 5)
Test_Macro(Queue "tests Queue.cpp" 5)
Test_Macro(BinarySearchTree "tests Binary Search Tree.cpp" 2)

add_executable(${PROJECT_NAME}_ALL ${AllTestFiles} main.cpp)
target_link_libraries(${PROJECT_NAME}_ALL PUBLIC
    ${AllLibraryFiles}
    self::Utility
    self::HelpTest
    gtest_main
)
add_custom_command(
    TARGET ${PROJECT_NAME}_ALL
    COMMENT "Running ALL tests"
    POST_BUILD
    COMMAND ${PROJECT_NAME}_ALL
)
