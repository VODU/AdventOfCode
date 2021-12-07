#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SIZE 9

void print_array(unsigned long *array)
{
    for (size_t i = 0; i < SIZE; i++)
    {
        printf("%lu", array[i]);
    }
    printf("\n");
}

int main()
{
    FILE *file = fopen("input", "r");

    unsigned long fish[SIZE] = {0};

    int c;
    while((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
            break;

        if (c != ',')
        {
            // only save how many fish are there instead of all
            unsigned int idx = c - '0';
            fish[idx] += 1;
        }
    }
    fclose(file);

    unsigned long tmp[SIZE] = {0};
    unsigned int days = 0;
    while(days < 256)
    {
        memset(tmp, 0, SIZE * sizeof(unsigned long));

        // shift all down means timer down
        for (size_t i = 1; i < SIZE; i++)
        {
            tmp[i-1] = fish[i];
        }
        // 0 becomes 6 each day
        // for every 0 there is a new fish, add this count to 8
        tmp[6] += fish[0];
        tmp[8] += fish[0];

        memcpy(fish, tmp, SIZE * sizeof(unsigned long));

        days++;
    }

    // count fish
    unsigned long count = 0;
    for (int i = 0; i < SIZE; i++)
    {
        count += fish[i];
    }

    printf("%lu", count);
    assert(count == 1639643057051); // part 2

    exit(EXIT_SUCCESS);
}
