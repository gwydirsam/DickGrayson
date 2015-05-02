foreach(LIB_NAME ${PROJECT_COMBINED_LIB_LIST})
  # include project-internal libraries
  include_directories(${INCLUDE_DIR})

  file(STRINGS ${LIB_NAME}/build_list.cmake LIB_BUILD_LIST)
  add_library(${LIB_NAME} ${LIB_BUILD_LIST})

  # link with project internal libs and global libs
  # also link libs to each other
  set(OTHER_LIBS ${PROJECT_COMBINED_LIB_LIST})
  list(REMOVE_ITEM OTHER_LIBS ${LIB_NAME})
  target_link_libraries(${LIB_NAME} ${PROJECT_GLOBAL_LIBS} ${OTHER_LIBS})
  #use C++
  set_property(TARGET ${LIB_NAME} PROPERTY LINKER_LANGUAGE CXX)
  #use C++14
  set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 14)
  #C++14 required
  set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
endforeach(LIB_NAME ${PROJECT_COMBINED_LIB_LIST})