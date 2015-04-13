#!/usr/bin/env bash


URL=http://www.cmake.org/files/v3.2/cmake-3.2.1-Linux-x86_64.sh
TMP_DIR=${HOME}/.tmp
INSTALL_PREFIX=${HOME}/local/$(uname)

mkdir -p ${TMP_DIR}
mkdir -p ${INSTALL_PREFIX}

if ! [ -f "${INSTALL_PREFIX}/bin/cmake" ]; then
    if ! [ -f "${TMP_DIR}/`basename $URL`" ]; then
        wget ${URL} -O ${TMP_DIR}/`basename $URL`
    fi

    chmod +x ${TMP_DIR}/`basename $URL`

    cd ${TMP_DIR}

    ${TMP_DIR}/`basename $URL` --prefix=${INSTALL_PREFIX} --exclude-subdir || exit $?

fi

exit $?

