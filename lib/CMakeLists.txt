include_directories(${INCLUDE_DIR})

## project internal libraries
# files
set(TYPE_LIB_FILES
  ${TYPE_LIB}/dgtype.cc)
set(IMAGE_LIB_FILES
  ${IMAGE_LIB}/bmp.cc
  ${IMAGE_LIB}/bmp_data.cc)
set(CRYPTO_LIB_FILES
  ${CRYPTO_LIB}/dginteger.cc
  ${CRYPTO_LIB}/dgrandominteger.cc
  ${CRYPTO_LIB}/dgrandomprime.cc)

add_library(${TYPE_LIB} ${TYPE_LIB_FILES})
add_library(${IMAGE_LIB} ${IMAGE_LIB_FILES})
add_library(${CRYPTO_LIB} ${CRYPTO_LIB_FILES})

### Binary Libraries
## RSA libs
set(RSA_CRYPT_LIB_FILES
  rsa-crypt-lib/rsa-crypt-lib.cc)
set(RSA_ATTACK_LIB_FILES
  rsa-attack-lib/rsa-attack-lib.cc)

add_library(${RSA_CRYPT_LIB} ${RSA_CRYPT_LIB_FILES})
add_library(${RSA_ATTACK_LIB} ${RSA_ATTACK_LIB_FILES})

## Stego libs
set(STEGO_CRYPT_LIB_FILES
  stego-crypt-lib/stego-crypt-lib.cc)
set(STEGO_ATTACK_LIB_FILES
  stego-attack-lib/stego-attack-lib.cc)


add_library(${STEGO_CRYPT_LIB} ${STEGO_CRYPT_LIB_FILES})
add_library(${STEGO_ATTACK_LIB} ${STEGO_ATTACK_LIB_FILES})
