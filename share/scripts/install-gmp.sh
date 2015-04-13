#!/usr/bin/env bash

mkdir -p $HOME/.tmp

URL=ftp://ftp.gmplib.org/pub/gmp/gmp-6.0.0a.tar.bz2
TMP_DIR=${HOME}/.tmp
INSTALL_PREFIX=${HOME}/local/$(uname)

if ! [ -f "${TMP_DIR}/`basename $URL`" ]; then
    wget ${URL} -O ${TMP_DIR}/`basename $URL`
fi

if ! [ -d "${TMP_DIR}/`basename $URL a.tar.bz2`" ]; then
    tar -C ${TMP_DIR} -xjf ${TMP_DIR}/`basename $URL`
fi

mkdir -p ${INSTALL_PREFIX}

cd ${TMP_DIR}/`basename $URL a.tar.bz2`

# configure
./configure \
    --prefix=${INSTALL_PREFIX} --enable-fat --enable-cxx

# build
make all

# check
make check

# install
make install

