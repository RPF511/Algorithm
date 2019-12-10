#include <stdio.h>
#include <stdlib.h>

typedef struct Bagnode{
    int profit;
    int weight;
    int bound;
    int index;
    struct Bagnode * left, * right;
}bagnode;

typedef struct{
    int heap[100];
    int heapsize;
    bagnode * link[100];
    bagnode * cur;
}HeapType;


void printh(HeapType *h);
void insert(HeapType *h,int node,bagnode * nlink);
int delete(HeapType *h);