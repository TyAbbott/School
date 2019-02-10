#include <stdio.h>
#include <stdlib.h>


typedef struct bstnode{
        int data;
        bstnode *leftChild;
        bstnode *rightChild;
    }bstnode;

    typedef struct bTree{
        bstnode *nodes;
        int size;
    }bTree;

void readInput(FILE *fptr, int num, bTree *b);
bTree* initTree();
bTree* populateTree(bTree *b, int num);
int checkBalance(bTree *b)

int main()
{
    bTree binaryTree = initTree();
}

void readInput(FILE *fptr, int numCases, bTree *b)
{
    int i, j, numToAdd, numTimes, isBalanced;
    for(i=0; i<numCases; i++)
    {
        fscanf(fptr, "%d", &numTimes);
        isBalanced = 0;
        for(j=0; j<numTimes; j++)
        {
            fscanf(fptr, "%d", &numToAdd);
            b=populateTree(b, numToAdd);
            isBalanced +=checkBalance(b);
        }
        if(isBalanced==0)
            printf("Tree #%d: KEEP\n", i+1);
        else
            printf("Tree #%d: REMOVE\n", i+1);
    }
}

bTree* initTree()
{
    bTree* bstTree = (bTree*)malloc(sizeof(bTree));
    if(bstTree!= NULL)
    {
        bstTree->nodes = NULL;
        bstTree->size = 0;
        return bstTree;
    }
    printf("Could not initialize the tree\n");
    return NULL;
}

bTree* populateTree(bTree *b, int value)
{
    //go through the different cases, empty or not empty
    //then if value < b->nodes->data go to the left child
    //else if value > b->nodes->data go to the right child
    //else if b->nodes->data is null then put value there, make a new node: set left child and right children to null etc.
}
