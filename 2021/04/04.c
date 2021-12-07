#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define NBOARDS 3
#define BSIZE 5

typedef struct {
    unsigned int nums[BSIZE*BSIZE];
    unsigned int status[BSIZE*BSIZE];
} Board;

void print_board(Board *board)
{
    for (int r = 0; r < BSIZE; r++)
    {
        for (int c = 0; c < BSIZE; c++)
        {
            int idx = r * BSIZE + c;
            printf("%u ",board->nums[idx]);
        }
        printf("\n");
    }
    printf("\n");
}

void readin_board(FILE *file, Board *board)
{
    char buffer[64];
    int r = 0;
    // skip line
    fgets(buffer, sizeof(buffer), file);

    for (int i = 0; i < BSIZE; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        // printf("%s", buffer);
        unsigned int *nums_p = board->nums;
        sscanf(buffer, "%u %u %u %u %u",
            &nums_p[r * BSIZE],
            &nums_p[r * BSIZE + 1],
            &nums_p[r * BSIZE + 2],
            &nums_p[r * BSIZE + 3],
            &nums_p[r * BSIZE + 4]);
        r++;
    }
}

int main()
{
    FILE *file = fopen("test", "r");
    char buffer[128];

    // read in the numbers
    char numbers[128];
    fgets(buffer, sizeof(buffer), file);
    memcpy(numbers, buffer, strlen(buffer)+1);
    printf("nums: %s \n", numbers);

    // read in all boards
    Board *boards = calloc(NBOARDS, sizeof(Board));
    int idx = 0;
    do {
        Board board;
        readin_board(file, &board);
        boards[idx++] = board;
    } while (!feof(file));

    // draw number
    // update status on all boards
    

    fclose(file);
    exit(EXIT_SUCCESS);
}
