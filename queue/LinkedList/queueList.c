#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

typedef struct Node* PtrToNode;
typedef PtrToNode Queue;

struct Node {
	int element;
	int size;
	PtrToNode next;
};

Queue createQueue() {
	PtrToNode q = (PtrToNode)malloc(sizeof(struct Node));
	q->size = 0;
	q->next = NULL;
	return q;
}
int IsEmpty(Queue q) {
	if (q->next == NULL) return 1;
	else return 0;
}
void Enqueue(Queue q, int x) {

}
void Dequeue(Queue q, FILE* fp2) {
	if (IsEmpty(q)) {
		fprintf(fp2, "Empty\n");
	}
	else {
		PtrToNode temp = q->next;
		q->next = temp->next;
		fprintf(fp2, "%d\n", temp->element);
		free(temp);
		q->size--;
	}
}

int main() {
	FILE* fp1, * fp2;
	int cnt;
	int element;
	char cmd[5];

	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");


	fscanf(fp1, "%d", &cnt);
	while (cnt--) {
		fscanf(fp1, "%s", cmd);
		if (strcmp(cmd, "enQ") == 0) {
			fscanf(fp1, "%d", &element);
			printf("enQ %d\n", element);
		}
		else {
			printf("deQ\n");
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}