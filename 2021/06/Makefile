TARGET1 = 06_1
TARGET2 = 06_2

CFLAGS=-std=c11 -Wall -pedantic

.phony: all run1 run2 clean

all: part1 part2

run1: part1
	./$(TARGET1).out

run2: part2
	./$(TARGET2).out

part1: $(TARGET1).c
	$(CC) $(CFLAGS) $< -o $(TARGET1).out

part2: $(TARGET2).c
	$(CC) $(CFLAGS) $< -o $(TARGET2).out

clean:
	rm -rf $(TARGET1).out
	rm -rf $(TARGET2).out