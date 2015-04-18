Dick Grayson
================

[![Join the chat at https://gitter.im/gwydirsam/DickGrayson](https://badges.gitter.im/Join%20Chat.svg)](https://gitter.im/gwydirsam/DickGrayson?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

[![Build Status](https://travis-ci.org/gwydirsam/DickGrayson.svg?branch=develop)](https://travis-ci.org/gwydirsam/DickGrayson) [![Coverage Status](https://coveralls.io/repos/gwydirsam/DickGrayson/badge.svg?branch=develop)](https://coveralls.io/r/gwydirsam/DickGrayson?branch=develop)

## Help

```bash
# for basic commands
make help
# for advanced commands
make help-all
```

## Building

### download repository
```bash
# clone repository
git clone https://github.com/gwydirsam/DickGrayson.git
cd DickGrayson
```

### install dependencies

#### recommended
use your package manager to install:
- cmake
- openssl
- gmp (GNU MP)

#### automated
The makefile included is capable of installing all of the needed dependencies, but will install them to your home folder. This is probably not what you want and is mostly intended for un-attended testing. If you are ok with this use `make install-deps`

```bash
# install depencies to $HOME/local/$(uname)/
make install-deps

# add paths to bashrc
echo "export PATH=$HOME/local/$UNAME/bin:$PATH" >> $HOME/.bashrc
echo "export MANPATH=$HOME/local/$UNAME/share/man:$MANPATH" >> $HOME/.bashrc
echo "export LD_LIBRARY_PATH=$HOME/local/$UNAME/lib:$LD_LIBRARY_PATH" >> $HOME/.bashrc
echo "export CPLUS_INCLUDE_PATH=$HOME/local/$UNAME/include:$CPLUS_INCLUDE_PATH" >> $HOME/.bashrc
```

### build
```bash
# clone repository
git clone https://github.com/gwydirsam/DickGrayson.git
cd DickGrayson
make all
```

## Testing

```bash
make test-all
```

## Dependencies
- cmake (installed seperately)
- GNU MP library (installed seperately)
- openssl (included)
- googletest (included)

