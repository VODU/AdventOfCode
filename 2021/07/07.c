#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

#define SIZE 1024

int part1(const int *positions, const size_t size, int min, int max)
{    
    int min_fuel = INT_MAX;
    for (size_t p = min; p <= max; p++)
    {
        int fuel = 0;
        for (size_t i = 0; i < size; i++)
        {
            fuel += abs(positions[i] - p);
        }

        if (fuel < min_fuel)
        {
            min_fuel = fuel; 
        }
    }

    return min_fuel;
}

int part2(const int *positions, const size_t size, int min, int max)
{
    int min_fuel = INT_MAX;
    for (size_t p = min; p <= max; p++)
    {
        int fuel = 0;
        for (size_t i = 0; i < size; i++)
        {
            int dist = abs(positions[i] - p);
            int step = 1;  
            for (size_t j = 0; j < dist; j++)
            {
                fuel += step;
                step++;
            }
        }

        if (fuel < min_fuel)
        {
            min_fuel = fuel; 
        }
    }

    return min_fuel;
}

int main(void)
{
    FILE *file = fopen("input", "r");

    int positions[SIZE] = {0};
    int max = 0;
    int min = INT_MAX;
    int pos = 0;
    size_t size = 0;
    while (fscanf(file, "%d,", &pos) != EOF)
    {
        if (pos > max)
            max = pos;
        if (pos < min)
            min = pos;

        positions[size++] = pos;

        if (size >= SIZE-1) {
            printf("\n Error, SIZE too small \n");
            exit(EXIT_FAILURE);
        }
    }
    // printf("size: %zu \n", size);

    int p1 = part1(positions, size, min, max);
    printf("part1: %d \n", p1);
    assert(p1 == 352254);

    int p2 = part2(positions, size, min, max);
    printf("part2: %d \n", p2);
    assert(p2 == 99053143);

    fclose(file);
    exit(EXIT_SUCCESS);
}
