TARGET = 09

CFLAGS=-std=c11 -Wall -pedantic -g

.phony: run clean

run: all
	./$(TARGET).out

all: $(TARGET).c
	$(CC) $(CFLAGS) $< -o $(TARGET).out

clean:
	rm -rf $(TARGET).out