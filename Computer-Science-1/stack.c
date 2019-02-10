//  Ty Abbott
//  practice stack program

#include <stdio.h>

#define SIZE 50

struct stack{
    int items[SIZE];
    int top;
};

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, int value);
int empty(struct stack* stackPtr);
int pop(struct stack* stackPtr);
int peek(struct stack* stackPtr);


int main()
{
    char* value = 'k';
    printf("%c", value);

    int printNum, work;
    struct stack bigStack;
    initialize(&bigStack);

    work = push(&bigStack, 5);
    work = push(&bigStack, 4);
    work = push(&bigStack, 9);
    work = push(&bigStack, 12);
    work = push(&bigStack, 3);
    printNum = pop(&bigStack);
    printf("Just popped off %d\n", printNum);
    printNum = peek(&bigStack);
    printf("Just peeked %d\n", printNum);
    printNum = pop(&bigStack);
    printf("Just popped off %d\n", printNum);

    return 0;
}

void initialize(struct stack* stackPtr)
{
    stackPtr->top = -1;
}

int push(struct stack* stackPtr, int value)
{
    if(full(stackPtr))
    {
        printf("The stack is full!\n");
        return 0;
    }
    stackPtr->top++;
    stackPtr->items[stackPtr->top]=value;
    return 1;
}

int full(struct stack* stackPtr)
{
    return stackPtr->top+1>=SIZE;
}

int empty(struct stack* stackPtr)
{
    return stackPtr->top == -1;
}

int pop(struct stack* stackPtr)
{
    int val;
    if(empty(stackPtr))
    {
        printf("The stack is empty\n");
        return -1;
    }
    val = stackPtr->items[stackPtr->top];
    stackPtr->items[stackPtr->top]=0;
    stackPtr->top--;
    return val;
}

int peek(struct stack* stackPtr)
{
    if(empty(stackPtr))
    {
        printf("The stack is empty\n");
        return -1;
    }
    return stackPtr->items[stackPtr->top];
}
