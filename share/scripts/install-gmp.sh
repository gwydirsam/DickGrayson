#!/usr/bin/env bash

mkdir -p $HOME/.tmp

URL=ftp://ftp.gmplib.org/pub/gmp/gmp-6.0.0a.tar.bz2
TMP_DIR=${HOME}/.tmp
INSTALL_PREFIX=${HOME}/local/$(uname)

wget ${URL} -O ${TMP_DIR}/`basename $URL`

tar -C ${TMP_DIR} -xjf `basename $URL`

mkdir -p ${INSTALL_PREFIX}

# configure
${TMP_DIR}/`basename $URL tar.bz2`/configure \
          --prefix=${INSTALL_PREFIX} --enable-fat --enable-cxx

# build
make -C ${TMP_DIR}/`basename $URL tar.bz2`

# check
make -C ${TMP_DIR}/`basename $URL tar.bz2` check

# install
make -C ${TMP_DIR}/`basename $URL tar.bz2` install

