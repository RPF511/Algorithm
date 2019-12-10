#include "bag_bfs.h"

bagnode * mkbagnode(int profit, int weight, int bound, int index){
    bagnode * temp = (bagnode *)malloc(sizeof(bagnode));
    temp -> profit = profit;
    temp -> weight = weight;
    temp -> bound = bound;
    temp -> index = index;
    temp -> left = NULL;
    temp -> right = NULL;
    return temp;
}

int bound(int max,int * weight, int * pw, int size){
    int cur = 0, res = 0;
    for(int i=0;i<size;i++){
        if(cur >= max){
            break;
        }
        for(int j=0;j<weight[i];j++){
            if(cur < max){
                res += pw[i];
                cur++;
            }
            else{
                break;
            }
        }
    }
    return res;
}

void bfs_bag_node(HeapType * heap, int *max,int wmax, int *weight, int *pw,int noe){
    if(heap -> heapsize > 0){
        delete(heap);
        bagnode * node = heap -> cur;
        int btemp;
        int ptemp;
        printf("%d\n",heap -> heapsize);
        printh(heap);

        //printf("%d %d\n",weight[node -> index + 1], node -> weight);
        if(weight[node -> index + 1] + node -> weight <= wmax){
            printf("%d %d %d",node -> profit,pw[node -> index + 1], weight[node -> index + 1]);
            ptemp = node -> profit + pw[node -> index + 1] * weight[node -> index + 1];
            btemp = ptemp + bound(wmax - (weight[node -> index + 1] + node -> weight),weight + (node -> index + 1),pw + (node -> index + 1), noe - node -> index);
            printf("index %d left profit %d temp %d\n",node -> index + 1,ptemp,btemp);
            node -> left = mkbagnode(ptemp,weight[node -> index + 1] + node -> weight,btemp,node -> index + 1);
            if(node -> left -> profit > *max){
                *max = node -> left -> profit;
            }
            if(node -> index + 1 < noe){
                insert(heap,node -> left -> bound, node -> left);
                printh(heap);
            }
        }

        ptemp = node -> profit;
        btemp = ptemp + bound(wmax - node -> weight,weight + (node -> index + 1),pw + (node -> index + 1), noe - node -> index);
        node -> right = mkbagnode(ptemp,node -> weight,btemp,node -> index + 1);
        printf("index %d right profit %d temp %d\n",node -> index + 1,ptemp,btemp);
        if(node -> right -> profit > *max){
            *max = node -> right -> profit;
        }

        if(node -> index + 1 < noe){
            insert(heap,node -> right -> bound, node -> right);
            printh(heap);
        }
    }
}
void bfs_bag(HeapType * heap,int *max,int wmax,int *weight, int *pw,int noe){
    printf("heapsize %d\n",heap -> heapsize);
    while(heap -> heapsize){
        bfs_bag_node(heap,max,wmax,weight,pw,noe);
        printh(heap);
    }
}