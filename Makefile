CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -ggdb
LIBS = -lm

.PHONY: all clean

all: gb

build:
	@mkdir -p build

gb: src/gb.c | build
	$(CC) $(CFLAGS) -o build/main src/gb.c

clean:
	rm -rf build/
