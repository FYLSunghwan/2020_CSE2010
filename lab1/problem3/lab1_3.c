#include <stdio.h>
#include <stdlib.h>

typedef struct{
	char *name;
	int id;
}student;


int main() {
    FILE *fin = fopen("lab1_3_input.txt", "r");
    FILE *fout = fopen("lab1_3_output.txt", "wt");
    int N, s, e, sum=0;
    student st[101];
    fscanf(fin, "%d", &N);
    for(int i=0;i<N;i++) {
        char* name = malloc(sizeof(char)*100);
        int id;
        fscanf(fin, "%s%d", name, &id);
        st[i].name = name;
        st[i].id = id;
    }

    // Selection Sort
    for(int i=0;i<N-1;i++) {
        for(int j=i+1;j<N;j++) {
            if(st[i].id>st[j].id) {
                student t = st[i];
                st[i] = st[j];
                st[j] = t;
            }
        }
    }

    // Print
    for(int i=0;i<N;i++) fprintf(fout, "%s %d\n", st[i].name, st[i].id);
    return 0;
}