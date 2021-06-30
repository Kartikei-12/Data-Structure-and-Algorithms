cmake_minimum_required(VERSION 3.15.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message("-- Setting build type to 'RelWithDebInfo' as none was specified.")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()

project(
    Kartikei-12_Cpp14_DSA VERSION 1.0
    DESCRIPTION "My Implementaion of data structures and algorithms in C++"
    LANGUAGES CXX
)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

add_subdirectory(Node_)
add_subdirectory(Data-Structure)
add_subdirectory(Utility_)
add_subdirectory(examples)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()


# find_package(Doxygen)
# if (DOXYGEN_FOUND)
#     set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)
#     set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)
#     configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#     message("-- Doxygen build started")
#     # Note: do not put "ALL" - this builds docs together with application EVERY TIME!
#     add_custom_target(docs ALL
#         COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#         WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
#         COMMENT "Generating documentation with Doxygen"
#         VERBATIM
#     )
# else (DOXYGEN_FOUND)
#     message(" -- Doxygen need to be installed to generate the doxygen documentation")
# endif (DOXYGEN_FOUND)
