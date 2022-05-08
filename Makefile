# Makefile of pear
# (C) 2022 Yota Sasaki,
# See LICENSE for license details.

CFLAGS=-Os -pipe
CC=clang

TARG=pear
SRC = pear.c inst.c msg.c screen.c dump.c
OBJ = ${SRC:.c=.o}

all: ${TARG}

clean:
	rm -f ${TARG} ${OBJ}

%.o: %.c
	${CC} -c ${CFLAGS} $^

${TARG}: ${OBJ}
	${CC} -o $@ $^

.PHONY: all clean
