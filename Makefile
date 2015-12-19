CC = clang
CXX = clang++
CXXFLAGS = -Wall -Wextra -Werror -std=c++14
LDLIBS = -ldl

.PHONY: all clean

all: test dynamicLinker.o testLib.so.1.0 Makefile

test: dynamicLinker.o dynamicLinker.hpp test.cpp Makefile testLib.so.1.0
	$(CXX) $(CXXFLAGS) test.cpp dynamicLinker.o -o test $(LDLIBS)

testLib.so.1.0: testLib.c Makefile
	$(CC) -shared -Wl,-soname,testLib.so.1 -o testLib.so.1.0 -Wall -Wextra -pedantic -fPIC testLib.c

dynamicLinker.o: dynamicLinker.cpp dynamicLinker.hpp Makefile
	$(CXX) $(CXXFLAGS) dynamicLinker.cpp -c

clean:
	rm -f test dynamicLinker.o testLib.so.1.0
