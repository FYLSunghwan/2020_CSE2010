#include <stdio.h>
#include <stdlib.h>
#include <string.h>

////////////////////////// ASSIGNMENT STATEMENT //////////////////////////
/* Push
 * Push a new element at the end of the element in stack.
 * If your stack is full, just print an error message.
 * 
 * Pop
 * Pop the element in the end of the stack. If stack does not have
 * any element, just print an error message.
 * 
 * Postfix
 * When you meet an operands (number), push it onto the stack.
 * When you meet an operator, pop two operands from the stack
 * and perform the operator, and push the result back to the stack.
 * 
 * DeleteStack
 * free all memory of the stack, and delete stack.
 */
typedef struct Stack {
    int* key;
    int top;
    int max_stack_size;
}Stack;

void Push(Stack* S, int X);
int Pop(Stack* S);
int Postfix(Stack* S, char input_str);
void DeleteStack(Stack* S);

Stack* CreateStack(int max); // Additional Function
//////////////////////////////////////////////////////////////////////////

#define ERR -1000000000

FILE* fi;
FILE* fo;

int main(int argc, char* argv[]) {
    if(argc<=2) {
        printf("Usage: ./lab3 INPUT_FILE_NAME OUTPUT_FILE_NAME\n");
        return 0;
    }
    fi = fopen(argv[1], "r");
    fo = fopen(argv[2], "wt");
    if(fi==NULL || fo==NULL) {
        printf("File IO Failed : Invalid filename\n");
        return 0;
    }

    Stack* stack;
    char input_str[101];
    int max, i=0, a, b, result;

    fgets(input_str, 101, fi);
    max = 1000;
    stack = CreateStack(max);

    fprintf(fo, "Top numbers :");

    for(i=0;i<strlen(input_str)&&input_str[i]!='#';i++)
        result = Postfix(stack, input_str[i]);

    fprintf(fo, "\nevaluation result : %d\n", result);
    fclose(fi);
    fclose(fo);
    DeleteStack(stack);
    return 0;
}

Stack* CreateStack(int max) {
    Stack* S = NULL;
    S = (Stack*)malloc(sizeof(struct Stack));
    S->key = (int*)malloc(sizeof(int)*max);
    S->max_stack_size = max;
    S->top = -1;
    return S;
}

void Push(Stack* S, int X) {
    if(S->top == S->max_stack_size-1) {
        fprintf(fo, "Error on Push(%d): Stack is Full\n", X);
        return;
    }
    S->top++;
    S->key[S->top] = X;
    fprintf(fo, "%d ", S->key[S->top]);
}

int Pop(Stack* S) {
    if(S->top<0) {
        fprintf(fo, "Error on Pop(): Stack is Empty\n");
        return ERR;
    }
    S->top--;
    return S->key[S->top+1];
}

int Postfix(Stack* S, char input_str) {
    int res = 0;

    if('1'<=input_str && input_str<='9')
        Push(S, input_str-'0');
    else {
        int num2 = Pop(S);
        int num1 = Pop(S);
        if(num1==ERR || num2==ERR) res = ERR;
        else {
            switch(input_str) {
                case '+':
                    Push(S, num1+num2);
                    res = num1+num2;
                    break;
                case '-':
                    Push(S, num1-num2);
                    res = num1-num2;
                    break;
                case '*':
                    Push(S, num1*num2);
                    res = num1*num2;
                    break;
                case '/':
                    Push(S, num1/num2);
                    res=num1/num2;
                    break;
                case '%':
                    Push(S, num1%num2);
                    res=num1/num2;
                    break;
                default:
                    res = ERR;
                    break;
            }
        }
    }
    return res;
}

void DeleteStack(Stack* S) {
    free(S->key);
    free(S);
}