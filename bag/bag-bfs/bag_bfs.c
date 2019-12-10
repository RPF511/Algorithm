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
        printf("\nnode got %p\n",node);
        printf("profit %d weight %d bound %d\nheap ",node -> profit, node -> weight, node -> bound);
        printh(heap);
        int btemp;
        int ptemp;

        //printf("%d %d\n",weight[node -> index + 1], node -> weight);
        if(weight[node -> index + 1] + node -> weight <= wmax){
            //printf("%d %d %d",node -> profit,pw[node -> index + 1], weight[node -> index + 1]);
            ptemp = node -> profit + pw[node -> index] * weight[node -> index];
            //printf("boundmax %d\n",wmax - (weight[node -> index] + node -> weight));
            btemp = ptemp + bound(wmax - (weight[node -> index] + node -> weight),weight + (node -> index + 1),pw + (node -> index + 1), noe - node -> index);
            printf("index %d left profit %d bound %d\n",node -> index,ptemp,btemp);
            if(btemp <= node -> bound && btemp > 0){
                node -> left = mkbagnode(ptemp,weight[node -> index] + node -> weight,btemp,node -> index + 1);
                if(node -> left -> profit > *max){
                    *max = node -> left -> profit;
                }
                if(node -> index + 1 < noe && node -> left != NULL && node -> left -> bound >= *max){
                    insert(heap,node -> left -> bound, node -> left);
                }
            }
            printf("heap ");
            printh(heap);
        }

        ptemp = node -> profit;
        //printf("%d %d\n",wmax - node -> weight, noe - node -> index);
        //printf("bound %d\n",bound(wmax - node -> weight,weight + (node -> index + 1),pw + (node -> index + 1), noe - node -> index));
        btemp = ptemp + bound(wmax - node -> weight,weight + (node -> index+1),pw + (node -> index+1), noe - node -> index -1);
        printf("index %d right profit %d bound %d\n",node -> index,ptemp,btemp);
        
        if(btemp <= node -> bound && btemp > 0){
            node -> right = mkbagnode(ptemp,node -> weight,btemp,node -> index + 1);
            if(node -> right -> profit > *max){
                *max = node -> right -> profit;
            }
            if(node -> index + 1 < noe && node -> right != NULL && node -> right -> bound >= *max){
                insert(heap,node -> right -> bound, node -> right);
                
            }
        }
        printf("heap ");
        printh(heap);
    }
}
void bfs_bag(HeapType * heap,int *max,int wmax,int *weight, int *pw,int noe){
    printf("heapsize %d\n",heap -> heapsize);
    while(heap -> heapsize){
        bfs_bag_node(heap,max,wmax,weight,pw,noe);
        //printh(heap);
    }
}