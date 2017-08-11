CC = gcc
CFLAGS = -g -O0 -Wall
luatest: luatest.c
	$(CC) $(CFLAGS) $^ -o $@ 
