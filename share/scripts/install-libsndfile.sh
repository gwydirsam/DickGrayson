#!/usr/bin/env bash

SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

URL=https://mirrors.kernel.org/debian/pool/main/libs/libsndfile/libsndfile_1.0.25.orig.tar.gz
DIR_NAME=libsndfile-1.0.25
TMP_DIR=${HOME}/.tmp
INSTALL_PREFIX=${HOME}/local/$(uname)

mkdir -p ${TMP_DIR}
mkdir -p ${INSTALL_PREFIX}


if ! [[ $(uname) == "Darwin" ]]; then

    if ! [ -f "${INSTALL_PREFIX}/include/sndfile.h" ]; then

        if ! [ -f "${TMP_DIR}/`basename $URL`" ]; then
            wget ${URL} -O ${TMP_DIR}/`basename $URL`
        fi

        if ! [ -d "${TMP_DIR}/${DIR_NAME}" ]; then
            tar -C ${TMP_DIR} -xf ${TMP_DIR}/`basename $URL`
        fi

        cd ${TMP_DIR}/${DIR_NAME}

        ./configure --prefix=${INSTALL_PREFIX} || exit $?
        make || exit $?
        make install || exit $?

    fi
else
    # if $(uname) == "Darwin"
    echo ======================================
    echo "Use Homebrew Instead:"
    echo "$ brew install libsndfile"
	  echo ======================================
fi

exit $?
