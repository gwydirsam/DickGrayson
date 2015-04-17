if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (COVERALLS)
    list(APPEND COVERAGE_SRCS
      ${PROJECT_SOURCE_DIR}/test/${RSA_CRYPT}/${RSA_CRYPT}-test.cc
      ${PROJECT_SOURCE_DIR}/test/${RSA_ATTACK}/${RSA_ATTACK}-test.cc
      ${PROJECT_SOURCE_DIR}/test/${STEGO_CRYPT}/${STEGO_CRYPT}-test.cc
      ${PROJECT_SOURCE_DIR}/test/${STEGO_ATTACK}/${STEGO_ATTACK}-test.cc
      ${PROJECT_SOURCE_DIR}/test/${TYPE_LIB}/${TYPE_LIB}-test.cc
      ${PROJECT_SOURCE_DIR}/test/${IMAGE_LIB}/${IMAGE_LIB}-test.cc
      ${PROJECT_SOURCE_DIR}/test/${CRYPTO_LIB}/${CRYPTO_LIB}-test.cc
      ${PROJECT_SOURCE_DIR}/test/libgnump/libgnump-test.cc
      )
  endif()
endif()
