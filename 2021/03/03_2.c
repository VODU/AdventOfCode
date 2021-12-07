#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdint.h>

// #define BITS 5      // cols
// #define COUNT 12    // rows
#define BITS 12
#define COUNT 1000

uint16_t calc_rating(uint16_t *numbers, int count, int oxygen);

int main(void)
{
    // parse everything into numbers
    uint16_t *numbers = calloc(COUNT, sizeof(uint16_t));
    
    char *line = NULL;
    size_t len = 0;
    int idx = 0;
    while (getline(&line, &len, stdin) > 0)
    {
        numbers[idx++] = strtol(line, NULL, 2);
    }

    // copy the data because its beeing sorted
    uint16_t *work = calloc(COUNT, sizeof(uint16_t));

    memcpy(work, numbers, COUNT * sizeof(uint16_t));
    uint16_t oxy = calc_rating(work, COUNT, 1);
    printf("oxygen: %d \n", oxy);

    memcpy(work, numbers, COUNT * sizeof(uint16_t));
    uint16_t co2 = calc_rating(work, COUNT, 0);
    printf("co2: %d \n", co2);

    printf("life support rating: %d", (int)oxy*co2);
    assert((int)oxy*co2 == 2817661);
    
    free(numbers);
    free(work);
    exit(EXIT_SUCCESS);
}

uint16_t calc_rating(uint16_t *numbers, int count, int oxygen)
{
    for (int bit = 0; bit < BITS; bit++)
    {
        // printf("curr count: %d ", count);

        int num1s = 0;
        for (size_t i = 0; i < count; i++)
        {
            // check if bit is 1
            if ( numbers[i] & (1 << (BITS-1 - bit)) ) {
                num1s++;
            }
        }

        // printf("num1s: %d ", num1s);

        // sort nums by least common bit for co2, by most common bit for oxygen
        int sort_key = (num1s >= (count - num1s)) ? 0 : 1;
        if (oxygen)
            sort_key = (num1s >= (count - num1s)) ? 1 : 0;

        // printf("sort: %d ", sort_key);

        int j = 0;
        for (size_t i = 0 ; i < count; i++)
        {
            // shift bits and check if bit is sort key, then move it to the beginning
            if ( ((numbers[i] >> (BITS-1 - bit)) & 1) == sort_key )
            {
                numbers[j++] = numbers[i];
            }
        }

        // only the filtered ones will be checked next time
        count = j;

        // printf("new count: %d ", count);
        // printf("\n");
    }
    return numbers[0];    
}
