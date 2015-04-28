# version 2.8.7 is on travis
cmake_minimum_required(VERSION 2.8.7 FATAL_ERROR)

project(DickGrayson)

# create debug and release builds
set(CMAKE_CONFIGURATION_TYPES Debug Release)

# turn colors on for makefiles
SET(CMAKE_COLOR_MAKEFILE ON)
# turn on for verbose makesfiles
SET(CMAKE_VERBOSE_MAKEFILE OFF)

# tests are on by default
option(BUILD_TESTS "Enable tests build" ON)

# coverage is on when tests are on
option(COVERALLS "Generate coveralls data" ${BUILD_TESTS})

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
set(SOUND_LIB dgsnd)
set(CRYPTO_LIB dgcrypto)
set(TYPE_LIB dgtype)

## list of binaries
list(APPEND PROJECT_BIN_LIST ${RSA_CRYPT} ${RSA_ATTACK} ${STEGO_CRYPT} ${STEGO_ATTACK})
## list of libraries
# binary specific libraries
list(APPEND PROJECT_BIN_LIB_LIST ${RSA_CRYPT_LIB} ${RSA_ATTACK_LIB} ${STEGO_CRYPT_LIB} ${STEGO_ATTACK_LIB})
# project internal libraries
list(APPEND PROJECT_INTERNAL_LIB_LIST ${IMAGE_LIB} ${SOUND_LIB} ${CRYPTO_LIB} ${TYPE_LIB})
# project internal and binary specific libraries
list(APPEND PROJECT_COMBINED_LIB_LIST ${PROJECT_BIN_LIB_LIST} ${PROJECT_INTERNAL_LIB_LIST})

## locations
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/bin)
set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib)
set(TEST_DIR ${PROJECT_SOURCE_DIR}/test)

# tell cmake to look in share/cmake for modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/share/cmake)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
if(COVERALLS)
  include(Coveralls)
endif()
endif()

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

# find OpenSSL
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIR})
  list(APPEND PROJECT_GLOBAL_LIBS ${OPENSSL_CRYPTO_LIBRARY})
endif()

## set some compiler flags
#  note DEBUG is set for debug build
#       NDEBUG is set for release build
if(${CMAKE_COMPILER_IS_GNUCXX})
  ## gcc/g++ flags
  # c++
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread -lsndfile")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra -DDEBUG")
  # c
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pthread -lsndfile")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wextra -DDEBUG")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall -Wextra -DDEBUG")
  if(COVERALLS)
    ## coverage
    # c++
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} --coverage -fPIC -fprofile-arcs -ftest-coverage")
    # c
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage -fPIC -fprofile-arcs -ftest-coverage")
    ## linking
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} --coverage -fprofile-arcs")
  endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    # OS X clang flags (use libc++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libc++")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra -DDEBUG")
    # c
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pthread -lsndfile")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -Wall -Wextra -DDEBUG")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -O0 -Wall -Wextra -DDEBUG")
    if(COVERALLS)
      ## coverage
      # c++
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fPIC -fprofile-arcs -ftest-coverage")
      # c
      set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fPIC -fprofile-arcs -ftest-coverage")
      ## linking
      set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}  -fprofile-arcs -ftest-coverage")
    endif()
  else()
    # linux clang flags (use libstdc++)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -stdlib=libstdc++ -pthread -lsndfile")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -Wextra -DNDEBUG")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -Wall -Wextra -DDEBUG")
    if(COVERALLS)
      ## coverage
      # c++
      set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fPIC-fprofile-arcs -ftest-coverage")
      # c
      set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fPIC -fprofile-arcs -ftest-coverage")
      ## linking
      set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}  -fprofile-arcs -ftest-coverage")
    endif()
  endif()
endif()

# build source dir
add_subdirectory(${SOURCE_DIR})
# build include dir
add_subdirectory(${INCLUDE_DIR})

# if testing, build gflags and tests
if(BUILD_TESTS)
  include(CTest)
  enable_testing()
  add_subdirectory(${TEST_DIR})
endif()

