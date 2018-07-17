#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "sys/time.h" 

struct timeval time_start, time_end;
struct timezone tz; 
long int cpu_time=0;
int t1=0,t2=0;

int ar[50000];

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Hoare Partition Scheme */
int partition(int A[], int start, int end)
{
    int pivot = A[start];
    int low = start - 1;
    int high = end + 1;
    while(1)
    {
        do {
            low += 1;
        } while( A[low] < pivot);
        do {
            high -= 1;
        } while( A[high] > pivot);
        if (low < high)
            swap(&A[low], &A[high]);
        else return high;
    }
}

int quicksort(int A[], int start, int end)
{
    if (start < end)
    {
        int pivot_index = partition(A, start, end);
        quicksort(A, start, pivot_index);
        quicksort(A, pivot_index + 1, end);
    }
}

int main(int argc, char *argv[])
{
    int num = atoi(argv[1]);
    if (num > 50000)
        return 1;

    FILE *fp;
    fp = fopen("random.txt", "r");
    
    for (int i=0; i<num; i++)
        fscanf(fp, "%d", &ar[i]);

    fclose(fp);
   
    t1=gettimeofday(&time_start,&tz); 
    
    quicksort(ar, 0, num-1);
    
    t2=gettimeofday(&time_end,&tz); 

    cpu_time = ((time_end.tv_sec*1000000)+ time_end.tv_usec)-((time_start.tv_sec*1000000)+time_start.tv_usec);
    
    printf("CPU time for quicksort = %ld microsecs.= %9.6f secs.\n",cpu_time,(float)cpu_time/1000000);


    fp = fopen("sorted.txt", "w");
    for (int i=0; i<num; i++)
        fprintf(fp, "%d\n", ar[i]);
    fclose(fp);

    return 0;    
}
