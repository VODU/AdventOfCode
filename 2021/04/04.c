#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define NBOARDS 1024
#define BSIZE 5

typedef struct {
    unsigned int nums[BSIZE*BSIZE];
    unsigned int status[BSIZE*BSIZE];
    bool done;
} Board;

void print_board(Board *board)
{
    printf("\n");
    for (int r = 0; r < BSIZE; r++)
    {
        for (int c = 0; c < BSIZE; c++)
        {
            int idx = r * BSIZE + c;
            printf("%u|%u  ", board->nums[idx], board->status[idx]);
        }
        printf("\n");
    }
    printf("\n");
}

void update_board(Board *board, unsigned int number)
{
    for (int r = 0; r < BSIZE; r++)
    {
        for (int c = 0; c < BSIZE; c++)
        {
            int idx = r * BSIZE + c;
            if (board->nums[idx] == number)
            {
                board->status[idx] = 1;
            }
        }
    }
}

bool check_board(Board *board)
{
    // horizontal
    for (int r = 0; r < BSIZE; r++)
    {
        int sum_row = 0;
        for (int c = 0; c < BSIZE; c++)
        {
            int idx = r * BSIZE + c;
            sum_row += board->status[idx];
        }
        if (sum_row == BSIZE)
        {
            return true;
        }
    }

    // vertical
    for (int c = 0; c < BSIZE; c++)
    {
        int sum_col = 0;
        for (int r = 0; r < BSIZE; r++)
        {
            int idx = r * BSIZE + c;
            sum_col += board->status[idx];
        }
        if (sum_col == BSIZE)
        {
            return true;
        }
    }
    return false;
}

int sum_unmarked(Board *board)
{
    int sum = 0;
    for (int c = 0; c < BSIZE; c++)
    {
        for (int r = 0; r < BSIZE; r++)
        {
            int idx = r * BSIZE + c;
            if (board->status[idx] == 0)
            {
                sum += board->nums[idx];
            }
        }
    }
    return sum;
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
    FILE *file = fopen("input", "r");
    
    // read in the numbers
    char buffer[512];
    char numbers[512];
    fgets(buffer, sizeof(buffer), file);
    memcpy(numbers, buffer, strlen(buffer)+1);

    // read in all boards
    Board boards[NBOARDS] = {0};
    size_t size = 0;
    do {
        Board board = {{0}, {0}};
        readin_board(file, &board);
        boards[size++] = board;
    } while (!feof(file));
    
    // draw number, update & check all boards
    int number = 0;
    int offset = 0;
    char *line = numbers;
    bool part1 = false;
    Board last_win_board = {0};
    int last_win_num = 0;
    while(sscanf(line, "%d,%n", &number, &offset) > 0 )
    {
        for (int i = 0; i < size-1; i++)
        {
            if (!boards[i].done)
            {
                update_board(&boards[i], number);
                if (check_board(&boards[i]))
                {
                    last_win_board = boards[i];
                    last_win_num = number;
                    boards[i].done = true;
                    if (!part1)
                    {
                        int p1 = sum_unmarked(&boards[i]) * number;
                        printf("part1: %d\n", p1);
                        assert(p1 == 39984);
                        part1 = true;
                    }
                }
            }
        }
        line += offset;
    }
    
    int p2 = sum_unmarked(&last_win_board) * last_win_num;
    printf("part2: %d\n", p2);
    assert(p2 == 8468);

    fclose(file);
    exit(EXIT_SUCCESS);
}
