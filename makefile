CC=cc
#CFLAGS=-I/usr/local/include/SDL2 -L/usr/local/lib
CFLAGS=`sdl2-config --cflags` `sdl2-config --libs`

all:
	$(CC) main.c $(CFLAGS)
