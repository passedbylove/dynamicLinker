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

.PHONY: all clean

all: dynamicLinker.o Makefile

dynamicLinker.o: dynamicLinker.cpp dynamicLinker.hpp Makefile
	$(CXX) $(CXXFLAGS) dynamicLinker.cpp -c

clean:
	rm -f test dynamicLinker.o test.lib

test: dynamicLinker.o dynamicLinker.hpp test.cpp Makefile test.lib
	$(CXX) $(CXXFLAGS) test.cpp dynamicLinker.o -o test $(LDLIBS)

test.lib: testLib.c Makefile
	$(CC) -shared -Wl,$(SONAME),test.lib -o test.lib -Wall -Wextra -pedantic -fPIC testLib.c
