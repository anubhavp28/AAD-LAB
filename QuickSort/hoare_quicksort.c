#include <stdio.h>

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
        quicksort(A, start, pivot_index - 1);
        quicksort(A, pivot_index + 1, end);
    }
}

int main()
{
    int A[] = {3, 5, -6, 55, 98, -65, 35, 445};
    int n = sizeof(A)/sizeof(A[0]);
    quicksort(A, 0, n-1);
    for (int i=0; i<n; i++)
        printf(" %d ", A[i]);
    return 0;
}
