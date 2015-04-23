#!/usr/bin/env bash

URL=http://samba.org/ftp/ccache/ccache-3.2.1.tar.bz2
TMP_DIR=${HOME}/.tmp
INSTALL_PREFIX=${HOME}/local/$(uname)

mkdir -p ${TMP_DIR}
mkdir -p ${INSTALL_PREFIX}


if ! [[ $(uname) == "Darwin" ]]; then

    if ! [ -f "${INSTALL_PREFIX}/bin/ccache" ]; then

        if ! [ -d "${TMP_DIR}/`basename $URL .tar.bz2`" ]; then

            if ! [ -f "${TMP_DIR}/`basename $URL`" ]; then
                wget --no-check-certificate ${URL} -O ${TMP_DIR}/`basename $URL`
            fi

            tar -C ${TMP_DIR} -xjf ${TMP_DIR}/`basename $URL`
        fi

        cd ${TMP_DIR}/`basename $URL .tar.bz2`

        # configure
        ./configure --prefix=${INSTALL_PREFIX} || exit$?

        # build
        make || exit $?

        # install
        make install || exit $?

    fi
else
    # if $(uname) == "Darwin"
    echo ======================================
    echo "Use Homebrew Instead:"
    echo "$ brew install ccache"
	  echo ======================================
fi

exit $?
