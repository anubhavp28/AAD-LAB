#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX 100

// For adjacency List
struct edge {
    int v;
    int weight;
    struct edge *next;
};

struct vertex {
    int vid;
    int dist;
};

struct edge *adjList[MAX + 1] = {NULL}; // used as a 1-index array
int V;
int E;

int dist[MAX + 1] = { [0 ... MAX] = 10000}; // 1-based array
int prev[MAX + 1] = { [0 ... MAX] = -1}; // stores the previous node in shortest path   
int pos[MAX + 1] = { [0 ... MAX] = -1}; // stores the position of vertex in heap. 

struct vertex heap[MAX + 1]; // array to store heap
int heapSize = 0;

void runForEveryNeighbour(int u, void (*func)(int, int, int ))
{
    struct edge *p = adjList[u];
    while(p!=NULL) {
        (*func)(u, p->v, p->weight);
        p = p->next;
    }
}
int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

// i, j are index of vertex in heap array
void swapInHeap(int i, int j) {
    struct vertex v = heap[i];
    heap[i] = heap[j];
    heap[j] = v;

    // Update position array
    int p = pos[heap[i].vid];
    pos[heap[i].vid] = pos[heap[j].vid];
    pos[heap[j].vid] = p;
}

int heapifyUp(int index) {
    while (index !=1) {
        if (heap[parent(index)].dist > heap[index].dist ) {
            swapInHeap(parent(index), index);
        }
        else return index;
        index = parent(index);
    }
    return index;
}

int heapifyDown(int i) {
    int min;
    while (i<=heapSize) {
        min = i;
        min = (left(i) <= heapSize && heap[left(i)].dist < heap[min].dist) ? left(i) : min;
        min = (right(i) <= heapSize && heap[right(i)].dist < heap[min].dist) ? right(i) : min;
        if (min == i) return i;
        swapInHeap(i, min);
        i = min;
    }
    return i;
}

int insertHeap(int vertex, int d) {
    heapSize++;
    heap[heapSize].vid = vertex;
    heap[heapSize].dist = d;
    dist[vertex] = d;
    return pos[vertex] = heapifyUp(heapSize);
}

struct vertex extractMin() {
    swapInHeap(1, heapSize);
    heapSize--;
    if (heapSize!=0) 
        heapifyDown(1);
    pos[heap[heapSize + 1].vid] = -1; 
    return heap[heapSize + 1];
}

// updateDistanceInHeap calculates only the new position of the
// vertex in the heap. It does not modify the dist array.
int updateDistanceInHeap(int v, int dist) {
    heap[pos[v]].dist = dist;
    pos[v] = heapifyUp(pos[v]);
    return pos[v];
}

int heapEmpty() {
    return (heapSize < 1) ? 1 : 0;
}

void updateDistance(int u, int v, int w) {
    if (pos[v] != -1 && dist[v] > (dist[u] + w)) {
        dist[v] = dist[u] + w;
        prev[v] = u;
        updateDistanceInHeap(v, dist[v]);
    }
}

void printPath(int v) {
    while (v!=-1) {
        printf("%d ", v);
        v = prev[v];
    }
    printf("\n");
}

int main() {
    int u,v,w;
    struct edge *p;
    struct vertex vv;
    scanf("%d", &V);
    scanf("%d", &E);

    // Build the Adjacency List
    for (int i=0; i<E; i++) {
        scanf("%d %d %d", &u, &v, &w);
        p = (struct edge*)malloc(sizeof(struct edge));
        p->v = v;
        p->weight = w;
        p->next = adjList[u];
        adjList[u] = p;
    }

    // Add every vertex to priority queue
    for (int i=1; i<=V; i++) {
        insertHeap(i, 10000);
    }



    // vertex 1 is our source
    dist[1] = 0;
    updateDistanceInHeap(1, 0);

    while (!heapEmpty()) {

        /*printf("Inside Heap : ");
        for (int i=1; i<=heapSize; i++) {
            printf(" %d dist=%d", heap[i].vid, heap[i].dist);
        }
        printf("\n"); */
        vv = extractMin();
        
        /*for (int i=1; i<=heapSize; i++) {
            printf(" %d dist=%d", heap[i].vid, heap[i].dist);
        }
        printf("\n Removed : ");
        printf( "%d dist=%d\n", vv.vid, vv.dist);
        */
        runForEveryNeighbour(vv.vid, updateDistance);
    }

    for (int i=1; i<=V; i++) {
        printf("dist(%d)=%d\n", i, dist[i]);
        printPath(i);
    }

}
