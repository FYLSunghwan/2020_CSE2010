#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXN 1000

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* CreateGraph
 * Create a graph with nodes. All input nodes will be positive numbers.
 * 
 * InsertEdge
 * Insert a edge.
 * 
 * TopSort
 * Print the graph by topological sort. Sort the smaller number key
 * if same priority.
 * 
 * MakeNewQueue
 * Create a new queue with the size of X.
 * 
 * Enqueue
 * Insert a new element at the end of the element in the queue.
 * 
 * Dequeue
 * Pop the node in the front.
 */
typedef struct _Queue* Queue;
struct _Queue {
    int* key;
    int first;
    int rear;
    int qsize;
    int max_queue_size;
};

typedef struct _Graph* Graph;
struct _Graph {
    int* node;
    int size;
    int** matrix;
};

Graph CreateGraph(int* nodes);
void InsertEdge(Graph G, int a, int b);
void TopSort(Graph G);
Queue MakeNewQueue(int X);
void Enqueue(Queue Q, int X);
int Dequeue(Queue Q);
//////////////////////////////////////////////////////////////////////////

FILE* fi;
FILE* fo;

int main(int argc, char* argv[]) {
    if(argc<=2) {
        printf("Usage: ./lab9 INPUT_FILE_NAME OUTPUT_FILE_NAME\n");
        return 0;
    }
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "wt");
    if(fi==NULL || fo==NULL) {
        printf("File IO Failed : Invalid filename\n");
        return 0;
    }

    int* nodes = (int*)malloc(sizeof(int)*MAXN);
    Graph graph = CreateGraph(nodes);

    int x, y, res;

    while(res = fscanf("%d",&x)) {
        graph->node[graph->size++] = x;
    }
    fflush(fi);
    while(res = scanf("%d-%d",&x, &y)) {
        InsertEdge(graph, x, y);
    }
    fprintf(fo, "  ");
    for(int i=0;i<graph->size;i++) {
        fprintf(fo, "%-2d", graph->node[i]);
    }
    fprintf(fo, "\n");
    for(int i=0;i<graph->size;i++) {
        fprintf(fo, "%-2d", graph->node[i]);
        for(int j=0;j<graph->size;j++) {
            fprintf(fo,"%-2d", graph->matrix[i][j]);
        }
        fprintf(fo, "\n");
    }
    fprintf(fo,"\n");
    TopSort(graph);

    free(queue->key);
    free(queue);
    for(int i=0;i<MAXN;i++) {
        free(graph->matrix[i]);
    }
    free(graph->matrix);
    free(graph->node);
    free(graph);

    fclose(fi);
    fclose(fo);
    return 0;
}

Graph CreateGraph(int* nodes) {
    Graph graph = (Graph)malloc(sizeof(struct _Graph));
    graph->node = nodes;
    graph->size = 0;
    graph->matrix = (int**)malloc(sizeof(int*)*MAXN);
    for(int i=0;i<MAXN;i++) {
        graph->matrix[i] = (int*)malloc(sizeof(int)*MAXN);
    }
}

void InsertEdge(Graph G, int a, int b) {
    G->matrix[a][b] = 1;
    G->matrix[b][b]++;
}

void TopSort(Graph G) {
    Queue queue = MakeNewQueue(MAXN);
    for(int i=0;i<G->size;i++) {
        if(G->matrix[i][i]==0) {
            Enqueue(Q, i);
        }
    }

    while(queue->qsize) {
        int now = Dequeue(Q);
        for(int i=0;i<G->size;i++) {
            if(i==now) continue;
            fprintf(fo, "%d ", now);
            G->matrix[now][i]=0;
            G->matrix[i][i]--;
            if(G->matrix[i][i]==0) Enqueue(Q, i);
        }
    }

    free(queue->key);
    free(queue);
}
Queue MakeNewQueue(int X);
void Enqueue(Queue Q, int X);
int Dequeue(Queue Q);