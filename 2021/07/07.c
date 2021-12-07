#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define SIZE 1024

int ascending(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int part1(const int *positions, const size_t size)
{
    // sort and calculate median
    qsort((void *)positions, size, sizeof(int), ascending);
    int median = positions[5];
    printf("median: %d \n", median);

    int fuel = 0;
    for (size_t i = 0; i < size; i++)
    {
        fuel += abs(median - positions[i]);
        printf("%d", positions[i]);
    }
    return fuel;
}

int main(void)
{
    FILE *file = fopen("test", "r");

    int positions[SIZE] = {0};
    int pos = 0;
    size_t size = 0;
    while (fscanf(file, "%d,", &pos) != EOF)
    {
        positions[size++] = pos;

        if (size >= SIZE-1) {
            printf("\n Error, SIZE too small \n");
            exit(EXIT_FAILURE);
        }
    }
    printf("size: %zu \n", size);

    int fuel = part1(positions, size);
    printf("\nfuel: %d \n", fuel);

    // calculate the median

    fclose(file);
    exit(EXIT_SUCCESS);
}
