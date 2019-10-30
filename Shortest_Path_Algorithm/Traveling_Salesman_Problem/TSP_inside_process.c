//Traveling Salesman Problem
#include <limits.h>
#include "multiplearray.h"
//Print bits
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

//struct circular linked list
typedef struct circle{
    int index;
    struct circle *before;
    struct circle *after;
}circle;
//graph
typedef struct graph{
    int stat;
    int size;
    int **edge;
    int **tsp;
    circle *path;
}graph;


circle * initialize_circle(int num){
    circle *first = (circle *)malloc(sizeof(circle));
    circle *fore = first;
    for(int i=0;i<num-1;i++){
        circle *temp = (circle *)malloc(sizeof(circle));
        fore -> after = temp;
        temp -> before = fore;
        fore = temp;
    }
    first -> before = fore;
    fore -> after = first;
    return first;
}

circle * circle_next(circle *first, int num){
    circle * temp = first;
    while(num--){
        temp = temp -> after;
    }
    return temp;
}

int my_pow(int x,int y){
    int sum;
    for(sum = 1;y>0;y--){
        sum *= x;
    }
    return sum;
}
//copy the circular linked list
void circle_cpy(circle *a, circle *b,int num){
    for(int i=0;i<num;i++){
        circle_next(a,i) -> index = circle_next(b,i) -> index;
    }
}

void print_circle(circle *cir,int start, int num){
    circle *temp = circle_next(cir,start);
    for(int i =0; i<num; i++){
        printf("%d ",temp->index);
        temp = temp -> after;
    }
    printf("\n");
}

void initialize_graph(graph *gr){
    scanf("%d",&gr->size);
    gr->edge = mk_2dim_array(gr->size,gr->size);
    gr->stat = 0;
    gr->tsp = mk_2dim_array(gr->size, my_pow(2,gr->size));
    gr->path = initialize_circle(gr->size);
}
void delete_graph(graph *gr){
    delete_2dim_array(gr -> edge);
    delete_2dim_array(gr->tsp);
    free(gr->path);
    free(gr);
}


void set_dp(graph *gr, int end){
    for(int i = 0; i<gr->size; i++){
        for(int j = 0; j<my_pow(2,gr->size); j++){
            gr -> tsp[i][j] = INT_MAX;
        }
    }
    for(int i = 0; i<gr->size; i++){
        gr -> tsp[i][0] = gr -> edge[i][end];
    }
}

int cal_dp(graph * gr, int start, int via, int stat,circle *c_temp){
    printf("-----------------------------\n");
    if(via == 0){
        printf("via is 0 gr->tsp[%d][0] is %d\n",start,gr->tsp[start][0]);
        if(gr->tsp[start][0] == INT_MAX){
            if(!gr->stat)circle_next(c_temp,stat) -> index = INT_MAX;
            return INT_MAX;
        }
        else{
            if(!gr->stat)circle_next(gr->path,stat) -> index = start;
            return gr->edge[start][0];
        }
    }
    else if(gr->tsp[start][via] != INT_MAX){
        printf("gr->tsp is calculated [%d][%d] = %d\n",start,via,gr->tsp[start][via]);
        return gr->tsp[start][via];
    }
    else{
        printf("get_gr->tsp(%d,"BYTE_TO_BINARY_PATTERN")\n",start, BYTE_TO_BINARY(via));
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
                    circle_next(c_temp,stat+1) -> index = index;
                    print_circle(c_temp,0,gr->size);
                    printf("gr -> edge[%d][%d] + cal_dp(%d, "BYTE_TO_BINARY_PATTERN")\n",start,index,index,BYTE_TO_BINARY(via^bit));
                    temp = gr -> edge[start][index] + cal_dp(gr, index, via^bit,stat+1,c_temp);
                    printf("temp %d\n",temp);
                }
                
                if(temp < sum && temp > 0){
                    circle_cpy(gr->path,c_temp,gr->size);
                    printf("cpy\n");
                    print_circle(gr->path,0,gr->size);
                    printf("gr->tsp[%d]["BYTE_TO_BINARY_PATTERN"] sum %d -> temp %d\n",start,BYTE_TO_BINARY(via),sum,temp);
                    sum = temp;
                }
            }
            bit = bit << 1;
            printf("\n");
        }
        printf("recording sum %d to gr->tsp[%d]["BYTE_TO_BINARY_PATTERN"]\n",sum,start,BYTE_TO_BINARY(via));
        gr->tsp[start][via] = sum;
        print_2dim_array(gr->tsp,gr->size,my_pow(2,gr->size));
        return gr->tsp[start][via];
        //if not printing line 89, 91, 92, use this return
        //return gr->tsp[start][via] = sum;
    }
    

}

int main(void){
    //example with 4 nodes
    int ex[] = {0,7,5,2,8,0,9,INT_MAX,4,INT_MAX,0,7,3,10,INT_MAX,0};

    //initialize graph
    graph *map = (graph *)malloc(sizeof(graph));
    printf("4 node example. input 4.\n");
    initialize_graph(map);
    input_2dim_array(map -> edge, ex, 16);
    
    //temp circular linked list
    circle * c_temp = initialize_circle(map->size);


    //first state
    printf("edge of the graph\n");
    print_2dim_array(map -> edge,4,4);
    printf("\ndp initialized\n");
    //setting dp
    set_dp(map,0);
    print_2dim_array(map->tsp,4,16);

    //calculate and print the result
    printf("\ndistance from 0 via all end 0 is %d\n",cal_dp(map, 0, 14, 0, c_temp));
    printf("path ");
    print_circle(map->path,0,map->size);
    printf("\n-----dp after process-------\n");
    print_2dim_array(map->tsp,map->size,my_pow(2,map->size));

    //free memory
    delete_graph(map);
    free(c_temp);
    return 0;
}