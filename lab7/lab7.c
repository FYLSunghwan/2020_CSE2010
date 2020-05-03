#include <stdio.h>
#include <stdlib.h>
#include <time.h>

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* init
 * Initialize all sets to sets and maze_print.
 * 
 * union
 * Union two sets.
 * 
 * find
 * Find the set including the number  and return the representative member
 * of the set.
 * 
 * createMaze
 * Generate a maze that includes a path from Start position to End position
 * WITHOUT any cycles. You can generate such a maze by randomly choosing
 * a cell and direction. Use Union-Find ADT. For random number generation,
 * use the library functions.
 * 
 * printMaze
 * Print the resulting maze.
 * 
 * freeMaze
 * Free memory of the maze.
 */
typedef struct _DisjointSet{
    int size_maze;
    int *ptr_arr;
}DisjointSets;

void init(DisjointSets *sets, DisjointSets* maze_print, int num);
void uni(DisjointSets *sets, int i, int j);
int find(DisjointSets *sets, int i);
void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num);
void printMaze(DisjointSets *maze_print, int num);
void freeMaze(DisjointSets *sets, DisjointSets *maze_print);
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

    srand((unsigned int)time(NULL));
    int num;
    fscanf(fi, "%d", &num);
    DisjointSets* sets = (DisjointSets*)malloc(sizeof(struct _DisjointSet));
    DisjointSets* maze_print = (DisjointSets*)malloc(sizeof(struct _DisjointSet));
    init(sets, maze_print, num);
    createMaze(sets,maze_print,num);
    printMaze(maze_print, num);
    freeMaze(sets,maze_print);
    fclose(fi);
    fclose(fo);
    return 0;
}

void init(DisjointSets *sets, DisjointSets* maze_print, int num) {
    sets->size_maze = num*num+1;
    sets->ptr_arr = (int*)malloc((num*num+1)*sizeof(int));
    for(int i=1;i<sets->size_maze;i++) sets->ptr_arr[i] = 0;
    maze_print->size_maze = 2*num*(num-1);
    maze_print->ptr_arr = (int*)malloc((maze_print->size_maze)*sizeof(int));
    for(int i=0;i<maze_print->size_maze;i++) maze_print->ptr_arr[i] = 0;
}

void uni(DisjointSets *sets, int i, int j) {
    i = find(sets, i);
    j = find(sets, j);
    if(i==j) return;
    if(sets->ptr_arr[j] < sets->ptr_arr[i]) sets->ptr_arr[i] = j;
    else {
        if(sets->ptr_arr[j] == sets->ptr_arr[i]) sets->ptr_arr[i]--;
        sets->ptr_arr[j] = i;
    }
}

int find(DisjointSets *sets, int i) {
    if(sets->ptr_arr[i] <=0) return i;
    else return (sets->ptr_arr[i] = find(sets, sets->ptr_arr[i]));
}

void createMaze(DisjointSets *sets, DisjointSets *maze_print, int num) {
    while(find(sets,1)!=find(sets,num*num)) {
        int rnd = rand()%(maze_print->size_maze);
        if(maze_print->ptr_arr[rnd]) continue;
        int a = num * (rnd/(2*num-1))+rnd%(2*num-1) + 1;
        int b;
        if(rnd%(2*num-1)>=(2*num-1)/2) {
            a-=((2*num-1)/2);
            b = a+num;
        }
        else b=a+1;
        if(find(sets,a) == find(sets,b)) continue;
        uni(sets,a,b);
        maze_print->ptr_arr[rnd] = 1;
    }
}
void printMaze(DisjointSets *maze_print, int num) {
    fprintf(fo,"+");
    for(int i=0;i<num;i++) fprintf(fo,"-+");
    fprintf(fo,"\n");
    int cnt=0, mode=0;
    while(cnt<maze_print->size_maze) {
        if(cnt==0) fprintf(fo, "  ");
        else if(cnt%(2*num-1)==0) {
            fprintf(fo,"\n| ");
            mode =!mode;
        }
        else if((cnt%(2*num-1))==((2*num-1)/2)) {
            fprintf(fo, "|\n+");
            mode=!mode;
        }

        if(maze_print->ptr_arr[cnt]==0)
            fprintf(fo,"%s",mode?"-+":"| ");
        else fprintf(fo,"%s",mode?" +":"  ");
        ++cnt;
    }
    fprintf(fo,"\n+");
    for(int i=0;i<num;i++) fprintf(fo,"-+");
}

void freeMaze(DisjointSets *sets, DisjointSets *maze_print) {
    free(sets->ptr_arr);
    free(sets);
    free(maze_print->ptr_arr);
    free(maze_print);
}