
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3 
CPPFLAGS =
LDFLAGS=
LDLIBS= -lm

SRC1= main.c XOR.c
OBJ= ${SRC1:.c=.o}
DEP= ${SRC1:.c=.d}

all : main


main : ${OBJ}


clean : 
	${RM} ${OBJ} 
	${RM} ${DEP}
	${RM} main


-include ${DEP}
