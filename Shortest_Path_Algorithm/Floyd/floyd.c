#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "multiplearray.h"

typedef struct graph{
    int *node;
    int node_num;
    int **w;
    int **f;
    int **path;
}graph;
void initialize_edge(int **arr,int num){
    for(int i=0; i<num; i++){
        for(int j=0; j<num; j++){
            if(i == j){
                arr[i][j] = 0;
            }
            else{
                arr[i][j] = INT_MAX;
            }
        }
    }
}
void initialize_graph(graph *gr,int num){
    gr -> node_num = num;
    gr -> node = (int *)malloc(sizeof(int)*num);
    for(int i = 0; i<num; i++){
        gr -> node[i] = 0;
    }
    gr -> w = mk_2dim_array(num, num);
    gr -> f = mk_2dim_array(num, num);
    gr -> path = mk_2dim_array(num, num);

    //initialize edge of the 2dimention array
    initialize_edge(gr->w,num);
    initialize_edge(gr->f,num);
    initialize_edge(gr->path,num);
    //since node index starts from 0 in this algorithm, all elements in path should be not '0' (for example, MAX) when initialized
    for(int i=0; i<num; i++){
        gr->path[i][i] = INT_MAX;
    }

}

void init_w_coor(graph *gr, int temp[3]){
    gr -> w[temp[0]][temp[1]] = temp[2];
    gr -> f[temp[0]][temp[1]] = temp[2];
}

void free_graph(graph *gr){
    free(gr -> node);
    delete_2dim_array(gr -> w);
    delete_2dim_array(gr -> f);
    delete_2dim_array(gr -> path);
    free(gr);
}

void print_gr(graph *gr,int stat){
    int temp;
    for(int i=0;i<gr->node_num;i++){
        for(int j=0;j<gr->node_num;j++){
            if(stat){
                if(gr->f[i][j] == INT_MAX){
                    printf("MAX ");
                }
                else{
                    printf("%3d ",gr->f[i][j]);
                }
                
            }
            else{
                if(gr->w[i][j] == INT_MAX){
                    printf("MAX ");
                }
                else{
                    printf("%3d ",gr->w[i][j]);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

int floyd(graph *gr){
    for(int i=0; i<gr->node_num; i++){
        for(int j=0; j<gr->node_num; j++){
            for(int k=0; k<gr->node_num; k++){
                if(gr->f[j][i] + gr -> f[i][k] > 0 && gr->f[j][i] + gr -> f[i][k] < gr -> f[j][k]){
                    gr -> path[j][k] = i;
                    gr -> f[j][k] = gr->f[j][i] + gr -> f[i][k];
                    /*
                    printf("%d %d %d\n",i,j,k);
                    print_gr(gr,1);
                    */
                }
            }
        }
    }
}

void get_path(graph *gr, int i, int j){
    if(gr->path[i][j] != INT_MAX){
        get_path(gr,i,gr->path[i][j]);
        get_path(gr,gr->path[i][j],j);
    }
    else{
        if(gr->w[i][j] != INT_MAX){
            printf("%d -> ",j);
        }
        else{
            printf("there is no road");
        }
    }
}

void print_path(graph *gr, int i, int j){
    printf("%d -> ",i);
    get_path(gr,i,j);
    printf("\n");
}

int main(void){
    int num;
    int temp[3];
    graph *gr = (graph *)malloc(sizeof(graph));
    scanf("%d",&num);
    initialize_graph(gr,num);
    //printf("number of init : ");
    scanf("%d",&num);
    for(int i=0;i<num;i++){
        scanf("%d %d %d",&temp[0],&temp[1],&temp[2]);
        init_w_coor(gr,temp);
    }
    printf("floyd before\n");
    print_2dim_array(gr->f,gr->node_num,gr->node_num);
    floyd(gr);
    printf("\nfloyd after\n");
    print_2dim_array(gr->f,gr->node_num,gr->node_num);
    printf("\npath\n");
    print_2dim_array(gr->path,gr->node_num,gr->node_num);
    printf("\nex) path from 4 to 2\n");
    print_path(gr,4,2);
    free_graph(gr);
    return 0;
}

/* example
5
10
0 1 1
0 3 1
0 4 5
1 0 9
1 2 3
1 3 2
2 3 4
3 2 2
3 4 3
4 0 3
*/