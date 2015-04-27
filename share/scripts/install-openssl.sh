#!/usr/bin/env bash

URL=http://openssl.org/source/openssl-1.0.2a.tar.gz
TMP_DIR=${HOME}/.tmp
INSTALL_PREFIX=${HOME}/local/$(uname)
OPENSSL_DIR=${HOME}/local/$(uname)/etc/openssl

mkdir -p ${TMP_DIR}
mkdir -p ${INSTALL_PREFIX}
mkdir -p ${OPENSSL_DIR}

if ! [[ $(uname) == "Darwin" ]]; then

    if ! [ -f "${INSTALL_PREFIX}/include/openssl/md5.h" ]; then

        if ! [ -d "${TMP_DIR}/`basename $URL .tar.gz`" ]; then

            if ! [ -f "${TMP_DIR}/`basename $URL`" ]; then
                wget ${URL} -O ${TMP_DIR}/`basename $URL`
            fi

            tar -C ${TMP_DIR} -xf ${TMP_DIR}/`basename $URL`
        fi

        cd ${TMP_DIR}/`basename $URL .tar.gz`

        # config
        ./config \
            --prefix=${INSTALL_PREFIX} --openssldir=${OPENSSL_DIR} \
            zlib-dynamic shared enable-cms || exit$?

        # build
        make || exit $?

        # check
        #make check || exit $?

        # install
        make install MANDIR=${INSTALL_PREFIX}/share/man MANSUFFIX=ssl || exit $?

    fi
else
    # if $(uname) == "Darwin"
    echo ======================================
    echo "Use Homebrew Instead:"
    echo "$ brew install openssl"
	  echo ======================================
fi

exit $?
