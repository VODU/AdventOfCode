#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define COLS 100
#define ROWS 100

typedef struct Map {
    int data[COLS*ROWS];
    int rows;
    int cols;
} Map;

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Basin {
    Point locations[1024];
    int size;
} Basin;

void dump_map(Map map)
{
    printf("%d x %d \n", map.rows, map.cols);
    for (int r = 0; r < map.rows; r++)
    {
        for (int c = 0; c < map.cols; c++)
        {
            int idx = r * map.cols + c;
            printf("%d", map.data[idx]);
        }
        printf("\n");
    }
}

int value_at_coord(Map m, int x, int y)
{
    int i = y * COLS + x;
    return m.data[i];
}

void basin_add_location(Basin *basin, Point loc)
{
    for (int i = 0; i < basin->size; i++)
    {
        Point p = basin->locations[i];
        if ((p.x == loc.x) && (p.y == loc.y))
        {
            return;
        }
    }
    basin->locations[basin->size++] = loc;
}

void get_basin_locations(Map map, int x, int y, Basin *basin)
{
    // check neighbour of low point
    // if < 9 and > low point add to basin

    int curr = value_at_coord(map, x, y);
    // printf("curr point: %d \n", curr);
    
    //top
    if (((y-1) >= 0) && (value_at_coord(map, x, y-1) < 9) && (value_at_coord(map, x, y-1) > curr))
    {
        Point p = {x, y-1};
        basin_add_location(basin, p);
        get_basin_locations(map, x, y-1, basin);
    }
    // bottom
    if (((y+1) < map.rows) && (value_at_coord(map, x, y+1) < 9) && (value_at_coord(map, x, y+1) > curr))
    {
        Point p = {x, y+1};
        basin_add_location(basin, p);
        get_basin_locations(map, x, y+1, basin);
    }
    // left
    if (((x-1) >= 0) && (value_at_coord(map, x-1, y) < 9) && (value_at_coord(map, x-1, y) > curr))
    {
        Point p = {x-1, y};
        basin_add_location(basin, p);
        get_basin_locations(map, x-1, y, basin);
    }
    // right
    if (((x+1) < map.cols) && (value_at_coord(map, x+1, y) < 9) && (value_at_coord(map, x+1, y) > curr))
    {
        Point p = {x+1, y};
        basin_add_location(basin, p);
        get_basin_locations(map, x+1, y, basin);
    }
}

bool is_low_point(Map map, Point point)
{
    int x = point.x;
    int y = point.y;

    int curr = value_at_coord(map, x, y);

    // top
    if (((y-1) >= 0) && (value_at_coord(map, x, y-1) <= curr))
        return false;
    // bottom
    if (((y+1) < map.rows) && (value_at_coord(map, x, y+1) <= curr))
        return false;
    // left
    if (((x-1) >= 0) && (value_at_coord(map, x-1, y) <= curr))
        return false;
    // right
    if (((x+1) < map.cols) && (value_at_coord(map, x+1, y) <= curr))
        return false;

    // found low point
    // printf("low point: %d \n", curr);
    return true;
}

int largest(const void *a, const void *b)
{
    return ( (*(Basin*)b).size - (*(Basin*)a).size );
}

int part2(Map map)
{
    Basin basins[300] = {0};
    int idx = 0;

    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            Point p = {x, y};
            if (is_low_point(map, p)) 
            {
                Basin basin = {0};
                basin_add_location(&basin, p);
                get_basin_locations(map, x, y, &basin);
                basins[idx++] = basin;
                // printf("basin size: %d \n", basin.size);
                
            }
        }
    }

    // sort by largest size
    qsort(basins, idx, sizeof(Basin), largest);
    
    int result = 1;
    for (int i = 0; i < 3; i++)
    {
        result *= basins[i].size;
    }

    return result;
}

int part1(Map map)
{
    int sum_risk = 0;

    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            Point p = { x=x, y=y};
            if (is_low_point(map, p)) 
            {
                sum_risk += value_at_coord(map, p.x, p.y) + 1;
            }
        }
    }

    return sum_risk;
}

int main(void)
{
    Map map = {0};

    FILE *file = fopen("input", "r");
    char c;
    int row = 0;
    int col = 0;
    while( (c = fgetc(file)) != EOF )
    {
        if (c == '\n') {
            col = 0;
            row++;
        } else {
            int value = c - '0';
            int idx = row * COLS + col;
            map.data[idx] = value;
            col++;
        }
    }
    // ok stupid
    map.rows = ROWS;
    map.cols = COLS;

    // dump_map(map);

    int p1 = part1(map);
    printf("part1: %d \n", p1);
    assert( p1 == 498);

    int p2 = part2(map);
    printf("part2: %d \n", p2);
    assert( p2 == 1071000);

    fclose(file);
    exit(EXIT_SUCCESS);
}
