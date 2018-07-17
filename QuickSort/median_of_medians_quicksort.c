#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
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

int partition(int A[], int start, int end, int pivotIndex)
{
    int pivotValue = A[pivotIndex];
    swap(&A[pivotIndex], &A[end]);
    int j = start;
    for (int i=start; i<end; i++)
    {
        if (A[i] < pivotValue)
        {
            swap(&A[j], &A[i]);
            j++;
        }
    }
    swap(&A[j], &A[end]);
    return j;
}

int partition5(int arr[], int start, int end)
{
   int n = end - start + 1;
   int i, key, j;
   for (i = start; i<=end; i++)
   {
       key = arr[i];
       j = i-1;
 
       while (j >= 0 && arr[j] > key)
       {
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }

}


int Select(int list[], int left, int right)
{
    while(1)
    {
        if (left == right)
            return left;
            
         if (right - left < 5)
         return partition5(list, left, right);
     
        for (int i=left; i<=right; i += 5)
        {
         int subRight = i + 4;
         if (subRight > right)
             subRight = right;

         int median5 = partition5(list, i, subRight);
         swap(&list[median5], &list[left + (int)floor((i - left)/5)]);
        }
        int pivotIndex = Select(list, left, left + floor((right - left) / 5));     
        
        pivotIndex = partition(list, left, right, pivotIndex);
        int n = (left - right)/2;
        if (n == pivotIndex)
            return pivotIndex;
        else if (n < pivotIndex)
            right = pivotIndex - 1;
        else
            left = pivotIndex + 1;
    }
}

/* Hoare Partition Scheme */
int qs_partition(int A[], int start, int end)
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
        int pivot_index = qs_partition(A, start, end);
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
