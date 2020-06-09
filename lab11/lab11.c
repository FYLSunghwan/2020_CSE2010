#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* Insert
 * Insert value to HashTable using the solution
 *
 * Delete
 * Delete the value from HashTable.
 *
 * Find
 * Find the value from HashTable.
 *
 * printTable
 * Print all values of HashTable.
 *
 * Hash
 * Convert value to hash key using the solution.
 */
typedef struct ListNode *Position;
typedef Position List;
typedef struct HashTbl *HashTable;

struct ListNode{
    int Element;
};
struct HashTbl{
    int TableSize;
    List* TheLists;
};

void Insert(HashTable H, int value, int solution);
void Delete(HashTable H, int value, int solution);
int Find(HashTable H, int value, int solution);
void printTable(HashTable H);
int Hash(int value, int Size, int i, int solution);
//////////////////////////////////////////////////////////////////////////

FILE* fi;
FILE* fo;

int main(int argc, char* argv[]) {
    if(argc<=2) {
        printf("Usage: ./lab11 INPUT_FILE_NAME OUTPUT_FILE_NAME\n");
        return 0;
    }
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "wt");
    if(fi==NULL || fo==NULL) {
        printf("File IO Failed : Invalid filename\n");
        return 0;
    }

    char sol_s[128], cmd;
    int val, solution;
    HashTable table = (HashTable)malloc(sizeof(struct HashTbl));

    fscanf(fi, "%s", sol_s);
    solution = (sol_s[0]=='L'?1:2);

    fscanf(fi, "%d", &val);
    table->TableSize = val;
    table->TheLists = (List*)malloc(val*sizeof(List));
    for(int i=0;i<val;i++) table->TheLists[i] = NULL;

    for(int i=0;i<val;i++)

    while(fscanf(fi,"%c",&cmd) != EOF) {
        switch(cmd) {
            case 'i':
                fscanf(fi, "%d", &val);
                Insert(table, val, solution);
                break;

            case 'd':
                fscanf(fi, "%d", &val);
                Delete(table, val, solution);
                break;

            case 'f':
                fscanf(fi, "%d", &val);
                Find(table, val, solution);
                break;

            case 'p':
                printTable(table);
                break;
        }
    }

    fclose(fi);
    fclose(fo);
    return 0;
}

void Insert(HashTable H, int value, int solution) {
    int hashval = Hash(value, H->TableSize, 1, 0);
    if(H->TheLists[hashval] == NULL) {
        H->TheLists[hashval] = (List)malloc(sizeof(struct ListNode));
        H->TheLists[hashval]->Element = value;
        fprintf(fo, "Inserted %d\n", value);
    }
    else {
        int cnt=1;
        while(H->TheLists[hashval] != NULL && H->TheLists[hashval]->Element != value)
            hashval = Hash(value, H->TableSize, cnt++, solution);

        if(H->TheLists[hashval])
            fprintf(fo, "Already exists\n");
        else {
            H->TheLists[hashval] = (List)malloc(sizeof(struct ListNode));
            H->TheLists[hashval]->Element = value;
            fprintf(fo, "Inserted %d\n", value);
        }
    }
}

void Delete(HashTable H, int value, int solution) {
    int hashval = Hash(value, H->TableSize, 1, 0);
    if(H->TheLists[hashval] == NULL) {
        fprintf(fo, "%d not exists\n", value);
    }
    else {
        int cnt = 1;
        while(H->TheLists[hashval] && H->TheLists[hashval]->Element != value)
            hashval = Hash(value, H->TableSize, cnt++, solution);

        if(H->TheLists[hashval] == NULL)
            fprintf(fo, "%d not exists\n", value);
        else {
            free(H->TheLists[hashval]);
            H->TheLists[hashval] = NULL;
            fprintf(fo, "Deleted %d\n", value);
        }
    }
}

int Find(HashTable H, int value, int solution) {
    int hashval = Hash(value, H->TableSize, 1, 0);
    if(H->TheLists[hashval] == NULL) {
        fprintf(fo, "Not found\n");
        return 0;
    }
    else {
        int cnt = 1;
        while(H->TheLists[hashval] != NULL && H->TheLists[hashval]->Element != value)
            hashval = Hash(value, H->TableSize, cnt++, solution);

        if(H->TheLists[hashval] == NULL) {
            fprintf(fo, "Not found\n");
            return 0;

        }
        else {
            fprintf(fo, "hash index: %d\n", hashval);
            return hashval;
        }
    }
}

void printTable(HashTable H) {
    for(int i=0;i<H->TableSize;i++) {
        if(H->TheLists[i]==NULL) fprintf(fo, "0 ");
        else fprintf(fo, "%d ", H->TheLists[i]->Element);
    }
    fprintf(fo,"\n");
}

int Hash(int value, int Size, int i, int solution) {
    if(solution==1)
        return (value + i) % Size;
    else if(solution==2)
        return (value + i*i) % Size;
    else
        return value % Size;
}