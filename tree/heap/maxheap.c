#include <stdio.h>
#include <stdlib.h>

#define HEAPSIZE 100

typedef int ElementType;
typedef struct HeapStruct* PriorityQueue;
struct HeapStruct {
	int capacity;// max heap capacity
	int size;// current heap size
	ElementType* elements;
};

PriorityQueue InitHeap();
void Insert(ElementType x, PriorityQueue h, FILE* fp2);
void Find(ElementType x, PriorityQueue h);
void Print(PriorityQueue h);
int IsFull(PriorityQueue h);

int main() {

	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");


	fclose(fp1);
	fclose(fp2);

	return 0;
}

PriorityQueue InitHeap() {
	PriorityQueue h = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	h->size = 0;
	h->capacity = HEAPSIZE;
	h->elements = (ElementType*)malloc(sizeof(int) * h->capacity);

	return h;
}
void Insert(ElementType x, PriorityQueue h, FILE* fp2) {
	if (IsFull(h)) {
		fprintf(fp2, "heap is full\n");
		return;
	}
	int i = 0;
	for (i = ++h->size; h->elements[i / 2] < x; i /= 2) {
		h->elements[i] = h->elements[i / 2];
	}
	h->elements[i] = x;
}
void Find(ElementType x, PriorityQueue h) {

}
void Print(PriorityQueue h) {

}
int IsFull(PriorityQueue h) {
	return h->size == h->capacity;
}
