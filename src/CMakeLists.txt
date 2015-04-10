set(MAIN_SRC main.cc)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${RSA_ATTACK} ${RSA_ATTACK}/${MAIN_SRC})
target_link_libraries(${RSA_ATTACK} ${RSA_ATTACK_LIB})

#use C++14
set_property(TARGET ${RSA_ATTACK} PROPERTY CXX_STANDARD 14)
#C++14 required
set_property(TARGET ${RSA_ATTACK} PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(${RSA_CRYPT} ${RSA_CRYPT}/${MAIN_SRC})
target_link_libraries(${RSA_CRYPT} ${RSA_CRYPT_LIB})

#use C++14
set_property(TARGET ${RSA_CRYPT} PROPERTY CXX_STANDARD 14)
#C++14 required
set_property(TARGET ${RSA_CRYPT} PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(${STEGO_ATTACK} ${STEGO_ATTACK}/${MAIN_SRC})
target_link_libraries(${STEGO_ATTACK} ${STEGO_ATTACK_LIB})

#use C++14
set_property(TARGET ${STEGO_ATTACK} PROPERTY CXX_STANDARD 14)
#C++14 required
set_property(TARGET ${STEGO_ATTACK} PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(${STEGO_CRYPT} ${STEGO_CRYPT}/${MAIN_SRC})
target_link_libraries(${STEGO_CRYPT} ${STEGO_CRYPT_LIB})

#use C++14
set_property(TARGET ${STEGO_CRYPT} PROPERTY CXX_STANDARD 14)
#C++14 required
set_property(TARGET ${STEGO_CRYPT} PROPERTY CXX_STANDARD_REQUIRED ON)