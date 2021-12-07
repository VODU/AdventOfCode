TARGET = 02

CFLAGS=-std=c11 -Wall -pedantic

.phony: run clean

run: all
	./$(TARGET).out

all: $(TARGET).c
	$(CC) $(CFLAGS) $< -o $(TARGET).out

clean:
	rm -rf $(TARGET).out