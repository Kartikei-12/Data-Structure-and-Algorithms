project (Utility
    VERSION 1.0
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} INTERFACE)
add_library(self::Utility ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include
)
