/* Ty Abbott
    ExpEvaluator.c
    Expression Evaluator which calculates infix and postfix
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

    typedef struct stacknode{
        char data;
        struct stacknode *next;
    }stacknode;

    typedef struct stack{
        stacknode *top;
        stacknode *nodes;
        int size;
    }stack;

stack* initStack();
stack* push(stack *s, char c);
char pop(stack *s);
char peek(stack *s);
int isEmpty(stack *s);
void evaluatePostfix(char *);
void evaluateInfix(char *);

int main(int argc, char *argv[])
{
    int num, i;
    FILE *fptr = fopen(argv[1], "r");
    FILE *f = fopen("output.txt", "w");
    char nums[20];
    stack *stackT = initStack();
    if(f==NULL||fptr==NULL)
    {
        printf("Error opening the file\n");
        return 0;
    }
    fscanf(fptr, "%d", &i);
    while(i!=0)
    {
        fgets(nums, 20, fptr);
        if(i==1)
            evaluateInfix(nums);
        else
            evaluatePostfix(nums);
        fscanf(fptr, "%d", &i);
    }

}

stack* initStack()
{
    stack* theStack = (stack*)malloc(sizeof(stack));
    if(theStack != NULL)
    {
        theStack->nodes = NULL;
        theStack->top = NULL;
        theStack->size = 0;
        return theStack;
    }
    printf("Could not initialize the stack\n");
    return NULL;
}

stack* push(stack *s, char c)
{
    stack *temptr = s;
    stacknode* newNode = (stacknode*)malloc(sizeof(stacknode));
    newNode->data=c;
    if(s==NULL)
    {
        newNode->next=NULL;
        s->nodes = newNode;
        return s;
    }
    newNode->next=temptr->top;
    s->nodes = newNode;
    return s;
}

char pop(stack *s)
{
    stack *temptr;
    temptr = s;
    char output = temptr->top->data;

    if(temptr->top->next==NULL)
        s = NULL;
    else
        s->nodes = s->nodes->next;

    free(temptr);
    return output;
}

char peek(stack *s)
{
    if(s!=NULL)
        return s->top->data;
    else
        return ' ';
}

int IsEmpty(stack *s)
{
    if(s==NULL)
        return 1;
    else
        return 0;
}

void evaluatePostfix(char *c)
{
    stack *nums = initStack();
    char numb1, numb2;
    int i, num1, num2, last, size = sizeof(c)/sizeof(c[0]);
    for(i=0; i<size; i++)
    {
        if(c[i]=='+'||c[i]=='-'||c[i]=='*'||c[i]=='/')
        {
            numb1 = pop(nums);
            numb2 = pop(nums);
            num1 = numb1-'0';
            num2 = numb2-'0';
            if(c[i]=='+')
                push(nums,num2+num1+'0');
            else if(c[i]=='-')
                push(nums,num2-num1+'0');
            else if(c[i]=='*')
                push(nums,num2*num1+'0');
            else
                push(nums,num2/num1+'0');
        }
        else
            push(nums,c[i]);
    }
    last = pop(nums);
}

void evaluateInfix(char *c)
{
    stack *nums = initStack();
}
