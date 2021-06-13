project (Utility_
    VERSION 1.0
    LANGUAGES CXX
)

add_library(${PROJECT_NAME} src/Utility_.cpp)
add_library(self::Utility ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)
