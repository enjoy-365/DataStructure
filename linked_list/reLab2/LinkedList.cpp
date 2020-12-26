#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

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
int Insert(ElementType X, List L);
int Delete(ElementType X, List L);
Position Find(ElementType X, List L);
void PrintList(List L, FILE* fp2);
List MakeEmpty();
int IsEmpty(List L);
int IsLast(Position P, List L);
void DeleteList(List L);
char* LeftTrim(char* s);

int main(void) {
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	char line[100];
	char type;
	char check;
	int id;
	char name[20];

	List h = MakeEmpty();

	while (fgets(line, 100, fp1) != NULL) {
		sscanf(line, "%c", &type);
		if (type == 'i') {
			sscanf(line, "%c%d%[^\n]s", &check, &id, name);
			char* trimmed = LeftTrim(name);
			ElementType temp;
			temp.studentID = id;
			temp.studentName = (char*)malloc(strlen(trimmed) + 1);
			strcpy(temp.studentName, trimmed);
			if (Insert(temp, h)) {
				fprintf(fp2, "Insertion Success : %d\n", temp.studentID);
				Position P = h->next;
				fprintf(fp2, "Current List >");
				fprintf(fp2, " %d %s", P->element.studentID, P->element.studentName);
				P = P->next;
				while (P != NULL) {
					fprintf(fp2, "-%d %s", P->element.studentID, P->element.studentName);
					P = P->next;
				}
				fprintf(fp2, "\n");
			}
			else {
				fprintf(fp2, "Insertion Failed. ID %d already exists.\n", temp.studentID);
			}

			/*printf("%c ", check);
			printf("%d ", id);
			printf("%s ", name);
			printf("\n");*/
		}
		else if (type == 'd') {
			sscanf(line, "%c%d", &type, &id);
			/*printf("target deletion: %d\n", id);
			printf("target type: %c\n", type);
			*/
			ElementType temp;
			temp.studentID = id;
			if (Delete(temp, h)) {
				fprintf(fp2, "Deletion Success : %d\n", id);
				Position P = h->next;
				fprintf(fp2, "Current List > ");
				while (P != NULL) {
					fprintf(fp2, "%d %s", P->element.studentID, P->element.studentName);
					P = P->next;
					if (P != NULL) {
						fprintf(fp2, "-");
					}
				}
				fprintf(fp2, "\n");
			}
			else {
				fprintf(fp2, "Deletion Failed : Student ID %d is not in the list.\n", id);
			}
			/*printf("%d ", id);
			printf("\n");*/
		}
		else if (type == 'f') {
			sscanf(line, "%c%d", &type, &id);
			ElementType temp;
			temp.studentID = id;
			Position res = Find(temp, h);
			if (res != NULL) {
				fprintf(fp2, "Find Success : %d %s\n", id, res->element.studentName);
			}
			else {
				fprintf(fp2, "Find %d Failed. There is no student ID\n", id);
			}

			/*printf("%d ", id);
			printf("\n");*/
		}
		else {
			// type이 p일 때이다.
			PrintList(h, fp2);
		}
	}


	fclose(fp1);
	fclose(fp2);

}

List MakeEmpty() {
	List L = (List)malloc(sizeof(struct Node));
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
int Insert(ElementType X, List L) {
	if (Find(X, L) != NULL) return 0;
	List temp = (List)malloc(sizeof(struct Node));
	temp->element.studentID = X.studentID;
	temp->element.studentName = (char*)malloc(strlen(X.studentName) + 1);
	strcpy(temp->element.studentName, X.studentName);

	Position P = L;
	while (P->next != NULL && P->next->element.studentID < X.studentID) {
		P = P->next;
	}
	//이제 P뒤에다가 새로 만든 temp 노드를 끼워넣는다.

	temp->next = P->next;
	P->next = temp;

	return 1;
}
int Delete(ElementType X, List L) {
	Position target = Find(X, L);
	if (target != NULL) {
		Position prev = L;
		while (prev->next != NULL && prev->next->element.studentID != X.studentID) {
			prev = prev->next;
		}

		prev->next = target->next;
		free(target);
		target = NULL;

		return 1;
	}
	else {
		return 0;
	}
}
void DeleteList(List L) {
	Position P, tmp;
	P = L->next;
	L->next = NULL;

	while (P != NULL) {
		tmp = P->next;
		free(P);
		P = tmp;
	}
}

char* LeftTrim(char* s) {
	char* left = s;
	while (*left != '\0') {
		if (isspace(*left)) {
			left++;
		}
		else {
			s = left;
			break;
		}
	}
	return s;
}