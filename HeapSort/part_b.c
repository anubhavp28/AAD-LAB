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

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void Max_Heapify(int *A, int index, int N)
{
    int root=index;
    while (1)
    {
        int left_child = 2*root + 1;
        int right_child = 2*root + 2;
        int _max = root;
        if (left_child < N)
            _max = (A[_max] > A[left_child]) ? _max : left_child;
        if (right_child < N)
            _max = (A[_max] > A[right_child]) ? _max : right_child;
        if (_max != root)
        {
            swap(&A[_max],&A[root]);
            root = _max;
        }
        else return;
    }
}

void Insert_Max_Heap(int *A, int value, int size)
{
    A[size] = value;
    
    int index = size - 1;
    while (index != 0 && A[parent(index)] < A[index])
    {
        swap(&A[parent(index)], &A[index]);
        index = parent(index);
    }
}

void Build_Max_Heap(int *A, int N)
{
    for (int i=0; i<N; i++)
        Insert_Max_Heap(A, A[i], i);
}

void Heap_Sort(int *A, int N)
{
    while (N > 0)
    {
        printf(" %d ", A[0]);
        swap(&A[0], &A[N-1]);
        N--;
        Max_Heapify(A, 0, N);
    }
}

int main()
{
    int size = 0;
    printf("Number of elements : ");
    scanf("%d", &size);
    
    int A[size];
    for (int i=0; i<size; i++)
        scanf("%d",&A[i]);
    
    Build_Max_Heap(A, size);
    
    Heap_Sort(A, size);
}
