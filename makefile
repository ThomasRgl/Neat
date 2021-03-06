GCC=gcc

CFLAGS=-g

OFLAGS2=-g -Wall -Werror -Wextra
OFLAGS=-g -Wall  -Wextra
OLD = -O3 -finline-functions -funroll-loops -march=native -mtune=native -flto
OLD_OFLAGS = -I/usr/include

LFLAGS=-lm

neat: neat.c snake.c main.c
	$(GCC) $(CFLAGS) $(OFLAGS) -o neat neat.c main.c snake.c $(LFLAGS)


clean:
		rm -Rf *~ neat
