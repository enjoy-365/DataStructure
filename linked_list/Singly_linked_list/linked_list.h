#include <stdio.h>
#include <stdlib.h>

typedef struct Node* PtrToNode;
typedef int ElementType;

typedef PtrToNode Position;
typedef PtrToNode List;

struct Node{
    ElementType Element;
    Position Next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
Position Find(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
void Delete(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);

//MakeEmpty(List L)
List MakeEmpty(List L){
    L = (List)malloc(sizeof(struct Node));
    //L->Element = header;
    L->Next = NULL;
    return L;
}

int IsEmpty(List L){
    return L->Next==NULL;
}

int IsLast(Position P, List L){
    return P->Next==NULL;
}

Position Find(ElementType X, List L){
    Position P;
    P = L->Next;
    while(P != NULL && P->Element != X){
        P=P->Next;
    }
    return P;// if not found, return NUll. else return the position.
}
Position FindPrevious(ElementType X, List L){
    Position P;
    P = L;
    while(P->Next != NULL && P->Next->Element != X){
        P = P->Next;
    }
    return P;
}
void Delete(ElementType X, List L){
    Position P, TmpCell;
    TmpCell = Find(X, L);
    if(TmpCell == NULL){
        printf("NO such element!\n");
        return;
    }
    P = FindPrevious(X, L);
    P->Next = TmpCell->Next;
    free(TmpCell);
}
void Insert(ElementType X, List L, Position P){
    Position TmpCell = (List)malloc(sizeof(struct Node));

    if(TmpCell==NULL){
        printf("Out of space!!!\n");
        return;
    }
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}
void DeleteList(List L){
    Position P, Tmp;
    P = L->Next;
    L->Next = NULL;
    while(P != NULL){
        Tmp = P->Next;
        free(P);
        P = Tmp;
    }
}
//DeleteList(List L)
//Find(List L, Key K)
//Insert(Key k, List L, Position P)
//Delete(Key K, List L)
//Concat(List L1, List L2)
