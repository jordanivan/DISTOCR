CC = gcc

CPPFLAGS = `pkg-config --cflags sdl` -MMD
CFLAGS = -Wall -Wextra -std=c99 -O3
LDFLAGS = 
LDLIBS = `pkg-config --libs sdl` -lSDL_image

all: Bruit 

Bruit : Bruit.c pixel_operations.c

clean : 
	${RM} *.o
	${RM} *.d
	${RM} Bruit

#END
