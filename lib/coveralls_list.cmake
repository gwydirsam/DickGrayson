if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  if (COVERALLS)
    list(APPEND COVERAGE_SRCS
      ${PROJECT_SOURCE_DIR}/lib/${TYPE_LIB}/${TYPE_LIB}.cc
      ${PROJECT_SOURCE_DIR}/lib/${IMAGE_LIB}/${IMAGE_LIB}.cc
      ${PROJECT_SOURCE_DIR}/lib/${CRYPTO_LIB}/dginteger.cc
      ${PROJECT_SOURCE_DIR}/lib/${CRYPTO_LIB}/dgrandominteger.cc
      ${PROJECT_SOURCE_DIR}/lib/${CRYPTO_LIB}/dgrandomprime.cc
      ${PROJECT_SOURCE_DIR}/lib/${RSA_CRYPT_LIB}/${RSA_CRYPT_LIB}.cc
      ${PROJECT_SOURCE_DIR}/lib/${RSA_ATTACK_LIB}/${RSA_ATTACK_LIB}.cc
      ${PROJECT_SOURCE_DIR}/lib/${STEGO_CRYPT_LIB}/${STEGO_CRYPT_LIB}.cc
      ${PROJECT_SOURCE_DIR}/lib/${STEGO_ATTACK_LIB}/${STEGO_ATTACK_LIB}.cc
      )
  endif()
endif()
