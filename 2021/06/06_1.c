#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Array {
    unsigned int *values;
    size_t size;
    size_t len;
} Array;

void array_init(Array *a, size_t size)
{
    a->values = malloc(size * sizeof(unsigned int));
    a->size = size;
    a->len = 0;
}

void array_append(Array *a, unsigned element)
{
    if (a->len == a->size) {
        a->size *=2;
        a->values = realloc(a->values, a->size *sizeof(unsigned int));
    }
    a->values[a->len++] = element;
}

void array_free(Array *a)
{
    free(a->values);
    a->values = NULL;
    a->size = 0;
}

void array_print(Array *a)
{
    for (size_t i = 0; i < a->len; i++)
    {
        printf("%u", a->values[i]);
    }
    printf("\n");
}

void reproduce(Array *fish)
{
    int n = 0; // new fish
    for (size_t i = 0; i < fish->len; i++)
    {       
        if (fish->values[i] == 0)
        {
            fish->values[i] = 6;
            n++;
        }
        else 
        {
            fish->values[i] -= 1;
        }
    }

    for (size_t i = 0; i < n; i++)
    {
        array_append(fish, 8);
    }
}

int main()
{
    FILE *file = fopen("input", "r");

    Array fish;
    array_init(&fish, 2);

    int c;
    while( (c = fgetc(file)) != EOF)
    {
        if (c == '\n')
            break;

        if (c != ',')
            array_append(&fish, c - '0');
    }
    fclose(file);

    unsigned int days = 1;
    do {
        reproduce(&fish);
        days++;
    } while (days <= 80);


    printf("count: %zu", fish.len);
    assert(fish.len == 362346);

    array_free(&fish);
    exit(EXIT_SUCCESS);
}
