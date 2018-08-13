#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1000

typedef struct _node {
    char ch;
    int freq;
    struct _node *left;
    struct _node *right;
} node;

node *pqueue[MAX];
int size = 0;

void swap(node **a, node **b)
{
    node *t = *b;
    *b = *a;
    *a = t;
}

int parent(int i)
{
    return i/2;
}

int left(int i) 
{
    return 2*i;
}

int right(int i)
{
    return 2*i + 1;
}

void minheapify(int i)
{
    if (parent(i)==0)
        return;
    
    int f = pqueue[parent(i)]->freq;
    if (pqueue[i]->freq < f)
    {
        swap(&pqueue[parent(i)], &pqueue[i]);
        minheapify(parent(i));
    }
}

node *insert_pqueue(char ch, int freq)
{
    node *t = (node *)malloc(sizeof(node));
    t->left = t->right = NULL;
    t->ch = ch;
    t->freq = freq;
    pqueue[++size] = t;
    minheapify(size);
    return t;
}

node *remove_pqueue()
{
    if (size==0)
        return NULL;
    swap(&pqueue[1], &pqueue[size]);
    size--;
    int i = 1;
    while (1)
    {
        int min = i;
        if (left(i) <= size && pqueue[left(i)]->freq < pqueue[i]->freq) {
            min = left(i);
        }
        if (right(i) <= size && pqueue[right(i)]->freq < pqueue[min]->freq) {
            min = right(i);
        }
        if (min==i) break;
        swap(&pqueue[i], &pqueue[min]);
        i = min;
    }
    return pqueue[size + 1];
}

void prefix(node *p, FILE *f) {
    if (p==NULL)
        return;
    
    fprintf(f, "%c ", p->ch);
    if (p->left) 
        fprintf(f, "%c ", p->left->ch);
    else
        fprintf(f, "NULL ");
    if (p->right) 
        fprintf(f, "%c ", p->right->ch);
    else
        fprintf(f, "NULL ");
    fprintf(f, "%d\n", p->freq);
    prefix(p->left, f);
    prefix(p->right, f);
}

void assign_code(node *p, char code[], FILE *f) {
    if (p==NULL) return;
    if (p->left==NULL && p->right==NULL)
    {    
        fprintf(f, "%c %s \n", p->ch, code);
        return;
    }
    char left_code[100];
    char right_code[100];
    strcpy(left_code, code);
    strcat(left_code, "0");
    strcpy(right_code, code);
    strcat(right_code, "1");
    if (p->left)
        assign_code(p->left, left_code, f);
    if (p->right)
        assign_code(p->right, right_code, f); 
}

int main()
{
    FILE *freqfile = fopen("frequency.txt", "r");
    if (!freqfile)
        return 1;
    char ch;
    int freq;
    while (fscanf(freqfile, "%c %d\n", &ch, &freq)!=-1)
    {
        insert_pqueue(ch, freq);
    }
    fclose(freqfile);
   /*insert_pqueue('a', 13);
    insert_pqueue('b', 6);
    insert_pqueue('c', 7);
    insert_pqueue('d', 3);
    insert_pqueue('e', 10);
    insert_pqueue('f', 15);
    insert_pqueue('g', 13);*/

    while (size>1)
    {
        node *a = remove_pqueue();
        node *b = remove_pqueue();
        node *c = insert_pqueue('m', a->freq + b->freq);
        c->left = a;
        c->right = b;
    }

    node *k = remove_pqueue();

    FILE *treefile = fopen("tree.txt", "w");
    if (!treefile)
        return 2;
    prefix(k, treefile);

    FILE *codefile = fopen("codes.txt", "w");
    if (!codefile)
        return 3;
    assign_code(k, "0", codefile);
    fclose(codefile);
}




