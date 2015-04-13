#!/usr/bin/env bash

URL=ftp://ftp.gmplib.org/pub/gmp/gmp-6.0.0a.tar.bz2
TMP_DIR=${HOME}/.tmp
INSTALL_PREFIX=${HOME}/local/$(uname)

mkdir -p ${TMP_DIR}
mkdir -p ${INSTALL_PREFIX}

if ! [ -f "${INSTALL_PREFIX}/include/gmpxx.h" ]; then

    if ! [ -f "${TMP_DIR}/`basename $URL`" ]; then
        wget ${URL} -O ${TMP_DIR}/`basename $URL`
    fi

    if ! [ -d "${TMP_DIR}/`basename $URL a.tar.bz2`" ]; then
        tar -C ${TMP_DIR} -xjf ${TMP_DIR}/`basename $URL`
    fi

    cd ${TMP_DIR}/`basename $URL a.tar.bz2`

    # configure
    ./configure \
        --prefix=${INSTALL_PREFIX} --enable-fat --enable-cxx || exit$?

    # build
    make || exit $?

    # check
    #make check || exit $?

    # install
    make install || exit $?

fi

exit $?
