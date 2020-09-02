#include <stdio.h>
#include <stdlib.h>

#define EmptyTOS (-1)
#define MaxSize 100

typedef int ElementType;

typedef struct StackRecord* Stack;

struct StackRecord{
    int Capacity;
    int TopOfStack;
    ElementType* Array;
};

void push(ElementType X, Stack S, FILE* write);
void pop(Stack S, FILE* write);
void top(Stack S);
Stack CreateStack();
int isFull(Stack S);
int isEmpty(Stack S);

Stack CreateStack(int MaxElements){
    Stack S;

    S = malloc(sizeof(struct StackRecord));
    if(S == NULL){
        printf("Out of space!");
    }

    S->Array = malloc(sizeof(ElementType)*MaxElements);
    if(S->Array == NULL){
        printf("Out of space!");
    }
    S->Capacity = MaxElements;
    S->TopOfStack = EmptyTOS;

    return S;
}

void push(ElementType X, Stack S, FILE* write){
    if(isFull(S)) fprintf(write, "Full\n");
    else{
        S->Array[++S->TopOfStack] = X;
    }
}

int isFull(Stack S){
    if(S->Capacity == S->TopOfStack) return 1;
    else return 0;
}

int isEmpty(Stack S){
    if(S->TopOfStack < 0) return 1;
    else return 0;
}

void pop(Stack S, FILE* write){
    if(isEmpty(S)){
        fprintf(write,"Empty\n");
    }else{
        fprintf(write, "%d\n", S->Array[S->TopOfStack]);
        S->TopOfStack--;
    }
}

void top(Stack S){
    if(isEmpty(S)){
        printf("Empty\n");
    }else{
        printf("%d\n", S->Array[S->TopOfStack]);
    }
}
