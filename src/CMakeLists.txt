# Build steps
file(GLOB_RECURSE ${PROJECT_NAME}_SRC_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc)

add_executable(${PROJECT_NAME} main.cc)

# add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_SRC_FILES})
# add_library(${PROJECT_NAME}Shared SHARED ${${PROJECT_NAME}_SRC_FILES})

include_directories(${PROJECT_SOURCE_DIR}/include)