#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node* PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef struct {
    int studentID;
    char* studentName;
}ElementType;

struct Node {
    ElementType element;
    PtrToNode next;
};

void Insert(ElementType X, List L, Position P);
int Delete(int num, List L);
Position Find(ElementType X, List L);
Position FindNum(int num, List L);
Position FindPrev(ElementType X, List L);
Position FindPrevNum(int num, List L);
Position FindInsertPos(ElementType X, List L);
void PrintList(List L, FILE* fp);
void PrintCurrent(List L, FILE* fp);
List MakeEmpty(void);
int IsEmpty(List L);
int isLast(Position P, List L);
void DeleteList(List L);

void Insert(ElementType X, List L, Position P){
    Position Tmp;
    Tmp = (List)malloc(sizeof(struct Node));
    //Tmp->element.studentID = (char*)malloc(sizeof(X.studentID)+1);
    Tmp->element.studentName = (char*)malloc(sizeof(X.studentName)+1);
    Tmp->element.studentID =  X.studentID;
    strcpy(Tmp->element.studentName, X.studentName);
    Tmp->next = P->next;
    P->next = Tmp;
}
int Delete(int num, List L){
    Position Target = FindNum(num, L);
    if(Target == NULL){
        return 0;
        //fprintf("Deletion Failed : Student ID %d is not in the list.\n", num);
    }else{ 
        //fprintf("Deletion Success : %d\n", num);
        //fflush(stdout);
        Position Prev = FindPrevNum(num, L);

        Prev->next = Target->next;
        free(Target->element.studentName);
        free(Target);
        
        //PrintCurrent(L);

        return 1;
        //fprintf("Deletion Success : %d\n", num);
    }
}
Position Find(ElementType X, List L){
    Position P;
    P = L->next;
    while(P!=NULL&&(P->element.studentID)!=(X.studentID)){
        P = P->next;
    }
    return P; // if not found, return NULL
}
Position FindNum(int num, List L){
    Position Tmp;
    Tmp = L->next;
    while(Tmp!=NULL && Tmp->element.studentID != num){
        Tmp = Tmp->next;
    }
    return Tmp;
}
Position FindPrev(ElementType X, List L){
    Position P;
    P = L;
    while(P->next!=NULL && (P->next->element.studentID != X.studentID)){
        P = P-> next;
    }
    return P;
}
Position FindPrevNum(int num, List L){
    Position P;
    P = L;
    while(P->next != NULL && P->next->element.studentID != num){
        P = P->next;
    }
    return P;
}
Position FindInsertPos(ElementType X, List L){
    Position current;
    current = L;
    while(current->next != NULL && current->next->element.studentID < X.studentID){
        current = current->next;
    }
    return current; // Insert( , ,FindInsertPos() )
}
void PrintList(List L, FILE* fp){
    Position traverse;
    traverse = L->next;
    fprintf(fp, "-----LIST-----\n");
    while(traverse != NULL){
        fprintf(fp, "%d %s\n", traverse->element.studentID, traverse->element.studentName);
        traverse = traverse->next;
    }
    fprintf(fp, "--------------\n");
}

void PrintCurrent(List L, FILE* fp){
    Position trav;
    trav = L->next;
    int cnt = 0;
    fprintf(fp, "Current List > ");
    while(trav!=NULL){
        if(cnt != 0 ){
            fprintf(fp, "-%d %s", trav->element.studentID, trav->element.studentName);
        }else{
            fprintf(fp, "%d %s", trav->element.studentID, trav->element.studentName);
        }
        trav = trav->next;
        cnt++;
    }
    fprintf(fp, "\n");
}

List MakeEmpty(void){
    List L = (List)malloc(sizeof(struct Node));
    L->next = NULL;
    return L;
}

int IsEmpty(List L){
    return L->next==NULL;
}
int isLast(Position P, List L){
    return P->next==NULL;
}
void DeleteList(List L){

}
