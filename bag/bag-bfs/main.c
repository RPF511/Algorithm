#include "bag_bfs.h"




void main(void){
    HeapType * heap = (HeapType *)malloc(sizeof(HeapType));

    //elements : save each element's weight and price/weight
    int noe = 4;
    int weight[4] = {2,5,10,5};
    int pw[4] = {20,6,5,2};
    int wmax = 16;
    int max = 0;

    //node
    bagnode * head = mkbagnode(0,0,0 + bound(wmax,weight,pw,4),0);
    insert(heap,head -> bound, head);
    
    bfs_bag(heap,&max,wmax,weight,pw,noe);

    printf("%d",max);

    
    free(heap);
}