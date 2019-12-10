
#include "maxheap.h"




bagnode * mkbagnode(int profit, int weight, int bound);
int bound(int max, int cur,int *weight, int *pw, int size);

void bfs_bag_node(HeapType * heap, int *max,int wmax, int *weight, int *pw,int noe);
void bfs_bag(HeapType * heap,int *max,int wmax,int *weight, int *pw,int noe);