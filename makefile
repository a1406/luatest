CC = gcc
CFLAGS = -g -O0 -Wall
LUA_VERSION = 5.1
luatest: luatest.c
	$(CC) $(CFLAGS) -I/usr/include/lua$(LUA_VERSION) $^ -llua$(LUA_VERSION) -o $@ 
