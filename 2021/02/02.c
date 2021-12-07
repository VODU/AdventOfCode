#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <stdint.h>

#define INPUT_PATH "input.txt"

uint32_t part1(FILE *in);
uint32_t part2(FILE *in);

int main(void)
{
    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL)
    {
        exit(EXIT_FAILURE);
    }

    uint32_t p1 = part1(input);
    printf("part1: %u \n", p1);
    assert(p1 == 2322630);

    rewind(input);

    uint32_t p2 = part2(input);
    printf("part2: %u \n", p2);
    assert(p2 == 2105273490);

    fclose(input);
    exit(EXIT_SUCCESS);
}

uint32_t part1(FILE *in)
{
    uint32_t horiz = 0;
    uint32_t depth = 0;

    char dir[10] = {0};
    uint32_t dist = 0;

    while (fscanf(in, "%9s%u", dir, &dist) == 2)
    {
        if (strcmp(dir, "forward") == 0)
            horiz += dist;
        else if (strcmp(dir, "down") == 0)
            depth += dist;
        else if (strcmp(dir, "up") == 0)
            depth -= dist;
    }
    return horiz*depth;
}

uint32_t part2(FILE *in)
{
    uint32_t horiz = 0;
    uint32_t depth = 0;
    int32_t aim = 0;

    char dir[10] = {0};
    uint32_t dist = 0;

    while (fscanf(in, "%9s%u", dir, &dist) == 2)
    {
        if (strcmp(dir, "forward") == 0)
        {
            horiz += dist;
            depth += (aim * dist);
        }
        else if (strcmp(dir, "down") == 0)
            aim += dist;
        else if (strcmp(dir, "up") == 0)
            aim -= dist;
    }
    return horiz*depth;
}
