set(BINARY_NAME munchkincrypt)
set(MAIN_SRC main.cc)

add_executable(${BINARY_NAME} ${MAIN_SRC})

include_directories(${PROJECT_SOURCE_DIR}/include/${BINARY_NAME})
