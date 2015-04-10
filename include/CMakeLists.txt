set(TYPE_LIB_FILES
  ${TYPE_LIB}/dgtype.cc)
set(IMAGE_LIB_FILES
  ${IMAGE_LIB}/dgimg.cc)
set(CRYPTO_LIB_FILES
  ${CRYPTO_LIB}/dgcrypto.cc)

# RSA libs
set(RSA_CRYPT_LIB_FILES
  )
set(RSA_ATTACK_LIB_FILES
  )

# Stego libs
set(STEGO_CRYPT_LIB_FILES
  )
set(STEGO_ATTACK_LIB_FILES
  )

add_library(${TYPE_LIB} ${TYPE_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${IMAGE_LIB} ${IMAGE_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${CRYPTO_LIB} ${CRYPTO_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${RSA_CRYPT} ${RSA_CRYPT_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${RSA_ATTACK} ${RSA_ATTACK_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${STEGO_CRYPT} ${STEGO_CRYPT_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${STEGO_ATTACK} ${STEGO_ATTACK_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)