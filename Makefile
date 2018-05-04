#
#  Copyright (c) Hubert Jarosz. All rights reserved.
#  Licensed under the MIT license. See LICENSE file in the project root for full license information.
#

CC ?= clang
CXX ?= clang++
override CXXFLAGS += -Wall -fPIC -Wextra -Werror -std=c++11
override CFLAGS += -Wall -Wextra -pedantic
AR ?= ar

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
	$(AR) rsc libdynamicLinker.a dynamicLinker.o

install: libdynamicLinker.a Makefile
	cp libdynamicLinker.a /usr/local/lib/libdynamicLinker.a

clean:
	rm -rf test dynamicLinker.o libdynamicLinker.a test.lib test.dSYM test.exe test.dll test.bin

test: test.bin Makefile test.lib
	./test.bin

build-test: test.bin Makefile test.lib

test.bin: libdynamicLinker.a dynamicLinker.hpp test.cpp Makefile
	$(CXX) $(CXXFLAGS) test.cpp -o test.bin -L. -ldynamicLinker -ldl

test.lib: testLib.c Makefile
	$(CC) $(CFLAGS) -fPIC -shared -Wl,$(SONAME),test.lib -o test.lib testLib.c

test.dll: testLib.c Makefile
	$(CC) $(CFLAGS) -shared -o test.dll testLib.c

test.exe: libdynamicLinker.a dynamicLinker.hpp test.cpp Makefile
	$(CXX) $(CXXFLAGS) test.cpp -o test.exe -L. -ldynamicLinker $(LDLIBS)

test-windows: test.exe Makefile test.dll
	./test.exe
