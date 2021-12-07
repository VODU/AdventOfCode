CFLAGS=-std=c11 -Wall -pedantic
.phony: run clean

run: all
	./04.out

all: 04.c
	$(CC) $(CFLAGS) $< -o 04.out

clean:
	rm -rf 04.out
