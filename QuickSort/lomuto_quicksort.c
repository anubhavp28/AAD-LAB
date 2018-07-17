#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Lomuto Partition Scheme */
int partition(int A[], int start, int end)
{
    int pivot = A[end];
    int j = start;
    for (int i=start; i<end; i++)
    {
        if (A[i] < pivot)
        {
            swap(&A[j], &A[i]);
            j++;
        }
    }
    swap(&A[j], &A[end]);
    return j;
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
