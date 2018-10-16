
CC=gcc

CFLAGS= -Wall -Wextra -std=c99  `pkg-config --cflags gtk+-3.0`
CLIBS= `pkg-config --libs gtk+-3.0`

EXEC= distocr



distocr: distocr.c
	
	gcc $(CFLAGS) -o distocr distocr.c $(CLIBS)

clean::
	rm -rf *.o

mrproper: clean
	rm -rf  *o distocr

