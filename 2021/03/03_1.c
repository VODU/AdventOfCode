#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static uint16_t calc_gamma(uint16_t *count, int cols, int rows);
static uint16_t gamma_to_epsilon(uint16_t gamma, int cols);

int main(void)
{
    char line[16];
    uint16_t count[12] = {0};
    
    int cols = 0;
    int rows = 0;

    while(scanf("%15s", line) == 1)
    {
        // sum up the 1s in every columnn
        cols = strlen(line);
        for (int i = 0; i < cols; ++i)
        {
            if (line[i] == '1')
                count[i]++;
        }
        rows++;
    }

    uint16_t gamma = calc_gamma(count, cols, rows);
    uint16_t epsilon = gamma_to_epsilon(gamma, cols);
    
    int power = gamma * epsilon;
    printf("power consumption: %d", power);
    assert(power == 2035764);
    
    exit(EXIT_SUCCESS);
}

static uint16_t calc_gamma(uint16_t *count, int cols, int rows)
{
    uint16_t gamma = 0;
    for (int i = 0; i < cols; ++i)
    {
        // shift in a 1 into gamma if number of 1s in column is most common
        if (count[i] >= (rows/2))
        {
            gamma |= 1 << (cols - 1 - i);
        }
    }
    return gamma;
}

static uint16_t gamma_to_epsilon(uint16_t gamma, int cols)
{
    // flip the bits on gamma
    int mask = (1 << cols) - 1; // 11111
    return ~gamma & mask;
}
