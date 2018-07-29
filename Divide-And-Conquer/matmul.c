#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct _matrix{
    unsigned int size;    
    int *rptr[]; // ( uses C99 Flexible Array Member ) array of pointer to rows
} matrix;

matrix *new_matrix(unsigned int size)
{
    matrix *t = (matrix *)malloc(sizeof(matrix) + sizeof(int *) * size);
    t->size = size;
    for (unsigned int i=0; i<size; i++) 
        t->rptr[i] = (int *)malloc(sizeof(int) * size);
    return t;
}

matrix *upper_left(matrix *p)
{
    matrix *t = (matrix *)malloc(sizeof(matrix) + sizeof(int *) * (p->size/2));
    t->size = p->size/2;
    for (unsigned int i=0; i<t->size; i++) 
        t->rptr[i] = p->rptr[i];
    return t;
}

matrix *upper_right(matrix *p)
{
    matrix *t = (matrix *)malloc(sizeof(matrix) + sizeof(int *) * (p->size/2));
    t->size = p->size/2;
    for (unsigned int i=0; i<t->size; i++) 
        t->rptr[i] = &p->rptr[i][t->size];
    return t;
}

matrix *lower_left(matrix *p)
{
    matrix *t = (matrix *)malloc(sizeof(matrix) + sizeof(int *) * (p->size/2));
    t->size = p->size/2;
    for (unsigned int i=0; i<t->size; i++) 
        t->rptr[i] = p->rptr[t->size + i];
    return t;
}

matrix *lower_right(matrix *p)
{
    matrix *t = (matrix *)malloc(sizeof(matrix) + sizeof(int *) * (p->size/2));
    t->size = p->size/2;
    for (unsigned int i=0; i<t->size; i++) 
        t->rptr[i] = &p->rptr[t->size + i][t->size];
    return t;
}

bool free_matrix(matrix *ptr)
{
    for (unsigned int i=0; i<ptr->size; i++)
        free(ptr->rptr[i]);
    free(ptr);
    return true;
}

void matsum(matrix *A, matrix *B, matrix *C, unsigned int size)
{
    for (unsigned int i=0; i<size; i++)
        for (unsigned int j=0; j<size; j++)
            C->rptr[i][j] = A->rptr[i][j] + B->rptr[i][j];
}

void matmul(matrix *A, matrix *B, matrix *C, unsigned int size)
{
    if (size==1)
    {
        C->rptr[0][0] = A->rptr[0][0] * B->rptr[0][0];
        return;
    }

    matrix *X[8];
    for (int i=0; i<8; i++)
        X[i] = new_matrix(size / 2);

    /*
        +-----+-----+     +-----+-----+     +-----+-----+
        | A00 | A01 |     | B00 | B01 |     | C00 | C01 |
        |     |     |     |     |     |     |     |     |
        +-----+-----+  X  +-----+-----+  =  +-----+-----+   
        | A10 | A11 |     | B10 | B11 |     | C10 | C11 |
        |     |     |     |     |     |     |     |     |
        +-----+-----+     +-----+-----+     +-----+-----+   
        
    */

    matrix *a[2][2];
    matrix *b[2][2];
    matrix *c[2][2];

    a[0][0] = upper_left(A);
    a[0][1] = upper_right(A);
    a[1][0] = lower_left(A);
    a[1][1] = lower_right(A);

    b[0][0] = upper_left(B);
    b[0][1] = upper_right(B);
    b[1][0] = lower_left(B);
    b[1][1] = lower_right(B);

    c[0][0] = upper_left(C);
    c[0][1] = upper_right(C);
    c[1][0] = lower_left(C);
    c[1][1] = lower_right(C);

    matmul(a[0][0], b[0][0], X[0], size / 2);
    matmul(a[0][1], b[1][0], X[1], size / 2);
    matmul(a[0][0], b[0][1], X[2], size / 2);
    matmul(a[0][1], b[1][1], X[3], size / 2);
    matmul(a[1][0], b[0][0], X[4], size / 2);
    matmul(a[1][1], b[1][0], X[5], size / 2);
    matmul(a[1][0], b[0][1], X[6], size / 2);
    matmul(a[1][1], b[1][1], X[7], size / 2);

    matsum(X[0], X[1], c[0][0], size / 2);
    matsum(X[2], X[3], c[0][1], size / 2);
    matsum(X[4], X[5], c[1][0], size / 2);
    matsum(X[6], X[7], c[1][1], size / 2);
    
    for (int i=0; i<8; i++)
        free_matrix(X[i]);

    for (int i=0; i<2; i++)
        for (int j=0; j<2; j++)
        {
            /* We don't want to use free_matrix here, as it will release memory pointed by
            row pointers (ie. the memory of the original A, B, C matrices). */
            free(a[i][j]);
            free(b[i][j]);
            free(c[i][j]);
        }    

}

int main()
{   
    int N = 1 << 3; // 8
    matrix *A = new_matrix(8);
    matrix *B = new_matrix(8);
    matrix *C = new_matrix(8);

    srand(time(NULL));
    printf(" Printing A \n");
    for (unsigned int i=0; i<N; i++)
    {
        for (unsigned int j=0; j<N; j++)
        {
            A->rptr[i][j] = rand() % 10;
            printf(" %d ", A->rptr[i][j]);
        }
        printf("\n");
    }

    printf("\n Printing B \n");
    for (unsigned int i=0; i<N; i++)
    {
        for (unsigned int j=0; j<N; j++)
        {
            B->rptr[i][j] = rand() % 10;
            printf(" %d ", B->rptr[i][j]);
        }
        printf("\n");
    }

    matmul(A, B, C, N);

    printf("\n \n Printing A * B \n");
    for (unsigned int i=0; i<N; i++)
    {
        for (unsigned int j=0; j<N; j++)
        {
            printf(" %d ", C->rptr[i][j]);
        }
        printf("\n");
    }

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}
