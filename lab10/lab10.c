#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define INF 1e9

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* CreateGraph
 * Create a graph with nodes.
 *
 * printShortestPath
 * Print the shortest path for the given path
 *
 * createMinHeap
 * Create min heap
 *
 * insertToMinHeap
 * Insert a new vertex to heap
 *
 * deleteMin
 * Delete the smallest distance node for calculation.
 */
typedef struct Node {
    int vertex;
    int dist;
    int prev;
}Node;
typedef struct Graph {
    int size;
    int** vertices;
    Node* nodes;
}Graph;
typedef struct Heap {
    int Capacity;
    int Size;
    Node* Element;
}Heap;

Graph CreateGraph(int size);
void printShortestPath(Graph g);
Heap* createMinHeap(int heapSize);
void insertToMinHeap(Heap* minHeap, int vertex, int distance);
Node deleteMin(Heap* minHeap);

Node CreateNode(int vertex, int dist, int prev);
int Idx(Graph graph, int x);
int heapIdx(Heap* heap, int x);
void update(Heap* heap, int vertex, int dist);
void path(Graph graph, int idx);
//////////////////////////////////////////////////////////////////////////

FILE* fi;
FILE* fo;

int main(int argc, char* argv[]) {
    if(argc<=2) {
        printf("Usage: ./lab10 INPUT_FILE_NAME OUTPUT_FILE_NAME\n");
        return 0;
    }
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "wt");
    if(fi==NULL || fo==NULL) {
        printf("File IO Failed : Invalid filename\n");
        return 0;
    }

    Graph g;
    int size;

    fscanf(fi, "%d\n",&size);
    g = CreateGraph(size+1);
    int n1, n2, w;
    while(fscanf(fi, "%d-%d-%d", &n1, &n2, &w)!=EOF) {
        g.vertices[n1][n2] = w;
    }
    printShortestPath(g);

    free(g.nodes);
    for(int i=0;i<g.size;i++) free(g.vertices[i]);
    free(g.vertices);
    fclose(fi);
    fclose(fo);
}

Graph CreateGraph(int size) {
    Graph g;
    g.nodes = (Node*)malloc(sizeof(Node)*size);
    g.vertices = (int**)malloc(sizeof(int*)*size);
    g.size = size;
    for(int i=0;i<size;i++) {
        g.vertices[i] = (int*)malloc(sizeof(int)*size);
        g.nodes[i].vertex = i;
        for(int j=0;j<size;j++) g.vertices[i][j]=0;
    }
    return g;
}

void printShortestPath(Graph g) {
    Heap* heap = createMinHeap(g.size);
    for(int i=1;i<g.size;i++) {
        g.nodes[i].dist = INT_MAX;
        g.nodes[i].prev = -1;
    }
    g.nodes[1].dist = 0;
    for(int i=1;i<g.size;i++) {
        if(g.vertices[1][i]) {
            g.nodes[i].dist = g.vertices[1][i];
            g.nodes[i].prev = 1;
            insertToMinHeap(heap, g.nodes[i].vertex, g.nodes[i].dist);
        }
    }

    Node now;
    int now_i;
    while(heap->Size>0) {
        now = deleteMin(heap);
        now_i = Idx(g, now.vertex);
        for(int i=1;i<g.size;i++) {
            if(g.vertices[now_i][i]!=0) {
                int nCost = now.dist + g.vertices[now_i][i];
                if(nCost < g.nodes[i].dist) {
                    g.nodes[i].dist = nCost;
                    g.nodes[i].prev = now.vertex;
                    update(heap, g.nodes[i].vertex, g.nodes[i].dist);
                }
            }
        }
    }

    for(int i=2;i<g.size;i++) {
        if(g.nodes[i].prev == -1) {
            fprintf(fo, "Cannot reach to node %d.\n", i);
            continue;
        }
        path(g, i);
        fprintf(fo, "%d (cost: %d)\n", g.nodes[i].vertex, g.nodes[i].dist);
    }
}

Heap* createMinHeap(int heapSize) {
    Heap* heap = (Heap*)(malloc(sizeof(Heap)));
    heap->Element = (Node*)(malloc(sizeof(Node)*(heapSize)));
    heap->Capacity = heapSize;
    heap->Size = 0;
    return heap;
}

void insertToMinHeap(Heap* minHeap, int vertex, int distance) {
    int i;
    if(minHeap == NULL) {
        fprintf(fo, "Fatal Error : No heap is allocated\n");
        return;
    }
    if(minHeap->Capacity == minHeap->Size) {
        fprintf(fo,"Insert Error : heap is full\n");
        return;
    }
    for(i=++(minHeap->Size);minHeap->Element[i/2].dist>distance;i/=2)
        minHeap->Element[i] = minHeap->Element[i/2];
    minHeap->Element[i].dist = distance;
    minHeap->Element[i].vertex = vertex;
}

Node deleteMin(Heap* minHeap) {
    Node node;
    node.dist = -1;
    if(minHeap->Size==0) return node;

    int i, child;
    Node min_elem, last_elem;

    min_elem = minHeap->Element[1];
    last_elem = minHeap->Element[minHeap->Size--];

    for(i=1;i*2<=minHeap->Size;i=child) {
        child = i*2;
        if(child<minHeap->Size && minHeap->Element[child+1].dist < minHeap->Element[child].dist)
            child++;
        if(last_elem.dist > minHeap->Element[child].dist)
            minHeap->Element[i] = minHeap->Element[child];
        else break;
    }
    minHeap->Element[i] = last_elem;
    return min_elem;
}

Node CreateNode(int vertex, int dist, int prev) {
    Node node;
    node.vertex = vertex;
    node.dist = dist;
    node.prev = prev;
    return node;
}

int Idx(Graph graph, int x) {
    int i;
    for(i=1;i<graph.size;i++) {
        if(graph.nodes[i].vertex == x) return i;
    }
    return -1;
}

int heapIdx(Heap* heap, int x) {
    int i;
    for(i=1;i<heap->Size;i++) {
        if(heap->Element[i].vertex == x) return i;
    }
    return -1;
}
void update(Heap* heap, int vertex, int dist) {
    int child, idx = heapIdx(heap, vertex);
    heap->Element[idx].dist = dist;
    for(int i=1; i>1 && i*2 <= heap->Size; i=child) {
        child = i*2;
        if(child+1 <= heap->Size && heap->Element[child+1].dist < heap->Element[i].dist)
            ++child;
        if(heap->Element[child].dist < heap->Element[i].dist) {
            Node node = heap->Element[i];
            heap->Element[i] = heap->Element[child];
            heap->Element[child] = node;
        }
    }
}
void path(Graph graph, int idx) {
    if(graph.nodes[idx].prev != 1) path(graph, graph.nodes[idx].prev);
    fprintf(fo, "%d->", graph.nodes[idx].prev);
}