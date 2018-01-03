all: luatest test
CC = gcc
CXX = g++
CFLAGS = -g -O0 -Wall
LUA_VERSION = 5.1
luatest: luatest.c network.c
	$(CC) $(CFLAGS) -I/usr/include/lua$(LUA_VERSION) $^ -llua$(LUA_VERSION) -o $@ 

test: test.cpp
	$(CXX) $(CFLAGS) -I/usr/include/lua$(LUA_VERSION) $^ -llua$(LUA_VERSION) -o $@ 

clean:
	rm -f test luatest
