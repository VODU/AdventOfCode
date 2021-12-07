#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define SIZE 1024

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point start;
    Point end;
} Line;

void print_diagram(const int *diagram)
{
    for (int c = 0; c < SIZE; c++)
    {
        for (int r = 0; r < SIZE; r++)
        {
            int offset = (c * SIZE) + r;
            printf("%d", diagram[offset]);
        }
        printf("\n");
    }
}

size_t score(const int *diagram)
{
    size_t count = 0;
    for (int offset = 0; offset < (SIZE*SIZE); offset++)
    {
        if (diagram[offset] >= 2)
            count++;
    }
    return count;
}

bool line_is_horizontal(Line *line)
{
    return line->start.y == line->end.y;
}

bool line_is_vertical(Line *line)
{
    return line->start.x == line->end.x;
}

int main(void)
{
    FILE *file = fopen("input", "r");

    Line *lines = calloc(SIZE, sizeof(Line));
    int *diagram = calloc(SIZE * SIZE, sizeof(int));

    char buffer[64];
    int c = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        Line line;
        sscanf(buffer, "%d,%d -> %d,%d", &line.start.x, &line.start.y, &line.end.x, &line.end.y);
        lines[c++] = line;
        // printf("st: %d,%d  end: %d, %d \n", line.start.x, line.start.y, line.end.x, line.end.y);

        if (line_is_horizontal(&line))
        {
            // horizontal
            int len =  line.end.x - line.start.x;
            for (size_t x = 0; x <= abs(len); x++)
            {
                int offset;
                if (len > 0)
                    offset = (line.start.y * SIZE) + line.start.x + x;
                else
                    offset = (line.start.y * SIZE) + line.start.x - x;
                diagram[offset] += 1;
            }
            
            
        }
        else if (line_is_vertical(&line))
        {
            int len = line.end.y - line.start.y;
            for (size_t y = 0; y <= abs(len); y++)
            {
                int offset;
                if (len > 0)
                    offset = (line.start.y + y) * SIZE + line.start.x;
                else 
                    offset = (line.start.y - y) * SIZE + line.start.x;

                diagram[offset] += 1;
            }
        }
        else 
        {
            // part2 adds diagonal
            //diagonal
            int dx = line.end.x - line.start.x;
            int dy = line.end.y - line.start.y;
            for (size_t d = 0; d <= abs(dx); d++)
            {
                int offset = 0;
                if (dx > 0 && dy > 0)
                    offset = (line.start.y + d) * SIZE + line.start.x + d;
                else if (dx > 0 && dy < 0)
                    offset = (line.start.y - d) * SIZE + line.start.x + d;
                else if (dx < 0 && dy > 0)
                    offset = (line.start.y + d) * SIZE + line.start.x - d;
                else if (dx < 0 && dy < 0)
                    offset = (line.start.y - d) * SIZE + line.start.x - d;

                diagram[offset] += 1;
            }

        }
    }
    fclose(file);

    // print_diagram(diagram);
    size_t s = score(diagram);
    printf("%zu \n", s);
    // assert(s == 5576); //part1
    assert(s == 18144); //part2

    free(lines);
    free(diagram);
    exit(EXIT_SUCCESS);
}
