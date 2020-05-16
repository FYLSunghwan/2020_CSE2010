#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* Create Heap
 * Create a heap with the given size.
 *
 * Insert
 * Insert a new key to the max heap. You should find the right position
 * for the new key to maintain the max heap. Print what key you inserted.
 *
 * Find
 * Find the key in the heap. Return 1 if the value exists. Otherwise,
 * return 0.
 *
 * DeleteMax
 * Find Delete the max in root node and reconstruct the heap to maintain
 * the max heap. Print what node you have deleted.
 *
 * PrintHeap
 * Print the entire heap in level order traversal.
 */
typedef struct HeapStruct {
    int Capacity;
    int Size;
    int* Element;
}Heap;

Heap* CreateHeap(int heapSize);
void Insert(Heap *heap, int value);
int Find(Heap *heap, int value);
int DeleteMax(Heap *heap);
void PrintHeap(Heap *heap);
//////////////////////////////////////////////////////////////////////////

FILE* fi;
FILE* fo;

int main(int argc, char* argv[]) {
    if(argc<=2) {
        printf("Usage: ./lab7 INPUT_FILE_NAME OUTPUT_FILE_NAME\n");
        return 0;
    }
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "wt");
    if(fi==NULL || fo==NULL) {
        printf("File IO Failed : Invalid filename\n");
        return 0;
    }
    
    Heap* heap = NULL;
    int heapSize=0;

    char cmd;
    int value, res;

    while((cmd = fgetc(fi))!= EOF) {
        switch(cmd) {
            case 'n':
                fscanf(fi, "%d", &value);
                heap = CreateHeap(value);
                break;

            case 'i':
                fscanf(fi, "%d", &value);
                Insert(heap, value);
                break;

            case 'f':
                fscanf(fi, "%d", &value);
                if(Find(heap, value))
                    fprintf(fo, "%d is in the heap\n", value);
                else
                    fprintf(fo, "%d is not in the heap\n", value);
                break;
            case 'd':
                res = DeleteMax(heap);
                if(res==-1)
                    fprintf(fo, "Delete Error : heap is empty\n");
                else
                    fprintf(fo, "Max Element: %d deleted\n", res);
                break;
            case 'p':
                PrintHeap(heap);
                break;
        }
    }

    free(heap->Element);
    free(heap);

    fclose(fi);
    fclose(fo);
    return 0;
}

Heap* CreateHeap(int heapSize) {
    Heap* heap = (Heap*)(malloc(sizeof(Heap)));
    heap->Element = (int*)(malloc(sizeof(int)*(heapSize+1)));
    heap->Capacity = heapSize;
    heap->Size = 0;
    heap->Element[0] = 1e9;
    return heap;
}

void Insert(Heap *heap, int value) {
    int i;
    if(heap == NULL) {
        fprintf(fo, "Fatal Error : No heap is allocated\n");
        return;
    }
    if(heap->Capacity == heap->Size) {
        fprintf(fo,"Insert Error : heap is full\n");
        return;
    }
    if(Find(heap, value)) {
        fprintf(fo, "%d is already in the heap\n",value);
        return;
    }
    fprintf(fo, "insert %d\n", value);
    for(i=++heap->Size;heap->Element[i/2]<value;i/=2)
        heap->Element[i] = heap->Element[i/2];
    heap->Element[i] = value;
}

int Find(Heap *heap, int value) {
    if(heap == NULL || heap->Size==0)
        return 0;
    for(int i=1;i<=heap->Size;i++) {
        if(heap->Element[i]==value) return 1;
    }
    return 0;
}
int DeleteMax(Heap *heap) {
    if(heap == NULL) {
        fprintf(fo, "Fatal Error : No heap is allocated\n");
        return -1;
    }
    if(heap->Size==0) return -1;

    int i, child;
    int max_elem, last_elem;

    max_elem = heap->Element[1];
    last_elem = heap->Element[heap->Size--];

    for(i=1;i*2<=heap->Size;i=child) {
        child = i*2;
        if(child<heap->Size && heap->Element[child+1] > heap->Element[child])
            child++;
        if(last_elem < heap->Element[child])
            heap->Element[i] = heap->Element[child];
        else break;
    }
    heap->Element[i] = last_elem;
    return max_elem;

}
void PrintHeap(Heap *heap) {
    if(heap == NULL) {
        fprintf(fo, "Fatal Error : No heap is allocated\n");
        return;
    }
    if(heap->Size==0) fprintf(fo, "Print Error : heap is empty");
    for(int i=1;i<=heap->Size;i++) {
        fprintf(fo, "%d ", heap->Element[i]);
    }
    fprintf(fo,"\n");
}