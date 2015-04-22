# gtest definition
include(ExternalProject)

ExternalProject_Add(
  gtest
  # SVN_REPOSITORY http://googletest.googlecode.com/svn/tags/release-1.7.0
  GIT_REPOSITORY https://github.com/gwydirsam/googletest.git 
  GIT_TAG release-1.7.0
  TLS_VERIFY OFF
  TIMEOUT 15
  UPDATE_COMMAND ""
  PATCH_COMMAND ""
  INSTALL_COMMAND ""
  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  PREFIX "gtest"
  )

ExternalProject_Get_Property(gtest source_dir)
ExternalProject_Get_Property(gtest binary_dir)

file(STRINGS test_list.cmake TEST_LIST)
## print out list for debugging
#message(${TEST_LIST})

foreach(TEST_NAME ${TEST_LIST})
  set(TARGET ${TEST_NAME})
  set(TARGET_LIB ${TARGET}-lib)
  set(GTEST_TARGET ${TARGET}-test)
  set(TESTS_FILES ${TARGET}/${TARGET}-test.cc)

  add_executable(${GTEST_TARGET} ${TESTS_FILES})
  include_directories(${source_dir}/include ${PROJECT_SOURCE_DIR}/lib)

  add_dependencies(${GTEST_TARGET} gtest)

  if(TARGET ${TARGET_LIB})
    message("Found ${TARGET_LIB}. Linking ${GTEST_TARGET} with ${TARGET_LIB}")
    target_link_libraries(${GTEST_TARGET}
      ${TARGET_LIB})
  endif()
  # if(TARGET ${TARGET})
  #   target_link_libraries(${GTEST_TARGET}
  #     ${TARGET})
  # endif()
  target_link_libraries(${GTEST_TARGET}
    ${PROJECT_INTERNAL_LIB_LIST}
    ${PROJECT_GLOBAL_LIBS}
    ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest${CMAKE_STATIC_LIBRARY_SUFFIX}
    ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}gtest_main${CMAKE_STATIC_LIBRARY_SUFFIX})

  #use C++14
  set_property(TARGET ${GTEST_TARGET} PROPERTY CXX_STANDARD 14)
  #C++14 required
  set_property(TARGET ${GTEST_TARGET} PROPERTY CXX_STANDARD_REQUIRED ON)

  add_test(${TARGET} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${GTEST_TARGET} --gtest_color=yes)
endforeach(TEST_NAME ${TEST_LIST})

