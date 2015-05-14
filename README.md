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

### Download Repository
```bash
# Clone Repository
git clone https://github.com/gwydirsam/DickGrayson.git
cd DickGrayson
```

### Install Dependencies

#### Recommended
use your package manager to install:
- a C++ compiler capable of C++14
- cmake
- openssl
- gmp (GNU MP)
- libsndfile

#### Automated
The makefile included is capable of installing all of the needed dependencies, but will install them to your home folder. This is probably not what you want and is mostly intended for un-attended testing. If you are ok with this use `make install-deps`

```bash
# install dependencies to $HOME/local/$(uname)/
make install-deps

# add paths to bashrc
echo "export PATH=$HOME/local/$UNAME/bin:$PATH" >> $HOME/.bashrc
echo "export MANPATH=$HOME/local/$UNAME/share/man:$MANPATH" >> $HOME/.bashrc
echo "export LD_LIBRARY_PATH=$HOME/local/$UNAME/lib:$LD_LIBRARY_PATH" >> $HOME/.bashrc
echo "export CPLUS_INCLUDE_PATH=$HOME/local/$UNAME/include:$CPLUS_INCLUDE_PATH" >> $HOME/.bashrc
```

### Build

```bash
make all
```

## Testing

```bash
make test-all
```

## Dependencies
- cmake (installed separately)
- GNU MP library (installed separately)
- openssl (installed separately)
- googletest (included)


