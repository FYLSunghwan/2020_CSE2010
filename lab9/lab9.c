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

int idx(Graph graph, int x) {
    int i;
    for(i=0;i<graph->size;i++) {
        if(graph->node[i]==x) return i;
    }
    return -1;
}
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

    int x, y, res, read;
    char inp[1024] = {0, }, tmp;
    char* ptr = inp;


    fgets(inp, 1024, fi);
    ptr = inp;
    while(sscanf(ptr, "%d%n", &x, &read) == 1) {
        graph->node[graph->size++] = x;
        ptr += read;
    }

    fgets(inp, 1024, fi);
    ptr = inp;
    while(sscanf(ptr, "%d%c%d%n", &x, &tmp, &y, &read) == 3) {
        InsertEdge(graph, x, y);
        ptr += read;
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
    return graph;
}

void InsertEdge(Graph G, int a, int b) {
    a = idx(G, a);
    b = idx(G, b);
    G->matrix[a][b] = 1;
}

void TopSort(Graph G) {
    Queue queue = MakeNewQueue(MAXN);
    int indegree[MAXN] = {0,};
    for(int i=0;i<G->size;i++) {
        for(int j=0;j<G->size;j++) {
            indegree[i] += G->matrix[j][i];
        }
        if(indegree[i]==0) Enqueue(queue, i);
    }

    while(queue->qsize) {
        int now = Dequeue(queue);
        fprintf(fo, "%d ", G->node[now]);
        for(int i=0;i<G->size;i++) {
            if(i==now) continue;
            G->matrix[now][i]=0;
            indegree[i]--;
            if(indegree[i]==0) Enqueue(queue, i);
        }
    }

    free(queue->key);
    free(queue);
}
Queue MakeNewQueue(int X) {
    Queue queue = (Queue)malloc(sizeof(struct _Queue));
    queue->key = (int*)malloc(sizeof(int)*MAXN);
    queue->first = queue->qsize = queue->rear = 0;
    queue->max_queue_size = MAXN-1;
    return queue;
}
void Enqueue(Queue Q, int X) {
    if(Q->rear == Q->max_queue_size) {
        fprintf(fo, "Queue is full.\n");
        return;
    }
    Q->qsize++;
    Q->key[Q->rear++] = X;
}
int Dequeue(Queue Q) {
    if(Q->qsize==0) {
        fprintf(fo, "Queue is Empty.\n");
        return -1;
    }
    Q->qsize--;
    Q->first++;
    return Q->key[Q->first-1];
}