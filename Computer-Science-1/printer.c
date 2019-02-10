/* Ty Abbott
    printer.c
    A program designed to practice using Binary Heaps
    and Priority Queues with a printer example */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 35

typedef struct node{
    char job[MAX_LEN];
    int priority;
    struct pqNode* parent;
    struct pqNode* lchild;
    struct pqNode* rchild;
}pqNode;

typedef struct priorityQueue{
    int size;
    pqNode* nodes;
    pqNode* head;
    pqNode* tail;
}pQueue;

pQueue* initPq();
void readInput(FILE *fptr, FILE *wptr, pQueue*);
pQueue* writeToFile(FILE *wptr, int, pQueue*);
pqNode* createNode(char[], int);
pqNode* findLastNode(pqNode*);
pQueue* insertJob(pQueue*, pqNode*);
pQueue* deleteRoot(pQueue*);
void printJob(pqNode*);

int main()
{
    FILE *readFptr, *writeFptr;
    readFptr = fopen("jobs.txt", "r");
    writeFptr = fopen("output.txt", "w");
    if(readFptr == NULL || writeFptr == NULL)
    {
        printf("There was an issue with opening Files\n");
        return 0;
    }
    pQueue *prioQueue = initPq();
    readInput(readFptr, writeFptr, prioQueue);
    free(prioQueue);
    return 0;
}

// Function that when called initializes the Priority Queue
pQueue* initPq()
{
    pQueue* prioQ = (pQueue*)malloc(sizeof(pQueue));
    if(prioQ!=NULL)  //Checks if malloc worked
    {
        prioQ->nodes = NULL;
        prioQ->head = NULL;
        prioQ->tail = NULL;
        return prioQ;
    }
    printf("Could not initialize the Priority Queue");
    return NULL;
}

void readInput(FILE *fptr, FILE *wptr, pQueue *pq)
{
    int time, priority, previousTime=0;
    char fileName[MAX_LEN];
    pqNode *newNode;
    while(fscanf(fptr, "%d %s %d", &time, fileName, &priority) == 3)
    {
        while(previousTime<time)
        {
            pq = writeToFile(wptr, previousTime, pq);
            previousTime++;
            //Go through the times up to where the new job is being added a.k.a. print jobs in priority order.
        }
        newNode = createNode(fileName, priority);
        pq = insertJob(pq, newNode);
    }
}

pQueue* writeToFile(FILE *wptr, int time, pQueue *pq)
{
    fprintf(wptr, "\n\nTime %d\n-----------\n", time);
    if(pq->head->priority<=time)
    {
        fprintf(wptr, "%s has been printed\n\n", pq->head->job);
        pq = deleteRoot(pq);
    }
    else if(pq->head==NULL)
    {
        fprintf(wptr, "are waiting to be printed\n\n");
    }
    else
    {
        fprintf(wptr, "%s\n", pq->head->job);
    }
    return pq;
}

pqNode* createNode(char name[], int priority)
{
    pqNode *node = (pqNode*)malloc(sizeof(pqNode));
    if(node!=NULL)
    {
        node->job = name;
        node->priority = priority;
        node->parent = NULL;
        node->lchild = NULL;
        node->rchild = NULL;
    }
    return node;
}

pqNode* findLastNode(pQueue *pq)
{
    pqNode *tempNode = pQueue->head;
    if(pq->size==0)
    {
        printf("\nPriority Queue is empty\n");
        return NULL;
    }
    else if(pq->size==1)
        return pq->head;
    else
    {
        int count=0, n=pq->size;
        int quickStack[20];
        while(n!=1) //goes through the queue, the number of levels it has.
        {
            quickStack[count] = n%2;  // an even number indicates you have to go left, odd number is right
            n = n/2;
            count++;
        }
        while(count>0)
        {
            if(quickStack[count]==1)
                tempNode = tempNode->rchild;
            else
                tempNode = tempNode->lchild;
            count--;
        }
        return tempNode;
    }
}

pQueue* insertJob(pQueue *pq, pqNode *node)
{
    if(pq==NULL) //if the pQueue is empty
    {
        pq->nodes = node;
        pq->head = node;
        pq->tail = node;
        pq->size = 1;
    }
    else  //if the pQueue is not empty
    {
        pqNode *tempNode = pq->head;
        int count=0, n=pq->size+1, lastVal;
        int quickStack[20];
        while(n!=1) //goes through the queue, the number of levels it has.
        {
            quickStack[count] = n%2;  // an even number indicates you have to go left, odd number is right
            n = n/2;
            count++;
        }
        while(count>0)
        {
            if(quickStack[count]==1)
                tempNode = tempNode->rchild;
            else
                tempNode = tempNode->lchild;
            count--;
        }
        node->parent = tempNode->parent;
        pq->tail = node;
        pq->size++;
    }
    return pq;
}


pQueue* deleteRoot(pQueue *pq)
{
    pqNode *freeNode = pq->head;
    pq->head = pq->tail;
    pqNode *tempNode = pq->head;
    while(tempNode->lchild!=NULL && tempNode->rchild!=NULL)
    {
        if(tempNode->rchild==NULL)
        {
            pq->tail = tempNode->rchild;
            free(freeNode);
            return pq;
        }
        else if(tempNode->rchild>tempNode->lchild)
            tempNode = tempNode->lchild;
        else
            tempNode = tempNode->rchild;
    }
    pq->tail = tempNode;
    free(freeNode);
    return pq;
}

void printJob(pqNode *node)
{
    printf("%s\n" node->job);
    if(node->lchild==NULL && node->rchild==NULL)
        return;
    else if(node->lchild==NULL)
        return printJob(node->rchild);
    else
        return printJob(node->lchild) + printJob(node->rchild);
}
