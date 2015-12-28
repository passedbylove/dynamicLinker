#
#  Copyright (c) Hubert Jarosz. All rights reserved.
#  Licensed under the MIT license. See LICENSE file in the project root for full license information.
#

CC = clang
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11
LDLIBS = -ldl

OS_NAME = $(shell uname -s)
ifeq ($(OS_NAME), Darwin)
  SONAME = -install_name
else
  SONAME = -soname
endif

.PHONY: all clean install build-test test

all: libdynamicLinker.a Makefile

libdynamicLinker.a: dynamicLinker.cpp dynamicLinker.hpp Makefile
	$(CXX) $(CXXFLAGS) dynamicLinker.cpp -c
	ar rsc libdynamicLinker.a dynamicLinker.o

install: libdynamicLinker.a Makefile
	cp libdynamicLinker.a /usr/local/lib/libdynamicLinker.a

clean:
	rm -rf test dynamicLinker.o libdynamicLinker.a test.lib test.dSYM

test: test.bin Makefile test.lib
	./test.bin

build-test: test.bin Makefile test.lib

test.bin: libdynamicLinker.a dynamicLinker.hpp test.cpp Makefile
	$(CXX) $(CXXFLAGS) test.cpp -o test.bin -L. -ldynamicLinker $(LDLIBS)

test.lib: testLib.c Makefile
	$(CC) -shared -Wl,$(SONAME),test.lib -o test.lib -Wall -Wextra -pedantic -fPIC testLib.c
