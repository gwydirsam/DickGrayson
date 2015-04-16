#!/usr/bin/env bash

SCRIPT_DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
PATCH_FILE=lcov-prefix.patch

URL=http://ftp.de.debian.org/debian/pool/main/l/lcov/lcov_1.11.orig.tar.gz
DIR_NAME=lcov-1.11
TMP_DIR=${HOME}/.tmp
INSTALL_PREFIX=${HOME}/local/$(uname)

mkdir -p ${TMP_DIR}
mkdir -p ${INSTALL_PREFIX}


if ! [[ $(uname) == "Darwin" ]]; then

    # install lcovrc
    cp ${SCRIPT_DIR}/../examples/lcovrc ${HOME}/.lcovrc

    if ! [ -f "${INSTALL_PREFIX}/bin/lcov" ]; then

        if ! [ -f "${TMP_DIR}/`basename $URL`" ]; then
            wget ${URL} -O ${TMP_DIR}/`basename $URL`
        fi

        if ! [ -d "${TMP_DIR}/${DIR_NAME}" ]; then
            tar -C ${TMP_DIR} -xf ${TMP_DIR}/`basename $URL`
        fi

        cd ${TMP_DIR}/${DIR_NAME}

        # patch
        patch -p1 < ${SCRIPT_DIR}/${PATCH_FILE}

        # build and install
        PREFIX=${INSTALL_PREFIX} make install || exit $?

    fi
else
    # if $(uname) == "Darwin"
    echo ======================================
    echo "Use Homebrew Instead:"
    echo "$ brew install lcov"
	  echo ======================================
fi

exit $?
