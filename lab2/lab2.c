#include <stdio.h>
#include <stdlib.h>

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* Insert                                                               
 * i x -1 : Insert a node with key "x" after the head of the list. 
 *      
 * i x y : Insert a node with key "x" after the node with key "y"    
 * Error message when 'insertion' cannot be performed                 
 * (ex., no the node with key "y")                                    
 *                                                                 
 * Show
 * p : Print entire list(key of node) from beginning to end.
 * 
 * Delete
 * d x : Delete a node with key "x" from the list (free)
 * Error message when 'deletion' cannot be performed.
 * (ex./ no the node with key "x")
 * 
 * Find
 * f x : find a node with key "x" from the list.
 * Error message when 'finding' cannot be performed.
 * (ex., no the node with key "x")
 */
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node
{
    ElementType      element;
    Position         next;
};

List MakeEmpty( List L );
int IsEmpty( List L );
int IsLast( Position P, List L);
void DeleteList( List L );

void Insert( ElementType X, List L, Position P );
void PrintList( List L );
void Delete( ElementType X, List L );
Position Find( ElementType X, List L );
//////////////////////////////////////////////////////////////////////////

FILE *input, *output;

int main(int argc, char* argv[]) {
    char command;
    int key1, key2;
    Position header;
    Position tmp;

    if(argc<=2) {
        printf("Usage: ./lab2 INPUT_FILE_NAME OUTPUT_FILE_NAME\n");
        return 0;
    }

    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    if(input==NULL || output==NULL) {
        printf("File IO Failed : Invalid filename\n");
        return 0;
    }

    header = MakeEmpty(header);

    while(1) {
        command = fgetc(input);
        if(feof(input)) break;
        switch(command) {
            case 'i':       
                fscanf(input, "%d %d", &key1, &key2);
                if(key2==-1) {
                    Insert(key1, header, header);
                }
                else {
                    tmp = Find(key2, header);
                    if(IsLast(tmp, header)) {
                        fprintf(output, "Insertion(%d) Failed: cannot find the location to be inserted\n", key1);
                    }
                    else {
                        tmp = tmp->next;
                        Position newObj = MakeEmpty(header);
                        newObj->element = key1;
                        newObj->next = tmp->next;
                        tmp->next = newObj;
                    }
                }
                break;
            case 'd':
                fscanf(input, "%d", &key1);
                Delete(key1, header);
                break;
            case 'f':
                fscanf(input, "%d", &key1);
                tmp = Find(key1, header);
                if(IsLast(tmp, header)) 
                    fprintf(output, "Finding(%d) Failed: Element %d is not in the list\n", key1, key1);
                else {
                    if(tmp->element>0)
                        fprintf(output, "Key of the previous node %d is %d.\n", key1, tmp->element);
                    else
                        fprintf(output, "Key of the previous node of %d is header.\n", key1);
                }
                break;
            case 'p':
                PrintList(header);
                break;
            default:
                break;
        }
    }
    DeleteList(header);
    fclose(input);
    fclose(output);
    return 0;
}

List MakeEmpty( List L ) {
    Position header = malloc(sizeof(List));
    header->element = 0;
    header->next = NULL;
    return header;
}

int IsEmpty( List L ) {
    return L->next==NULL;
}

int IsLast( Position P, List L) {
    return P->next==NULL;
}

void DeleteList( List L ) {
    Position now = L;
    Position tmp = now->next;
    while(now) {
        tmp = now->next;
        free(now);
        now = tmp;
    }
}

void Insert( ElementType X, List L, Position P ) {
    Position newObj = MakeEmpty(L);
    newObj->next = P->next;
    newObj->element = X;
    P->next = newObj;
}

void PrintList( List L ) {
    Position P = L;
    while(!IsLast(P, L)) {
        P = P->next;
        fprintf(output, "key: %d ", P->element);
    }
    fprintf(output, "\n");
}

void Delete( ElementType X, List L ) {
    Position tmp = Find(X, L);
    if(IsLast(tmp, L)) {
        fprintf(output, "Deletion(%d) Failed: Element %d is not in the list\n", X, X);
    }
    else {
        Position tmp2 = tmp->next;
        tmp->next = tmp2->next;
        free(tmp2);
    }
}

Position Find( ElementType X, List L ) {
    Position p;
    p = L;
    while(p->next != NULL &&
          p->next->element !=X) {
              p = p->next;
          }
    return p;
}