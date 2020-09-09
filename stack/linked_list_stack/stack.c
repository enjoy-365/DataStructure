#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef PtrToNode Stack;

typedef struct Node{
    int nData;
    PtrToNode next;
}Node;

void InitializeStack(Stack S);
Stack CreateStack();
void Push(Stack S, int nData);
void Top(Stack S);
void Pop(Stack S);
int IsEmpty(Stack S);

int main(void){

    return 0;
}
