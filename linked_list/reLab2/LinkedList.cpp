#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void Delete(ElementType X, List L);
Position Find(ElementType X, List L);
void PrintList(List L, FILE* fp2);
List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void DeleteList(List L);

int main(void) {
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	char line[100];
	char type;
	char check;
	int id;
	char name[20];

	while (fgets(line, 100, fp1) != NULL) {
		sscanf(line, "%c", &type);
		if (type == 'i') {
			sscanf(line, "%c%d%[^\n]s", &check, &id, name);
			/*printf("%c ", check);
			printf("%d ", id);
			printf("%s ", name);
			printf("\n");*/
		}
		else if (type == 'd') {
			sscanf(line, "%d", &id);
			/*printf("%d ", id);
			printf("\n");*/
		}
		else if (type == 'f') {

			sscanf(line, "%d", &id);
			/*printf("%d ", id);
			printf("\n");*/
		}
		else
			// type이 p일 때이다.
			printf("%c ", type);
		printf("\n");
	}


	fclose(fp1);
	fclose(fp2);

}

List MakeEmpty(List L) {
	L = (List)malloc(sizeof(struct Node));
	L->next = NULL;

	return L;
}
int IsEmpty(List L) {
	return L->next == NULL;
}
int IsLast(Position P, List L) {
	return P->next == NULL;
}
Position Find(ElementType X, List L) {
	Position P = L->next;
	while (P != NULL && P->element.studentID != X.studentID) {
		P = P->next;
	}
	return P;
}
void PrintList(List L, FILE* fp2) {
	Position P = L->next;
	fprintf(fp2, "-----LIST-----\n");
	while (P != NULL) {
		fprintf(fp2, "%d %s\n", P->element.studentID, P->element.studentName);
		P = P->next;
	}
	fprintf(fp2, "--------------");
}