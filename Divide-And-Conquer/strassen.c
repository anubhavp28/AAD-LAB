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

matrix *zero_matrix(unsigned int size)
{
    matrix *t = (matrix *)malloc(sizeof(matrix) + sizeof(int *) * size);
    t->size = size;
    for (unsigned int i=0; i<size; i++)
    { 
        t->rptr[i] = (int *)malloc(sizeof(int) * size);
        for (unsigned int j=0; j<size; j++) 
            t->rptr[i][j] = 0;
    }
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
            C->rptr[i][j] += A->rptr[i][j] + B->rptr[i][j];
}

void matdiff(matrix *A, matrix *B, matrix *C, unsigned int size)
{
    for (unsigned int i=0; i<size; i++)
        for (unsigned int j=0; j<size; j++)
            C->rptr[i][j] += A->rptr[i][j] - B->rptr[i][j];
}

/* matmul() assumes that matrix C is a zero matrix */
void matmul(matrix *A, matrix *B, matrix *C, unsigned int size)
{
    if (size==1)
    {
        C->rptr[0][0] = A->rptr[0][0] * B->rptr[0][0];
        return;
    }

    matrix *S[10];
    for (int i=0; i<10; i++)
        S[i] = zero_matrix(size / 2);


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

    matdiff(b[0][1], b[1][1], S[0], size / 2);
    matsum(a[0][0], a[0][1], S[1], size / 2);
    matsum(a[1][0], a[1][1], S[2], size / 2);
    matdiff(b[1][0], b[0][0], S[3], size / 2);
    matsum(a[0][0], a[1][1], S[4], size / 2);
    matsum(b[0][0], b[1][1], S[5], size / 2);
    matdiff(a[0][1], a[1][1], S[6], size / 2);
    matsum(b[1][0], b[1][1], S[7], size / 2);
    matdiff(a[0][0], a[1][0], S[8], size / 2);
    matsum(b[0][0], b[0][1], S[9], size / 2);

    matrix *P[7];
    for (int i=0; i<7; i++)
        P[i] = zero_matrix(size / 2); // Needed to be zero for matmul()

    matmul(a[0][0], S[0], P[0], size / 2);
    matmul(S[1], b[1][1], P[1], size / 2);
    matmul(S[2], b[0][0], P[2], size / 2);
    matmul(a[1][1], S[3], P[3], size / 2);
    matmul(S[4], S[5], P[4], size / 2);
    matmul(S[6], S[7], P[5], size / 2);
    matmul(S[8], S[9], P[6], size / 2);

    matsum(P[4], P[5], c[0][0], size / 2);
    matdiff(P[3], P[1], c[0][0], size / 2);

    matsum(P[0], P[1], c[0][1], size / 2);

    matsum(P[2], P[3], c[1][0], size / 2);
    
    matdiff(P[4], P[6], c[1][1], size / 2);
    matdiff(P[0], P[2], c[1][1], size / 2);


    for (int i=0; i<10; i++)
        free_matrix(S[i]);

    for (int i=0; i<7; i++)
        free_matrix(P[i]);

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
    matrix *A = new_matrix(N);
    matrix *B = new_matrix(N);
    matrix *C = zero_matrix(N);

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
