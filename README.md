# dynamicLinker

[![Build Status](https://travis-ci.org/Marqin/dynamicLinker.svg?branch=master)](https://travis-ci.org/Marqin/dynamicLinker)
[![Join the chat at https://gitter.im/Marqin/dynamicLinker](https://badges.gitter.im/Marqin/dynamicLinker.svg)](https://gitter.im/Marqin/dynamicLinker?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)
[![Percentage of issues still open](http://isitmaintained.com/badge/open/Marqin/dynamicLinker.svg)](http://isitmaintained.com/project/Marqin/dynamicLinker "Percentage of issues still open")
[![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/Marqin/dynamicLinker.svg)](http://isitmaintained.com/project/Marqin/dynamicLinker "Average time to resolve an issue")

C++11 wrapper for POSIX dynamic linking ( for dlfcn.h ).

## Compilation

You **need** compiler with full C++11 support.

```make``` ( or ```make CXX=g++ CC=gcc``` if you don't have clang compiler )

```sudo make install``` - if you want to install *libdynamicLinker.a* to */usr/local/lib/*

You can also run ```make test``` ( or ```make test CXX=g++ CC=gcc``` ) after building, to check if dynamicLinker will be working for you. It will run simple test code ( which will also catch some exceptions ), and if make doesn't error - it's OK.


## Documentation

**TODO** :-1:
