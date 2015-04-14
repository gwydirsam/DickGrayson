if (COVERALLS)
  list(APPEND COVERAGE_SRCS
    ${PROJECT_SOURCE_DIR}/lib/${TYPE_LIB}/dgtype.cc
    ${PROJECT_SOURCE_DIR}/lib/${IMAGE_LIB}/dgimg.cc
    ${PROJECT_SOURCE_DIR}/lib/${CRYPTO_LIB}/dginteger.cc
    ${PROJECT_SOURCE_DIR}/lib/${CRYPTO_LIB}/dgrandominteger.cc
    ${PROJECT_SOURCE_DIR}/lib/${CRYPTO_LIB}/dgrandomprime.cc
    ${PROJECT_SOURCE_DIR}/lib/rsa-crypt-lib/rsa-crypt-lib.cc
    ${PROJECT_SOURCE_DIR}/lib/rsa-attack-lib/rsa-attack-lib.cc
    ${PROJECT_SOURCE_DIR}/lib/stego-crypt-lib/stego-crypt-lib.cc
    ${PROJECT_SOURCE_DIR}/lib/stego-attack-lib/stego-attack-lib.cc
    )
endif()
