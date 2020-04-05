#include <stdio.h>
int main() {
    FILE *fin = fopen("lab1_2_input.txt", "r");
    FILE *fout = fopen("lab1_2_output.txt", "wt");
    int N, ar[101], s, e, sum=0;
    fscanf(fin, "%d", &N);
    for(int i=0;i<N;i++) fscanf(fin, "%d", ar+i);

    // Selection Sort
    for(int i=0;i<N-1;i++) {
        for(int j=i+1;j<N;j++) {
            if(ar[i]>ar[j]) {
                int t = ar[i];
                ar[i] = ar[j];
                ar[j] = t;
            }
        }
    }

    // Print
    for(int i=0;i<N;i++) fprintf(fout, "%d ", ar[i]);
    return 0;
}