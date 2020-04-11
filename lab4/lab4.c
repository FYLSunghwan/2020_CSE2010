#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* Insert
 * Insert a new node in tree. If the tree is full, print an error message.
 * 
 * printInorder
 * Print the tree by inorder traversal.
 * 
 * printPreorder
 * Print the tree by preorder traversal
 * 
 * printPostorder
 * Print the tree by postorder traversal.
 * 
 * FreeTree
 * Free the tree
 */
struct CompleteTree{
    int Size;
    int nodeNum;
    int* Element;
};
typedef struct CompleteTree* Tree;

void Insert(Tree tree, int value);
void printPreorder(Tree tree, int index);
void printInorder(Tree tree, int index);
void printPostorder(Tree tree, int index);
void FreeTree(Tree tree);
//////////////////////////////////////////////////////////////////////////

FILE* fi;
FILE* fo;

int main(int argc, char* argv[]) {
    if(argc<=2) {
        printf("Usage: ./lab4 INPUT_FILE_NAME OUTPUT_FILE_NAME\n");
        return 0;
    }
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "wt");
    if(fi==NULL || fo==NULL) {
        printf("File IO Failed : Invalid filename\n");
        return 0;
    }

    int Size;
    fscanf(fi, "%d", &Size);
    Tree tree = malloc(sizeof(Tree));
    tree->Element = (int*)malloc(sizeof(int)*(Size+1));
    tree->Size = Size;

    while(1) {
        int element, isEOF;
        isEOF = fscanf(fi, "%d", &element);
        if(isEOF == EOF) break;
        if(tree->nodeNum == tree->Size) {
            fprintf(fo, "Error! Tree is FULL.\n");
            break;
        }
        Insert(tree, element);
    }
    fprintf(fo, "Preorder: ");
    printPreorder(tree, 1);
    fprintf(fo, "\nInorder: ");
    printInorder(tree, 1);
    fprintf(fo, "\nPostorder: ");
    printPostorder(tree, 1);
    fprintf(fo, "\n");
    FreeTree(tree);
    return 0;
}

void Insert(Tree tree, int value) {
    if(tree->nodeNum == tree->Size) {
        fprintf(fo, "Error! Tree is FULL.\n");
        return;
    }
    tree->nodeNum++;
    tree->Element[tree->nodeNum] = value;
}

void printPreorder(Tree tree, int index) {
    if(index>tree->nodeNum) return;
    fprintf(fo, "%d ", tree->Element[index]);
    printPreorder(tree, index*2);
    printPreorder(tree, index*2+1);
}

void printInorder(Tree tree, int index) {
    if(index>tree->nodeNum) return;
    printInorder(tree, index*2);
    fprintf(fo, "%d ", tree->Element[index]);
    printInorder(tree, index*2+1);
}

void printPostorder(Tree tree, int index) {
    if(index>tree->nodeNum) return;
    printPostorder(tree, index*2);
    printPostorder(tree, index*2+1);
    fprintf(fo, "%d ", tree->Element[index]);
}

void FreeTree(Tree tree) {
    free(tree->Element);
    free(tree);
}
