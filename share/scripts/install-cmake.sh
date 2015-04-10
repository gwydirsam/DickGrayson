#!/usr/bin/env bash

wget http://www.cmake.org/files/v3.2/cmake-3.2.1-Linux-x86_64.sh \
     -O /tmp/cmake-3.2.1-Linux-x86_64.sh

chmod +x /tmp/cmake-3.2.1-Linux-x86_64.sh

mkdir -p $HOME/local/$(uname)

./tmp/cmake-3.2.1-Linux-x86_64.sh --prefix=$HOME/local/$(uname) --exclude-subdir
