//Traveling Salesman Problem
#include <limits.h>
#include "multiplearray.h"

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

//initialize circular linked list datatype. this is for the path.
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
//num'th after from circular linked liste 0;
circle * circle_next(circle *first, int num){
    circle * temp = first;
    while(num--){
        temp = temp -> after;
    }
    return temp;
}
//copy the circular linked list
void circle_cpy(circle *a, circle *b,int num){
    for(int i=0;i<num;i++){
        circle_next(a,i) -> index = circle_next(b,i) -> index;
    }
}
//print the circular linked list
void print_circle(circle *cir,int start, int num){
    circle *temp = circle_next(cir,start);
    for(int i =0; i<num; i++){
        printf("%d ",temp->index);
        temp = temp -> after;
    }
    printf("\n");
}

//initialize the graph
void initialize_graph(graph *gr){
    scanf("%d",&gr->size);
    gr->edge = mk_2dim_array(gr->size,gr->size);
    gr->stat = 0;
    gr->tsp = mk_2dim_array(gr->size, my_pow(2,gr->size));
    gr->path = initialize_circle(gr->size);
}
//delete graph
void delete_graph(graph *gr){
    delete_2dim_array(gr -> edge);
    delete_2dim_array(gr->tsp);
    free(gr->path);
    free(gr);
}
//mypow
int my_pow(int x,int y){
    int sum;
    for(sum = 1;y>0;y--){
        sum *= x;
    }
    return sum;
}

//set the dp array : set the destination node. dp[i][j] means starts from 'i', via 'j', destination is 'end'. in this example, it's 0;
//A node that passes through is represented by a bit of an int variable.
//1 means passes that node and 0 means not passing that node. for example, via {node(1),node(3)} is int via = 0x1010
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

//get the dp[i][j] : used recursion + memoization
//(gr : graph, start : start node, via : via nodes using bits, stat : for recording path, c_temp : temporary path)
//stat : (number of node - stat) means number of nodes in via. use this variable to save temporary path.
//        for ex) circle_next(c_temp,stat+1) -> index = index;
int cal_dp(graph * gr, int start, int via, int stat, circle *c_temp){  
    //in case via == 0
    if(via == 0){
        //case : the road has been cut off at the end
        if(gr->tsp[start][0] == INT_MAX){
            if(!gr->stat)circle_next(c_temp,stat) -> index = INT_MAX;
            return INT_MAX;
        }
        //case : the road has not been cut off at the end
        else{
            if(!gr->stat)circle_next(gr->path,stat) -> index = start;
            return gr->edge[start][0];
        }
    }
    //already calculated
    else if(gr->tsp[start][via] != INT_MAX){
        return gr->tsp[start][via];
    }
    //not calculated
    else{
        int sum = INT_MAX;   //whole distance
        int bit = 1;
        int temp = INT_MAX;  //temporary distance
        //in this for : pick each nodes from via and calculate each shortest distances
        //save and return 
        for(int index=0; index<gr->size;index++){
            //when (bit & via) != 0) there is index'th bit
            if((bit & via) != 0){
                //when gr->edge[start][index] != INT_MAX, we don't have to calculate them. there is no roads
                if(gr->edge[start][index] != INT_MAX){
                    //save current path to the temporary path variable
                    circle_next(c_temp,stat+1) -> index = index;
                    //calculate gr -> edge[start][index] + dp[start : index][via : via^bit]
                    temp = gr -> edge[start][index] + cal_dp(gr, index, via^bit,stat+1,c_temp);
                }
                //(case : edge[start][index] + dp[start : index][via : via^bit] < current shortest path) -> renew shortest path
                //if temp < 0 , somehow cal_dp was INT_MAX
                if(temp < sum && temp > 0){
                    //copy temporary path to path log
                    circle_cpy(gr->path,c_temp,gr->size);
                    sum = temp;
                }
            }
            //next bit
            bit = bit << 1;
        }
        return gr->tsp[start][via] = sum;
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

    //setting dp
    set_dp(map,0);

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
