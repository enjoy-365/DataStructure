#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 100

typedef struct threaded_tree* threaded_ptr;
typedef struct threaded_tree {
	short int left_thread;
	threaded_ptr left_child;
	char data;
	threaded_ptr right_child;
	short int right_thread;
};

typedef struct QueueRecord* Queue;
typedef struct QueueRecord {
	int capacity;
	int front;
	int rear;
	int size;
	threaded_ptr* arr;
};

Queue CreateQueue();
int IsEmpty(Queue q);
int IsFull(Queue q);
int Enqueue(Queue q, threaded_ptr data);
int Dequeue(Queue q, threaded_ptr* temp);
threaded_ptr insucc(threaded_ptr tree);
void tinorder(threaded_ptr tree, FILE* fp2);
threaded_ptr CreateThreadedTree();
void InsertNode(threaded_ptr, char);
void ReleaseThreaded(threaded_ptr proot);

int main() {

	threaded_ptr proot = CreateThreadedTree();


	int cnt;
	char c;
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	fscanf(fp1, "%d ", &cnt);
	//printf("%d\n", cnt);
	while (cnt--) {
		fscanf(fp1, "%c ", &c);
		//printf("--------insert %c--------------------\n", c);
		InsertNode(proot, c);
	}

	tinorder(proot, fp2);
	//fprintf(fp2,"check\n");

	ReleaseThreaded(proot);

	//printf("hi");

	fclose(fp1);
	fclose(fp2);

	return 0;
}

threaded_ptr CreateThreadedTree() {
	threaded_ptr proot = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	proot->left_child = proot;
	proot->right_child = proot;

	proot->left_thread = 1;
	proot->right_thread = 1;

	//printf("Create dummy root\n");
	return proot;
}

void InsertNode(threaded_ptr proot, char c) {
	threaded_ptr addnode = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	addnode->data = c;
	addnode->left_thread = 1;
	addnode->right_thread = 1;//maybe it should be 0. but I changed it to 0 when the left_child is inserted.

	//dummy root(empty tree)
	if (proot->left_thread && proot->right_thread) {
		//printf("dummy root's left child %c\n", c);
		proot->left_child = addnode;
		proot->left_thread = 0;
		proot->right_thread = 0;
		addnode->left_child = proot;
		addnode->right_child = proot;
		return;
	}
	Queue q = CreateQueue();
	Enqueue(q, proot->left_child);
	threaded_ptr now;
	while (1) {
		Dequeue(q, &now);

		//left_child is empty;
		if (now->left_thread) {
			addnode->left_child = now->left_child;
			addnode->right_child = now;

			now->left_child = addnode;
			now->left_thread = 0;
			//printf("left child of %c is %c\n", now->data, addnode->data);
			break;

		}
		//right_child is empty
		else if (now->right_thread) {
			addnode->left_child = now;
			addnode->right_child = now->right_child;

			now->right_child = addnode;
			now->right_thread = 0;

			//printf("right child of %c is %c\n", now->data, addnode->data);
			break;
		}
		//left_child exists.
		if (!now->left_thread) {
			Enqueue(q, now->left_child);
		}
		if (!now->right_thread) {
			Enqueue(q, now->right_child);
		}
	}
	free(q->arr);
	free(q);
}

void ReleaseThreaded(threaded_ptr proot) {
	Queue q = CreateQueue();
	threaded_ptr now = proot;
	while (1) {
		now = insucc(now);
		if (now == proot) break;
		Enqueue(q, now);
	}
	while (Dequeue(q, &now)) {
		free(now);
	}
	free(q->arr);
	free(q);
	return;
}

threaded_ptr insucc(threaded_ptr tree) {
	threaded_ptr temp;
	temp = tree->right_child;
	//right_child exists & no leaf
	if (!tree->right_thread) {
		while (!temp->left_thread) {
			temp = temp->left_child;
		}
	}
	return temp;
}
void tinorder(threaded_ptr tree, FILE* fp2) {
	threaded_ptr temp = tree;
	while (1) {
		temp = insucc(temp);

		//dummy root
		if (temp == tree) break;
		fprintf(fp2, "%c ", temp->data);
	}
}

Queue CreateQueue() {
	Queue q = (Queue)malloc(sizeof(struct QueueRecord));
	q->arr = (threaded_ptr*)malloc(sizeof(threaded_ptr) * MAXSIZE);
	q->capacity = MAXSIZE;
	q->size = 0;
	q->front = 1;
	q->rear = 0;

	return q;
}
int IsEmpty(Queue q) {
	return q->size == 0;
}
int IsFull(Queue q) {
	return q->size == q->capacity;
}
int Enqueue(Queue q, threaded_ptr data) {
	if (IsFull(q)) return 0;
	else {
		q->size++;
		q->rear = (q->rear + 1) % q->capacity;
		q->arr[q->rear] = data;
		return 1;
	}
}
int Dequeue(Queue q, threaded_ptr* temp) {
	if (IsEmpty(q)) return 0;
	else {
		*temp = q->arr[q->front];
		q->front = (q->front + 1) % q->capacity;
		q->size--;
		return 1;
	}
}
