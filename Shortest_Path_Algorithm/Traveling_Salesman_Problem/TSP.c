//Traveling Salesman Problem
#include <limits.h>
#include "multiplearray.h"
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

//graph
typedef struct graph{
    int size;
    int **edge;
}graph;

void initialize_graph(graph *gr){
    scanf("%d",&gr->size);
    gr->edge = mk_2dim_array(gr->size,gr->size);
}
void delete_graph(graph *gr){
    delete_2dim_array(gr -> edge);
    free(gr);
}

int my_pow(int x,int y){
    int sum;
    for(sum = 1;y>0;y--){
        sum *= x;
    }
    return sum;
}

//set the dp array : set the destination node. dp[i][j] means starts from 'i', via 'j', destination is 'end'. in this example, it's 0;
void set_dp(int **arr, graph *gr, int end){
    for(int i = 0; i<gr->size; i++){
        for(int j = 0; j<my_pow(2,gr->size); j++){
            arr[i][j] = INT_MAX;
        }
    }
    for(int i = 0; i<gr->size; i++){
        arr[i][0] = gr -> edge[i][end];
    }
}

//get the dp[i][j] : used recursion + memoization
//A node that passes through is represented by a bit of an int variable.
//1 means passes that node and 0 means not passing that node. for example, via {node(1),node(3)} is int via = 0x1010
int get_dp(graph * gr, int **dp, int start, int via){
    //printf("-----------------------------\n");
    if(via == 0){
        printf("via is 0 dp[%d][0] is %d\n",start,dp[start][0]);
        return dp[start][0];
    }
    else if(dp[start][via] != INT_MAX){
        printf("dp is calculated [%d][%d] = %d\n",start,via,dp[start][via]);
        return dp[start][via];
    }
    else{
        printf("get_dp(%d,"BYTE_TO_BINARY_PATTERN")\n",start, BYTE_TO_BINARY(via));
        int sum = INT_MAX;
        int bit = 1;
        int temp = INT_MAX;
        int way = INT_MAX;
        
        for(int index=0; index<gr->size;index++){
            printf("checking "BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(bit));
            if((bit & via) != 0){
                printf("index %d gr->edge[%d][%d] : %d\n",index,start,index,gr->edge[start][index]);
                printf("in case "BYTE_TO_BINARY_PATTERN" "BYTE_TO_BINARY_PATTERN"\n",BYTE_TO_BINARY(bit & via),BYTE_TO_BINARY(bit^via));
                if(gr->edge[start][index] != INT_MAX){
                    printf("gr -> edge[%d][%d] + get_dp(%d, "BYTE_TO_BINARY_PATTERN")\n",start,index,index,BYTE_TO_BINARY(via^bit));
                    temp = gr -> edge[start][index] + get_dp(gr, dp, index, via^bit);
                    printf("temp %d\n",temp);
                }
                
                if(temp < sum){
                    printf("dp[%d]["BYTE_TO_BINARY_PATTERN"] sum %d -> temp %d\n",start,BYTE_TO_BINARY(via),sum,temp);
                    sum = temp;
                }
            }
            bit = bit << 1;
            printf("\n");
        }
        printf("recording sum %d to dp[%d]["BYTE_TO_BINARY_PATTERN"]\n",sum,start,BYTE_TO_BINARY(via));
        dp[start][via] = sum;
        printf("dp\n");
        print_2dim_array(dp,gr->size,my_pow(2,gr->size));
        return dp[start][via];
        //if not printing line 89, 91, 92, use this return
        //return dp[start][via] = sum;
    }
    

}

int main(void){
    //example with 4 nodes
    int ex[] = {0,7,5,2,8,0,9,INT_MAX,4,INT_MAX,0,7,3,10,INT_MAX,0};
    graph *map = (graph *)malloc(sizeof(graph));
    int **dp;
    printf("4 node example. input 4.\n");
    initialize_graph(map);
    input_2dim_array(map -> edge, ex, 16);
    dp = mk_2dim_array(map->size, my_pow(2,map->size));
    set_dp(dp, map, 0);

    //printf("edge of the graph\n");
    //print_2dim_array(map -> edge,4,4);
    //printf("\ndp initialized\n");
    //print_2dim_array(dp,4,16);

    /*
    int bit = 1;
    printf(BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(bit));
    bit = bit << 1;
    printf(BYTE_TO_BINARY_PATTERN"\n", BYTE_TO_BINARY(bit));
    */
    printf("\n from 0 via all end 0 is %d\n",get_dp(map, dp, 0, 14));


    delete_2dim_array(dp);
    delete_graph(map);
    return 0;
}