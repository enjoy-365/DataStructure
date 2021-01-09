#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EmptyTOS (-1)
#define LIMIT 99

typedef struct StackRecord* Stack;

struct StackRecord {
	int capacity;
	int topOfStack;
	int* array;
};

Stack CreateStack(int maxElements) {
	Stack S;
	S = (Stack)malloc(sizeof(struct StackRecord));
	S->array = (int*)malloc(sizeof(int) * maxElements);
	S->capacity = maxElements;
	S->topOfStack = EmptyTOS;

	return S;
}

int IsFull(Stack S) {
	if (S->capacity == S->topOfStack) {
		return 1;
	}
	else return 0;
}

void Push(FILE* fp2, int x, Stack S) {
	if (IsFull(S)) {
		fprintf(fp2, "Full\n");
	}
	else {
		S->array[++S->topOfStack] = x;

	}
}

int IsEmpty(Stack S) {
	if (S->topOfStack < 0) return 1;
	else return 0;
}

int Top(Stack S) {
	if (!IsEmpty(S)) return S->array[S->topOfStack];
	else return 0;
}

void Pop(FILE* fp2, Stack S) {
	if (IsEmpty(S)) {
		fprintf(fp2, "Empty\n");
	}
	else {
		fprintf(fp2, "%d\n", Top(S));
		S->topOfStack--;
	}
}



int main() {
	int cnt;
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	char type[6];
	int element;

	Stack S = CreateStack(LIMIT);

	fscanf(fp1, "%d", &cnt);
	//printf("%d\n", cnt);

	while (cnt--) {
		fscanf(fp1, "%s", type);

		//printf("%s\n", type);

		if (strcmp(type, "push") == 0) {
			fscanf(fp1, "%d", &element);
			Push(fp2, element, S);
		}
		else {
			Pop(fp2, S);
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}