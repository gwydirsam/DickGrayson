if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (COVERALLS)
    list(APPEND COVERAGE_SRCS
      include(build_list.cmake))
  endif()
endif()
