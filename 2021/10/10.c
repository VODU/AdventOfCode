#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACKSIZE 64

typedef struct Stack {
    int top;
    char data[STACKSIZE];
} Stack;

bool stack_is_full(Stack *stack)
{
    if (stack->top == STACKSIZE)
    {
        return true;
    }
    return false;
}

bool stack_is_empty(Stack *stack)
{
    if (stack->top == -1)
    {
        return true;
    }
    return false;
}

char stack_peek(Stack *stack)
{
    return stack->data[stack->top];
}

void stack_push(Stack *stack, char element)
{
    if (!stack_is_full(stack))
    {
        stack->top += 1;
        stack->data[stack->top] = element;
    }
    else
    {
        printf("Error, stack is full");
    }
}

char stack_pop(Stack *stack)
{
    if (!stack_is_empty(stack))
    {
        char element = stack->data[stack->top];
        stack->top -= 1;
        return element;
    }
    else
    {
        printf("Error, stack is empty");
        return '\0';
    }
}

int error_score(const char c)
{
    switch (c)
    {
        case ')':
            return 3;
        case ']':
            return 57;
        case '}':
            return 1197;
        case '>':
            return 25137;
        default:
            return 0;
    }
}

char open_bracket(const char close_bracket)
{
    switch(close_bracket)
    {
        case ')':
            return '(';
        case ']':
            return '[';
        case '}':
            return '{';
        case '>':
            return '<';
        default:
            return '\0';
    }
}

int syntax_error_score(const char *buffer)
{
    Stack brackets = {.top = -1, .data = {0}};
    for (int i; i < strlen(buffer); i++)
    {
        char c = buffer[i];
        switch (c)
        {
            case '(':
            case '[':
            case '{':
            case '<':
            {
                stack_push(&brackets, c);
                break;
            }
            case ')':
            case ']':
            case '}':
            case '>':
            {
                char ic = open_bracket(c);
                char p = stack_peek(&brackets);

                if ( ic == p )
                {
                    stack_pop(&brackets);
                }
                else 
                {
                    return error_score(c);
                }
                break;
            }
        }
    }
    return 0;
}

int main(void)
{
    FILE *file = fopen("test", "r");
    char buffer[32] = {0};
    
    int score = 0;
    while( fgets(buffer, 32, file) != NULL )
    {
        score += syntax_error_score(buffer);
    }

    printf("score: %d", score);

    fclose(file);
    exit(EXIT_SUCCESS);
}
