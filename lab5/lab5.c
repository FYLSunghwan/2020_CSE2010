#include <stdio.h>
#include <stdlib.h>

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* insertNode
 * i x : Insert a new key "x" into the binary search tree
 *       without duplication. If x already exists in the tree,
 *       print an error message.
 * 
 * deleteNode
 * d x : Delete a key "x" in the binary search tree. If x does not exist
 *       in the tree, print an error message.
 * 
 * findNode
 * f x : Find the given key "x" to check whether the key exists
 *       in the tree. Print "x is in the tree" if the key exists.
 *       Otherwise, print an error message.
 * 
 * printInorder
 * pi  : Print the tree by inorder traversal.
 * 
 * deleteTree
 * Delete the tree.
 */
typedef struct BinarySearchTree* Tree;
struct BinarySearchTree {
    int value;
    Tree left;
    Tree right;
};

Tree insertNode(Tree root, int key);
void findNode(Tree root, int key);
void printInorder(Tree root);
Tree deleteNode(Tree root, int key);
void deleteTree(Tree root);

Tree FindMin(Tree root); // Additional Function
//////////////////////////////////////////////////////////////////////////

FILE* fi;
FILE* fo;
int originalKey;

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

    Tree tree = NULL;
    char cmd;
    int x;

    while(fscanf(fi, "%c", &cmd) != EOF) {
        switch(cmd) {
            case 'i':
                fscanf(fi, "%d", &x);
                tree = insertNode(tree, x);
                break;
            case 'd':
                fscanf(fi, "%d", &x);
                originalKey = x;
                tree = deleteNode(tree, x);
                break;
            case 'f':
                fscanf(fi, "%d", &x);
                findNode(tree, x);
                break;
            case 'p':
                fscanf(fi, "%c", &cmd);
                if(cmd=='i') printInorder(tree), fprintf(fo, "\n");
                break;
        }
    }
    deleteTree(tree);
    return 0;
}

Tree insertNode(Tree root, int key) {
    if(root==NULL) {
        root = (Tree)malloc(sizeof(struct BinarySearchTree));
        root->value = key;
        root->left = NULL;
        root->right = NULL;
        fprintf(fo, "insert %d\n", key);
    }
    else if(key < root->value) root->left = insertNode(root->left, key);
    else if(key > root->value) root->right = insertNode(root->right, key);
    else fprintf(fo, "%d is already in the tree.\n", key);
    return root;
}

void findNode(Tree root, int key) {
    if(root == NULL) fprintf(fo, "%d is not in the tree\n", key);
    else if(key < root->value) findNode(root->left, key);
    else if(key > root->value) findNode(root->right, key);
    else fprintf(fo, "%d is in the tree.\n", key);
}

void printInorder(Tree root) {
    if(root) {
        printInorder(root->left);
        fprintf(fo, "%d ", root->value);
        printInorder(root->right);
    }
}

Tree deleteNode(Tree root, int key) {
    Tree tmp;
    if(root == NULL)
        fprintf(fo, "Deletion Error : %d is not in the tree.\n", key);
    else if(key < root->value)
        root->left = deleteNode(root->left, key);
    else if(key > root->value)
        root->right = deleteNode(root->right, key);
    else if(root->left && root->right) {
        tmp = FindMin(root->right);
        root->value = tmp->value;
        root->right = deleteNode(root->right, root->value);
    }
    else {
        tmp = root;
        if(root->left ==NULL) root = root->right;
        else root = root->left;
        free(tmp);
        fprintf(fo, "delete %d\n", originalKey);
    }
    return root;
}

void deleteTree(Tree root) {
    if(root!=NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
    }
}

Tree FindMin(Tree root) {
    if(root==NULL) return NULL;
    if(root->left == NULL) return root;
    return FindMin(root->left);
}
