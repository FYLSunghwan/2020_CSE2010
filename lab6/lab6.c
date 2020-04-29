#include <stdio.h>
#include <stdlib.h>

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* Insert
 * Insert a new node with the key value into the AVL tree. Print tree 
 * whenever inserting a new node. If the key already exists in the tree,
 * print error message.
 * 
 * printInorder
 * Print the tree by inorder traversal
 * 
 * SingleRotateWithLeft
 * 
 * SingleRotateWithRight
 * 
 * DoubleRotateWithLeft
 * 
 * DoubleRotateWithRight
 * 
 * deleteTree
 * Delete the tree.
 */
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
typedef int ElementType;
struct AVLNode {
    ElementType Element;
    AVLTree left;
    AVLTree right;
    int Height;
};

AVLTree Insert(ElementType X, AVLTree T);
Position SingleRotateWithLeft(Position node);
Position SingleRotateWithRight(Position node);
Position DoubleRotateWithLeft(Position node);
Position DoubleRotateWithRight(Position node);
void printInorder(AVLTree T);
void deleteTree(AVLTree T);

int getHeight(Position node); // Additional Function
int max(int a, int b); // Additional Function
//////////////////////////////////////////////////////////////////////////

FILE* fi;
FILE* fo;

int main(int argc, char* argv[]) {
    if(argc<=2) {
        printf("Usage: ./lab6 INPUT_FILE_NAME OUTPUT_FILE_NAME\n");
        return 0;
    }
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "wt");
    if(fi==NULL || fo==NULL) {
        printf("File IO Failed : Invalid filename\n");
        return 0;
    }

    AVLTree tree = NULL;
    int x;

    while(fscanf(fi, "%d", &x) != EOF) {
        tree = Insert(x, tree);
        printInorder(tree);
        fprintf(fo, "\n");
    }
    deleteTree(tree);
    fclose(fi);
    fclose(fo);
    return 0;
}

AVLTree Insert(ElementType X, AVLTree T) {
    if(T==NULL) {
        T = malloc(sizeof(struct AVLNode));
        T->Element = X;
        T->Height = 0;
        T->left = T->right = NULL;
    } else if (X < T->Element) {
        T->left = Insert(X, T->left);
        if(getHeight(T->left) - getHeight(T->right) >=2) {
            if(X<T->left->Element) T = SingleRotateWithLeft(T);
            else T = DoubleRotateWithLeft(T);
        }
    } else if(X > T->Element) {
        T->right = Insert(X, T->right);
        if(getHeight(T->right) - getHeight(T->left) >= 2) {
            if(X>T->right->Element) T = SingleRotateWithRight(T);
            else T = DoubleRotateWithRight(T);
        }
    } else {
        fprintf(fo, "[Error] %d already in the tree!\n", X);
    }
    T->Height = max(getHeight(T->left), getHeight(T->right))+1;
    return T;
}

Position SingleRotateWithLeft(Position node) {
    Position tmp;
    tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;

    node->Height = max(getHeight(node->left), getHeight(node->right))+1;
    tmp->Height = max(getHeight(tmp->left), getHeight(tmp->right))+1;

    return tmp;
}

Position SingleRotateWithRight(Position node) {
    Position tmp;
    tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;

    node->Height = max(getHeight(node->left), getHeight(node->right))+1;
    tmp->Height = max(getHeight(tmp->left), getHeight(tmp->right))+1;

    return tmp;    
}

Position DoubleRotateWithLeft(Position node) {
    node->left = SingleRotateWithRight(node->left);
    return SingleRotateWithLeft(node);
}

Position DoubleRotateWithRight(Position node) {
    node->right = SingleRotateWithLeft(node->right);
    return SingleRotateWithRight(node);
}

void printInorder(AVLTree T) {
    if(T) {
        printInorder(T->left);
        fprintf(fo, "%d(%d) ", T->Element, getHeight(T)-1);
        printInorder(T->right);
    }
}

void deleteTree(AVLTree T) {
        if(T!=NULL) {
        deleteTree(T->left);
        deleteTree(T->right);
        free(T);
    }
}

int getHeight(Position node) {
    if(node==NULL) return 0;
    else return node->Height;
}

int max(int a, int b) {
    return a>b?a:b;
}