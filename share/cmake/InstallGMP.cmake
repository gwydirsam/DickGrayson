# module name
set(MODULE_NAME gmp)

# gmp definition
include(ExternalProject)

set(${MODULE_NAME}_INSTALL_DIR "$ENV{HOME}/local/$ENV{UNAME}")
set(${MODULE_NAME}_CONFIGURE "./configure --enable-fat --enable-cxx" )
set(${MODULE_NAME}_BUILD "make && make check")
set(${MODULE_NAME}_INSTALL "make install")

ExternalProject_Add(
  ${MODULE_NAME}
  URL "ftp://ftp.gmplib.org/pub/gmp/gmp-6.0.0a.tar.bz2"
  TLS_VERIFY OFF
  TIMEOUT 15
  # SOURCE_DIR ${CMAKE_SOURCE_DIR}/ext/openssl
  # SOURCE_DIR ${${MODULE_NAME}_INSTALL}
  CONFIGURE_COMMAND ${${MODULE_NAME}_CONFIGURE}
  BUILD_COMMAND ${${MODULE_NAME}_BUILD}
  INSTALL_DIR ${${MODULE_NAME}_INSTALL_DIR}
  INSTALL_COMMAND ${${MODULE_NAME}_INSTALL}
  # Wrap download, configure and build steps in a script to log output
  LOG_DOWNLOAD ON
  LOG_CONFIGURE ON
  LOG_BUILD ON
  PREFIX "${MODULE_NAME}"
  )

ExternalProject_Get_Property(${MODULE_NAME} source_dir)
ExternalProject_Get_Property(${MODULE_NAME} binary_dir)

# add_executable(${${MODULE_NAME}_TARGET} ${TESTS_FILES})
# include_directories(${source_dir}/include ${PROJECT_SOURCE_DIR}/include)

# add_dependencies(${${MODULE_NAME}_TARGET} ${MODULE_NAME})

# target_link_libraries(${${MODULE_NAME}_TARGET}
#   ${TARGET_LIB}
#   # TODO OP should work but with something around ENABLE_EXPORTS
#   #  ${MODULE_NAME} ${MODULE_NAME}_main
#   ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}${MODULE_NAME}${CMAKE_STATIC_LIBRARY_SUFFIX}
#   ${binary_dir}/${CMAKE_STATIC_LIBRARY_PREFIX}${MODULE_NAME}_main${CMAKE_STATIC_LIBRARY_SUFFIX})

# target_link_libraries(${${MODULE_NAME}_TARGET} pthread)
