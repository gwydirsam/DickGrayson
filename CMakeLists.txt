# version 2.8.7 is on travis
cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(DickGrayson)

# tests are on by default
option(BUILD_TESTS "Enable tests build" ON)

## binary names
# set(RSA_CRYPT munchkincrypt)
set(RSA_CRYPT rsa-crypt)
set(RSA_CRYPT_LIB rsa-crypt-lib)
# set(RSA_ATTACK dorothy)
set(RSA_ATTACK rsa-attack)
set(RSA_ATTACK_LIB rsa-attack-lib)

# set(STEGO_CRYPT munchkinsteg)
set(STEGO_CRYPT stego-crypt)
set(STEGO_CRYPT_LIB stego-crypt-lib)
# set(STEGO_ATTACK toto)
set(STEGO_ATTACK stego-attack)
set(STEGO_ATTACK_LIB stego-attack-lib)

## library names
set(IMAGE_LIB dgimg)
set(CRYPTO_LIB dgcrypto)
set(TYPE_LIB dgtype)

## locations
set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/bin)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lib)
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

include_directories(${INCLUDE_DIR})

# tell cmake to look in share/cmake for modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/share/cmake)

## find libraries
# find pthread
find_package(Threads REQUIRED)
if(CMAKE_USE_PTHREADS_INIT)
  list(APPEND PROJECT_GLOBAL_LIBS ${CMAKE_THREAD_LIBS_INIT})
endif()

# find gmp
find_package(GMP REQUIRED)
if(GMP_FOUND)
  include_directories(${GMP_INCLUDE_DIR})
  list(APPEND PROJECT_GLOBAL_LIBS ${GMP_LIBRARIES} ${GMPXX_LIBRARIES})
endif()

## set some compiler flags
#  note DEBUG is set for debug build
#       NDEBUG is set for release build
if(${CMAKE_COMPILER_IS_GNUCXX})
  # gcc/g++ flags
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 --coverage -Wall -Wextra -DDEBUG")
  set(CMAKE_EXE_LINKER_FLAGS_DEBUG "--coverage")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # OS X clang flags (use libc++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -nostdinc++ -I/usr/local/opt/llvm36/lib/llvm-3.6/include/c++/v1 -Wall -Wextra -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 --coverage -Wall -Wextra -DDEBUG")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "--coverage")
    link_directories(/usr/local/opt/llvm36/lib/llvm-3.6/lib)
  else()
    # linux clang flags (use libstdc++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libstdc++")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 --coverage -Wall -Wextra -DDEBUG")
  endif()
endif()

# build source dir
add_subdirectory(${SOURCE_DIR} bin/)
# build include dir
add_subdirectory(${INCLUDE_DIR} lib/)

# if testing, build gflags and tests
if(BUILD_TESTS)
  add_subdirectory(${TEST_DIR} test/)
endif()

