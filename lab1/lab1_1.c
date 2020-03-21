#include <stdio.h>
int main() {
    FILE *fin = fopen("lab1_1_input.txt", "r");
    FILE *fout = fopen("lab1_1_output.txt", "wt");
    int N, ar[101], s, e, sum=0;
    fscanf(fin, "%d", &N);
    for(int i=0;i<N;i++) fscanf(fin, "%d", ar+i);
    fscanf(fin, "%d%d", &s, &e);
    for(int i=s;i<=e;i++) sum += ar[i];
    fprintf(fout, "%d", sum);
    return 0;
}