set(RSA_ATTACK dorothy)
set(STEGO_ATTACK toto)
set(RSA_CRYPT munchkincrypt)
set(STEGO_CRYPT munchkinsteg)

set(MAIN_SRC main.cc)

add_executable(${RSA_ATTACK} ${RSA_ATTACK}/${MAIN_SRC})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${RSA_CRYPT} ${RSA_CRYPT}/${MAIN_SRC})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${STEGO_ATTACK} ${STEGO_ATTACK}/${MAIN_SRC})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${STEGO_CRYPT} ${STEGO_CRYPT}/${MAIN_SRC})
include_directories(${PROJECT_SOURCE_DIR}/include)