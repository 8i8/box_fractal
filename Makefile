SRC = box_fractal.c
OBJ = $(SRC:.c=.o)

CC = gcc

CFLAGS = -Wextra -Wall -pedantic

LFLAGS = -lSDL2

all: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LFLAGS)

.PHONY: all clean distclean

clean:
	rm -f *.o

distclean: clean
	rm -f a.out
