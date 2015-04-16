#!/usr/bin/env bash

URL=http://ftp.de.debian.org/debian/pool/main/l/lcov/lcov_1.11.orig.tar.gz
DIR_NAME=lcov-1.11
TMP_DIR=${HOME}/.tmp
INSTALL_PREFIX=${HOME}/local/$(uname)

mkdir -p ${TMP_DIR}
mkdir -p ${INSTALL_PREFIX}


if ! [[ $(uname) == "Darwin" ]]; then

    if ! [ -f "${INSTALL_PREFIX}/bin/lcov" ]; then

        if ! [ -f "${TMP_DIR}/`basename $URL`" ]; then
            wget ${URL} -O ${TMP_DIR}/`basename $URL`
        fi

        if ! [ -d "${TMP_DIR}/${DIR_NAME}" ]; then
            tar -C ${TMP_DIR} -xf ${TMP_DIR}/`basename $URL`
        fi

        cd ${TMP_DIR}/${DIR_NAME}

        # build
        make || exit $?

        # install
        make install || exit $?

    fi
else
    # if $(uname) == "Darwin"
    echo ======================================
    echo "Use Homebrew Instead:"
    echo "$ brew install lcov"
	  echo ======================================
fi

exit $?
