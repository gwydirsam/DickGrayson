enable_testing()

# gtest definition
include(ExternalProject)

ExternalProject_Add(
  gtest
  SVN_REPOSITORY http://googletest.googlecode.com/svn/tags/release-1.7.0
  TIMEOUT 10
  # Disable install step
  INSTALL_COMMAND ""
  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  PREFIX "gtest"
  )

ExternalProject_Get_Property(gtest source_dir)
ExternalProject_Get_Property(gtest binary_dir)

set(TARGET ${RSA_ATTACK})
set(TARGET_LIB ${TARGET}-lib)
set(GTEST_TARGET ${TARGET}-test)
set(TESTS_FILES ${TARGET}/${TARGET}-test.cc)

add_executable(${GTEST_TARGET} ${TESTS_FILES})
include_directories(${source_dir}/include ${PROJECT_SOURCE_DIR}/include)

add_dependencies(${GTEST_TARGET} gtest)

target_link_libraries(${GTEST_TARGET}
  ${TARGET_LIB}
  # TODO OP should work but with something around ENABLE_EXPORTS
  #  gtest gtest_main
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(${GTEST_TARGET} pthread)

set(TARGET ${RSA_CRYPT})
set(TARGET_LIB ${TARGET}-lib)
set(GTEST_TARGET ${TARGET}-test)
set(TESTS_FILES ${TARGET}/${TARGET}-test.cc)

add_executable(${GTEST_TARGET} ${TESTS_FILES})
include_directories(${source_dir}/include ${PROJECT_SOURCE_DIR}/include)

add_dependencies(${GTEST_TARGET} gtest)

target_link_libraries(${GTEST_TARGET}
  ${TARGET_LIB}
  # TODO OP should work but with something around ENABLE_EXPORTS
  #  gtest gtest_main
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(${GTEST_TARGET} pthread)

set(TARGET ${STEGO_CRYPT})
set(TARGET_LIB ${TARGET}-lib)
set(GTEST_TARGET ${TARGET}-test)
set(TESTS_FILES ${TARGET}/${TARGET}-test.cc)

add_executable(${GTEST_TARGET} ${TESTS_FILES})
include_directories(${source_dir}/include ${PROJECT_SOURCE_DIR}/include)

add_dependencies(${GTEST_TARGET} gtest)

target_link_libraries(${GTEST_TARGET}
  ${TARGET_LIB}
  # TODO OP should work but with something around ENABLE_EXPORTS
  #  gtest gtest_main
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(${GTEST_TARGET} pthread)

set(TARGET ${STEGO_ATTACK})
set(TARGET_LIB ${TARGET}-lib)
set(GTEST_TARGET ${TARGET}-test)
set(TESTS_FILES ${TARGET}/${TARGET}-test.cc)

add_executable(${GTEST_TARGET} ${TESTS_FILES})
include_directories(${source_dir}/include ${PROJECT_SOURCE_DIR}/include)

add_dependencies(${GTEST_TARGET} gtest)

target_link_libraries(${GTEST_TARGET}
  ${TARGET_LIB}
  # TODO OP should work but with something around ENABLE_EXPORTS
  #  gtest gtest_main
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(${GTEST_TARGET} pthread)

set(TARGET ${IMAGE_LIB})
set(GTEST_TARGET ${TARGET}-test)
set(TESTS_FILES ${TARGET}/${TARGET}-test.cc)

add_executable(${GTEST_TARGET} ${TESTS_FILES})
include_directories(${source_dir}/include ${PROJECT_SOURCE_DIR}/include)

add_dependencies(${GTEST_TARGET} gtest)

target_link_libraries(${GTEST_TARGET}
  ${TARGET}
  # TODO OP should work but with something around ENABLE_EXPORTS
  #  gtest gtest_main
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(${GTEST_TARGET} pthread)

set(TARGET ${CRYPTO_LIB})
set(GTEST_TARGET ${TARGET}-test)
set(TESTS_FILES ${TARGET}/${TARGET}-test.cc)

add_executable(${GTEST_TARGET} ${TESTS_FILES})
include_directories(${source_dir}/include ${PROJECT_SOURCE_DIR}/include)

add_dependencies(${GTEST_TARGET} gtest)

target_link_libraries(${GTEST_TARGET}
  ${TARGET}
  # TODO OP should work but with something around ENABLE_EXPORTS
  #  gtest gtest_main
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(${GTEST_TARGET} pthread)

set(TARGET ${TYPE_LIB})
set(GTEST_TARGET ${TARGET}-test)
set(TESTS_FILES ${TARGET}/${TARGET}-test.cc)

add_executable(${GTEST_TARGET} ${TESTS_FILES})
include_directories(${source_dir}/include ${PROJECT_SOURCE_DIR}/include)

add_dependencies(${GTEST_TARGET} gtest)

target_link_libraries(${GTEST_TARGET}
  ${TARGET}
  # TODO OP should work but with something around ENABLE_EXPORTS
  #  gtest gtest_main
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
  ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

target_link_libraries(${GTEST_TARGET} pthread)
