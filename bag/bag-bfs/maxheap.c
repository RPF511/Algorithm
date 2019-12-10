#include "maxheap.h"


void printh(HeapType *h){
    for(int i = 1;i<h->heapsize+1;i++)
        printf("%3d ",h->heap[i]);
    printf("\n");
}
void insert(HeapType *h, int node, bagnode * nlink){
    h -> heapsize++;
    if(h -> heapsize == 1){
        h -> heap[1] = node;
        h -> link[1] = nlink;
        //printh(h);
    }
    else{
        h -> heap[h -> heapsize] = node;
        int n, m;
        bagnode * nlink, *mlink;
        for(int i = h->heapsize;i > 1;i/=2){
            n = h -> heap[i];
            nlink = h -> link[i];
            m = h -> heap[i/2];
            mlink = h -> link[i/2];
            if(n > m){
                h->heap[i] = m;
                h->link[i] = mlink;
                h->heap[i/2] = n;
                h->link[i/2] = nlink;
                //printh(h);
            }
        }
    }
}
int delete(HeapType *h){
    int max = h -> heap[1];
    bagnode * maxlink = h -> link[1];
    h -> heap[1] = h -> heap[h -> heapsize];
    h -> link[1] = h -> link[h -> heapsize];
    h -> heapsize--;
    int n;
    int cur;
    bagnode * curlink;
    for(int i = 1;i<h -> heapsize;){
        n = 2*i;
        cur = h -> heap[i];
        curlink = h -> link[i];
        if(h -> heap[n] > h -> heap[n+1]){
            if(h -> heap[n]>cur){
                h -> heap[i] = h -> heap[n];
                h -> link[i] = h -> link[n];
                h -> heap[n] = cur;
                h -> link[n] = curlink; 
            }
            else{
                break;
            }

        }
        else{
            if(h -> heap[++n]>cur){
                h->heap[i]=h->heap[n];
                h->link[i]=h->link[n];
                h->heap[n]=cur;
                h->link[n]=curlink;
            }
            else{
                break;
            }
        }
        i = n;
    }
    h -> cur = maxlink;
    return max;
}