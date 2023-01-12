#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>





double** mk_2dim_array(int m, int n){
    double **temp = (double **)malloc(sizeof(double *)*m);
    temp[0] = (double *)malloc(sizeof(double)*m*n);
    for(int i=1; i<m; i++){
        temp[i] = temp[i-1] + n;
    }
    return temp;
}

void delete_2dim_array(double **arr){
    free(arr[0]);
    free(arr);
}

void print_2dim_array(double **arr, int m, int n){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(arr[i][j] != INT_MAX){
                printf("%lf ",arr[i][j]);
            }
            else{
                printf("MAX ");
        }
        }
        printf("\n");
    }
}

void scanf_2dim_array(double **arr,int m, int n){
    for(int i=0; i<m*n; i++){
        scanf("%lf",arr[0]+i);
    }
}

void normalize_map(double **arr,int n){
    for(int i = 0; i< n; i++){
        int count = 0;
        for(int j= 0; j<n;j++) {if(arr[i][j]) count++;}
        for(int j= 0; j<n;j++) {if(arr[i][j]) arr[i][j] = (double)1 / (double)count;}
    }
}

void calculate_next(double * result, double ** map, double * temp, int size){\
    for(int i = 0; i< size; i++){
        temp[i] = 0;
    }
    for(int i = 0; i< size; i++){
        for(int j = 0; j<size ; j++){
            temp[j] += result[i] * map[i][j];
        }
        
    }


    for(int i = 0; i<size; i++){
        result[i] = temp[i];
    }

}


int main(void){
    int casenum, villagenum, day, temp;
    double * result;
    double ** map;
    double * tempres;

    scanf("%d",&casenum);

    for(int i = 0; i< casenum; i++){
        scanf("%d %d %d", &villagenum, &day, &temp);
        result = (double *)malloc(sizeof(double)*villagenum);
        tempres = (double *)malloc(sizeof(double)*villagenum);
        memset(result, 0, villagenum * sizeof(double));
        memset(tempres, 0, villagenum * sizeof(double));
        result[temp] = 1;
        map = mk_2dim_array(villagenum,villagenum);
        scanf_2dim_array(map,villagenum,villagenum);
        normalize_map(map,villagenum);
        // print_2dim_array(map,villagenum,villagenum);

        for(int i = 0; i<day;i++){
            calculate_next(result,map,tempres,villagenum);
        }

        // for(int i = 0; i< villagenum ; i++){
        //     printf("%10lf ", result[i]);
        // }
        // printf("\n");

        scanf("%d",&day);
        for(int i = 0; i<day;i++){
            scanf("%d",&temp);
            printf("%.10lf ",result[temp]);
        }
        printf("\n");

        free(result);
        delete_2dim_array(map);
        free(tempres);
    }   

    return 0;
}