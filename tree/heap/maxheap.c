#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define DEBUG

void PrintDebug(const char* format, ...) {
#ifdef DEBUG
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
#endif
}

typedef int ElementType;
typedef struct HeapStruct* PriorityQueue;
struct HeapStruct {
	int capacity;// max heap capacity
	int size;// current heap size
	ElementType* elements;
};

PriorityQueue InitHeap(int heapsize);
void Insert(ElementType x, PriorityQueue h, FILE* fp2);
int Find(ElementType x, PriorityQueue h);
//int FindRecursive(ElementType x, PriorityQueue h);
void Print(PriorityQueue h, FILE* fp2);
int IsFull(PriorityQueue h);

int main() {

	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	int heapsize;
	fscanf(fp1, "%d", &heapsize);
	PriorityQueue h = InitHeap(heapsize);

	char cmd;
	int num;
	while (fscanf(fp1, "%c", &cmd) != EOF) {
		if (cmd == 'i') {
			fscanf(fp1, "%d", &num);
			Insert(num, h, fp2);
			PrintDebug("after insert %d, h->size == %d\n", num, h->size);
		}
		else if (cmd == 'f') {
			fscanf(fp1, "%d", &num);
			if (Find(num, h)) {
				fprintf(fp2, "%d is in the heap\n", num);
			}
			else {
				fprintf(fp2, "%d is not in the heap\n", num);
			}
		}
		else if (cmd == 'p') {
			Print(h, fp2);
		}
	}


	fclose(fp1);
	fclose(fp2);

	return 0;
}

PriorityQueue InitHeap(int heapsize) {
	PriorityQueue h = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	h->size = 0;
	h->capacity = heapsize;
	h->elements = (ElementType*)malloc(sizeof(int) * h->capacity + 1);

	return h;
}
void Insert(ElementType x, PriorityQueue h, FILE* fp2) {
	if (IsFull(h)) {
		fprintf(fp2, "heap is full\n");
		return;
	}
	if (Find(x, h) == 1) {
		fprintf(fp2, "%d is already in the heap\n", x);
		return;
	}
	int i;
	for (i = ++h->size; i / 2 > 0 && h->elements[i / 2] < x; i /= 2) {
		h->elements[i] = h->elements[i / 2];
	}
	h->elements[i] = x;
	fprintf(fp2, "insert %d\n", x);
}
int Find(ElementType x, PriorityQueue h) {
	for (int i = 1; i <= h->size; i++) {
		if (h->elements[i] == x) {
			return 1;
		}
	}
	return 0;
}
/*int FindRecursive(ElementType x, PriorityQueue h) {

}*/
void Print(PriorityQueue h, FILE* fp2) {
	for (int i = 1; i <= h->size; i++) {
		fprintf(fp2, "%d ", h->elements[i]);
	}
	fprintf(fp2, "\n");
}
int IsFull(PriorityQueue h) {
	return h->size == h->capacity;
}
