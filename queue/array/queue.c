#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MAXSIZE 100

typedef struct QueueRecord* Queue;
typedef int ElementType;

struct QueueRecord {
	int capacity;
	int size;
	int front;
	int rear;
	ElementType* array;
};

Queue createQueue() {
	Queue q = (Queue)malloc(sizeof(struct QueueRecord));
	q->array = (ElementType*)malloc(sizeof(ElementType) * MAXSIZE);
	q->capacity = MAXSIZE;
	q->size = 0;
	q->front = 1;
	q->rear = 0;

	return q;
}
void MakeEmpty(Queue q) {
	q->size = 0;
	q->front = 1;
	q->rear = 0;
}
int IsFull(Queue q) {
	if (q->size == (q->capacity - 1)) return 1;
	else return 0;
}
int IsEmpty(Queue q) {
	if (q->size == 0) return 1;
	else return 0;
}
void Enqueue(Queue q, ElementType x, FILE* fp2) {
	if (IsFull(q)) {
		fprintf(fp2, "Full\n");
		return;
	}
	else {
		q->size++;
		q->rear = (q->rear + 1) % q->capacity;
		q->array[q->rear] = x;
	}
}
void Dequeue(Queue q, FILE* fp2) {
	if (IsEmpty(q)) {
		fprintf(fp2, "Empty\n");
	}
	else {
		fprintf(fp2, "%d\n", q->array[front]);
		q->size--;
		q->front = (q->front + 1) % q->capacity;
	}
}

int main() {
	FILE* fp1, * fp2;
	int cnt;
	ElementType element;
	char cmd[5];

	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	Queue q = createQueue();

	fscanf(fp1, "%d", &cnt);
	while (cnt--) {
		fscanf(fp1, "%s", cmd);
		if (strcmp(cmd, "enQ") == 0) {
			fscanf(fp1, "%d", &element);
			//printf("enQ %d\n", element);
			Enqueue(q, element, fp2);
		}
		else {
			//printf("deQ\n");
			Dequeue(q, fp2);
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}