#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int comp;
int exchange;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    exchange++;
}

void heapify(int arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]){
        largest = left;
        comp++;
    }
    if (right < n && arr[right] > arr[largest]){
        largest = right;
        comp++;
    }
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

int partition(int array[], int low, int high)
{

    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            comp++;
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(int array[], int low, int high)
{
    if (low < high)
    {
        comp++;
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}
int partition_random_pivot(int array[], int low, int high)
{
    int size = high-low;
    int index = rand()%size + low;
    int pivot = array[index];
    swap(&array[index],&array[high]);
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            comp++;
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort_random_pivot(int array[], int low, int high)
{
    if (low < high)
    {
        comp++;
        int pi = partition_random_pivot(array, low, high);
        quickSort_random_pivot(array, low, pi - 1);
        quickSort_random_pivot(array, pi + 1, high);
    }
}

int partition_middle_of_3(int array[], int low, int high)
{
    int lowv = array[low];
    int highv = array[high];
    int middleidx = (high+low)/2;
    int middlev = array[middleidx];
    int index;
    comp++;
    if(lowv < highv){
        comp++;
        if(middlev < lowv){
            index = low;
        }
        else{
            comp++;
            if(middlev < highv){
                index = middleidx;
            }else{
                index = high;
            }
        }
    }else{
        comp++;
        if(middlev < highv){
            index = high;
        }else{
            comp++;
            if(middlev<lowv){
                index = middleidx;
            }else{
                index = low;
            }
        }
    }

    int pivot = array[index];
    swap(&array[index],&array[high]);
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            comp++;
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort_middle_of_3(int array[], int low, int high)
{
    if (low < high)
    {
        comp++;
        int pi = partition_middle_of_3(array, low, high);
        quickSort_middle_of_3(array, low, pi - 1);
        quickSort_middle_of_3(array, pi + 1, high);
    }
}

int partition_middle_expect(int array[], int low, int high, int midvalue, int logvalue)
{
    int index = high;
    int highcomp = abs(array[high] - midvalue);
    int tempidx = high;
    int tempcomp = highcomp;
    int size = high -low;
    int loop = logvalue;
    for(int i =0;i< loop; i++){
        tempidx = low + rand()%size;
        comp++;
        tempcomp = abs(array[tempidx] - midvalue);
        if(tempcomp < highcomp){
            highcomp = tempcomp;
            index = tempidx;
        }
    }

    int pivot = array[index];
    swap(&array[index],&array[high]);
    int i = (low - 1);
    for (int j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            comp++;
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort_middle_expect(int array[], int low, int high, int midvalue, int logvalue)
{
    if (low < high)
    {
        comp++;
        int pi = partition_middle_expect(array, low, high, low+midvalue, logvalue);
        quickSort_middle_expect(array, low, pi - 1, midvalue/2, logvalue/2);
        quickSort_middle_expect(array, pi + 1, high, midvalue/2, logvalue/2);
    }
}

void printArray(int * array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

void copy_array(int * temp, int * origin, int size){
    for(int i = 0; i<size; i++){
        temp[i] = origin[i];
    }
}

int main()
{
    srand ( time(NULL) );
    printf("%22s %24s %28s %25s %25s\n","heap","quick", "quick random", "quick middle 3","quick mid expect");
    printf("%5s  %7s %7s %7s  %7s %7s %7s  %7s %7s %7s  %7s %7s %7s  %7s %7s %7s \n","n","comp","swap","time","comp","swap","time","comp","swap","time","comp","swap","time","comp","swap","time");
    int * origin_array;
    int * temp_array;

    int compset[5] = {0,0,0,0,0};
    int swapset[5] = {0,0,0,0,0};
    int timeset[5] = {0,0,0,0,0};

    int start;
    int size_array[10] = {100,200,500,1000,2000,3000,4000,5000,10000,20000};

    // int size_array[1] = {100};
    for(int i =0; i<10; i++){
        int size = size_array[i];
        origin_array = (int *)malloc(sizeof(int)*size);
        temp_array = (int *)malloc(sizeof(int)*size);
        for(int re = 0 ; re<5; re++){
            compset[re] = 0;
            swapset[re] = 0;
            timeset[re] = 0;
        }
        for(int t = 0; t<50; t++)
        {
            for(int j=0; j<size; j++){
                int temp = rand()%size;
                // printf("%d ",temp);
                origin_array[j] = temp;
                // printf("%d ",origin_array[j]);
            }
            
            start = clock();
            copy_array(temp_array,origin_array,size);
            comp = 0; exchange = 0;
            heapSort(temp_array, size);
            compset[0] += comp;
            swapset[0] += exchange;
            timeset[0] += (clock()-start);
            // printf("%8d %7d %7ld ",comp, exchange, (clock()-start));

            start = clock();
            copy_array(temp_array,origin_array,size);
            comp = 0; exchange = 0;
            quickSort(temp_array, 0, size - 1);
            compset[1] += comp;
            swapset[1] += exchange;
            timeset[1] += (clock()-start);
            // printf("%8d %7d %7ld ",comp, exchange, (clock()-start));

            start = clock();
            copy_array(temp_array,origin_array,size);
            comp = 0; exchange = 0;
            quickSort_random_pivot(temp_array, 0, size - 1);
            compset[2] += comp;
            swapset[2] += exchange;
            timeset[2] += (clock()-start);
            // printf("%8d %7d %7ld ",comp, exchange, (clock()-start));

            start = clock();
            copy_array(temp_array,origin_array,size);
            comp = 0; exchange = 0;
            quickSort_middle_of_3(temp_array, 0, size - 1);
            compset[3] += comp;
            swapset[3] += exchange;
            timeset[3] += (clock()-start);
            // printf("%8d %7d %7ld ",comp, exchange, (clock()-start));


            start = clock();
            copy_array(temp_array,origin_array,size);
            comp = 0; exchange = 0;
            quickSort_middle_expect(temp_array,0,size-1,size/2,(int)log2((double)size));
            compset[4] += comp;
            swapset[4] += exchange;
            timeset[4] += (clock()-start);
            // printf("%8d %7d %7ld ",comp, exchange, (clock()-start));
        }
        printf("%5d ",size);
        for(int r =0; r<5;r++){
            printf("%8d %7d %7d ",compset[r]/50, swapset[r]/50, timeset[r]/50);
        }
        
        printf("\n");

        free(origin_array);
        free(temp_array);
    }


}
