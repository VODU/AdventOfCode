#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define INPUT_PATH "input.txt"

unsigned int part1(FILE *in);
unsigned int part2(FILE *in);

int main(void)
{
    FILE *input = fopen(INPUT_PATH, "r");
    if (input == NULL)
    {
        exit(EXIT_FAILURE);
    }

    unsigned int p1 = part1(input);
    assert(p1 == 1390);
    printf("part1: %u \n", p1);

    rewind(input);

    unsigned int p2 = part2(input);
    assert(p2 == 1457);
    printf("part2: %u \n", p2);

    fclose(input);
    exit(EXIT_SUCCESS); 
}

unsigned int part1(FILE *in)
{
    char *line = NULL;
    size_t len = 0;

    int prev_depth = INT_MAX;
    unsigned int count = 0;
    while (getline(&line, &len, in) > 0)
    {
        int depth = atoi(line);
        if (prev_depth < depth)
        {
            count++;
        }
        prev_depth = depth;
    }
    return count;
}

#define WIN_LEN 3

unsigned int part2(FILE *in)
{
    char *line = NULL;
    size_t len = 0;

    size_t idx = 0;
    unsigned int count = 0;

    int prev_sum = 0;
    int curr_sum = 0;

    int win[WIN_LEN] = {0};

    while (getline(&line, &len, in) > 0)
    {
        int i = atoi(line);
        if (idx < WIN_LEN)
        {
            win[idx] = i;
            prev_sum += i;
            curr_sum = prev_sum;
        }
        else
        {
            int idx_w = idx % WIN_LEN;
            curr_sum += i - win[idx_w]; // only one element is different
            if (curr_sum > prev_sum) {
                count++;
            }
            win[idx_w] = i;
            prev_sum = curr_sum;
        }
        idx++;
    }
    return count;
}
