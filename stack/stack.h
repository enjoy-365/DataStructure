#include <stdio.h>

#define EmptyTOS(-1)
#define MaxSize 100
typedef int ElementType;

typedef struct StackRecord* Stack;

struct StackRecord{
    int Capacity;
    int TopOfStack;
    ElementType* Array;
};

void push();
void pop();
void top();
Stack CreateStack();
void isFull();
void isEmpty();

Stack CreateStack(int MaxElements){

}
