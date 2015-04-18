if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (COVERALLS)
    file(STRINGS ${PROJECT_SOURCE_DIR}/test/build_list.cmake BUILD_LIST)
    ## print out list for debugging
    #message(${BUILD_LIST})
    list(APPEND COVERAGE_SRCS ${BUILD_LIST})
  endif()
endif()
