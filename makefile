all: luatest test
CC = gcc
CXX = g++
CFLAGS = -g -O0 -Wall
#LUA_VERSION = 5.1
LUA_IPATH = ../lua
LUA_LPATH = ../lua
luatest: luatest.c network.c
	$(CC) $(CFLAGS) -I$(LUA_IPATH) $^ -llua -ldl -lm -L$(LUA_LPATH) -o $@ 
#	$(CC) $(CFLAGS) -I/usr/include/lua$(LUA_VERSION) $^ -llua$(LUA_VERSION) -o $@ 

test: test.cpp
	$(CXX) $(CFLAGS) -I$(LUA_IPATH) $^ -llua -ldl -lm -L$(LUA_LPATH) -o $@ 

clean:
	rm -f test luatest
