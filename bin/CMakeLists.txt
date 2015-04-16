set(MAIN_SRC main.cc)


# include project-internal libraries
include_directories(${INCLUDE_DIR})

add_executable(${RSA_ATTACK} ${RSA_ATTACK}/${MAIN_SRC})
target_link_libraries(${RSA_ATTACK} ${RSA_ATTACK_LIB} ${PROJECT_GLOBAL_LIBS})
#use C++14
set_property(TARGET ${RSA_ATTACK} PROPERTY CXX_STANDARD 14)
#C++14 required
set_property(TARGET ${RSA_ATTACK} PROPERTY CXX_STANDARD_REQUIRED ON)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (COVERALLS)
    set(COVERAGE_SRCS ${SOURCE_DIR}/${RSA_ATTACK}/${MAIN_SRC})
  endif()
endif()

add_executable(${RSA_CRYPT} ${RSA_CRYPT}/${MAIN_SRC})
target_link_libraries(${RSA_CRYPT} ${RSA_CRYPT_LIB} ${PROJECT_GLOBAL_LIBS})
#use C++14
set_property(TARGET ${RSA_CRYPT} PROPERTY CXX_STANDARD 14)
#C++14 required
set_property(TARGET ${RSA_CRYPT} PROPERTY CXX_STANDARD_REQUIRED ON)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (COVERALLS)
    list(APPEND COVERAGE_SRCS ${SOURCE_DIR}/${RSA_CRYPT}/${MAIN_SRC})
  endif()
endif()

add_executable(${STEGO_ATTACK} ${STEGO_ATTACK}/${MAIN_SRC})
target_link_libraries(${STEGO_ATTACK} ${STEGO_ATTACK_LIB} ${PROJECT_GLOBAL_LIBS})
#use C++14
set_property(TARGET ${STEGO_ATTACK} PROPERTY CXX_STANDARD 14)
#C++14 required
set_property(TARGET ${STEGO_ATTACK} PROPERTY CXX_STANDARD_REQUIRED ON)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (COVERALLS)
    list(APPEND COVERAGE_SRCS ${SOURCE_DIR}/${STEGO_ATTACK}/${MAIN_SRC})
  endif()
endif()

add_executable(${STEGO_CRYPT} ${STEGO_CRYPT}/${MAIN_SRC})
target_link_libraries(${STEGO_CRYPT} ${STEGO_CRYPT_LIB} ${PROJECT_GLOBAL_LIBS})
#use C++14
set_property(TARGET ${STEGO_CRYPT} PROPERTY CXX_STANDARD 14)
#C++14 required
set_property(TARGET ${STEGO_CRYPT} PROPERTY CXX_STANDARD_REQUIRED ON)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (COVERALLS)
    list(APPEND COVERAGE_SRCS ${SOURCE_DIR}/${STEGO_CRYPT}/${MAIN_SRC})
    include(${PROJECT_SOURCE_DIR}/lib/coveralls_list.cmake)
    # include(${PROJECT_SOURCE_DIR}/test/coveralls_list.cmake)

    # Create the coveralls target.
    coveralls_setup(
      # The source files.
      "${COVERAGE_SRCS}" 
      # If we should upload.
      ON                 
      # (Optional) Alternate project cmake module path.
      "${PROJECT_SOURCE_DIR}/share/cmake")
  endif()
endif()