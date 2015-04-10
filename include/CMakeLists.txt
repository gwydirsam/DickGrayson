set(TYPE_LIB dgtype)
set(IMAGE_LIB dgimg)
set(CRYPTO_LIB dgcrypto)

set(TYPE_LIB_FILES
  ${TYPE_LIB}/dgtype.cc)
set(IMAGE_LIB_FILES
  ${IMAGE_LIB}/dgimg.cc)
set(CRYPTO_LIB_FILES
  ${CRYPTO_LIB}/dgcrypto.cc)

add_library(${TYPE_LIB} ${TYPE_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${IMAGE_LIB} ${IMAGE_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(${CRYPTO_LIB} ${CRYPTO_LIB_FILES})
include_directories(${PROJECT_SOURCE_DIR}/include)
