#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node* PtrToNode;
typedef PtrToNode Stack;
struct Node {
	int element;
	PtrToNode next;
};

Stack CreateStack();
void MakeEmpty(Stack S);
int IsEmpty(Stack S);
void Push(int x, Stack S);
int Top(Stack S);
void Pop(FILE* fp2, Stack S);

int main() {
	int cnt;
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	char type[6];
	int element;

	Stack S = CreateStack();

	fscanf(fp1, "%d", &cnt);
	//printf("%d\n", cnt);

	while (cnt--) {
		fscanf(fp1, "%s", type);

		//printf("%s\n", type);

		if (strcmp(type, "push") == 0) {
			fscanf(fp1, "%d", &element);
			Push(element, S);
		}
		else {
			Pop(fp2, S);
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}

Stack CreateStack() {
	Stack S;
	S = (Stack)malloc(sizeof(struct Node));
	S->next = NULL;

	return S;
}
void MakeEmpty(FILE* fp2, Stack S) {
	if (S != NULL) {
		while (!IsEmpty) {
			Pop(fp2, S);
		}
	}
}
int IsEmpty(Stack S) {
	if (S->next == NULL) return 1;
	else return 0;
}
void Push(int x, Stack S) {
	PtrToNode temp = (PtrToNode)malloc(sizeof(struct Node));
	temp->element = x;
	temp->next = S->next;
	S->next = temp;
}
int Top(Stack S) {
	if (!IsEmpty(S)) {
		return S->next->element;
	}
	return 0;
}
void Pop(FILE* fp2, Stack S) {
	if (IsEmpty(S)) {
		fprintf(fp2, "Empty\n");
	}
	else {
		fprintf(fp2, "%d\n", Top(S));
		PtrToNode target = S->next;
		S->next = target->next;
		free(target);
	}
}