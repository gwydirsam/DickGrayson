if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (COVERALLS)
    list(APPEND COVERAGE_SRCS include(build_list.cmake))
    include(${PROJECT_SOURCE_DIR}/lib/coverage_list.cmake)
    # include(${PROJECT_SOURCE_DIR}/test/coverage_list.cmake)

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