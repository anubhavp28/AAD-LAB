#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int parent(int i)
{
    return (i-1)/2;
}

void Shift_Up(int *A, int index)
{
    int i=index;
    while (i!=0 && A[parent(i)] < A[i])
    {
        swap(&A[parent(i)],&A[i]);
        i = parent(i);
    }
}

void Build_Max_Heap(int *A, int N)
{
    for (int i=0; i<N; i++)
        Shift_Up(A, i);
}

int main()
{
    int A[] = {3,-5,6,8,7,4,2,3,6,55,14,-125,23};
    int N = sizeof(A)/sizeof(A[0]);
    Build_Max_Heap(A,N);
    for (int i=0; i<N; i++)
        printf(" %d ",A[i]);
}
