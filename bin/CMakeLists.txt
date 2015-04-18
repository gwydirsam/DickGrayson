set(MAIN_SRC main.cc)

foreach(BIN_NAME ${PROJECT_BIN_LIST})
  # include project-internal libraries
  include_directories(${INCLUDE_DIR})

  # binaries have their own libs called BIN_NAME-lib
  set(BIN_NAME_LIB ${BIN_NAME}-lib)

  # create binary named ${BIN_NAME}
  add_executable(${BIN_NAME} ${BIN_NAME}/${MAIN_SRC})

  if(TARGET ${BIN_NAME_LIB})
    message("Found ${BIN_NAME_LIB}. Linking ${BIN_NAME} with ${BIN_NAME_LIB}")
    target_link_libraries(${BIN_NAME}
      ${BIN_NAME_LIB})
  endif()
  # link with project internal libs and global libs
  target_link_libraries(${BIN_NAME} ${PROJECT_INTERNAL_LIB_LIST} ${PROJECT_GLOBAL_LIBS})
  #use C++14
  set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD 14)
  #C++14 required
  set_property(TARGET ${BIN_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
endforeach(BIN_NAME ${PROJECT_BIN_LIST})

# these binaries are built last, so this is where we create our coverage target
include(coverage_list.cmake)