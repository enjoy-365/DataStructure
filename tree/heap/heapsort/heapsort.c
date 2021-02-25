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
void HeapSort(PriorityQueue h, int cnt, FILE* fp2);
void BuildHeap(PriorityQueue h);
void MaxHeapify(PriorityQueue h, int i);
int DeleteMax(PriorityQueue h, FILE* fp2);
int Find(ElementType x, PriorityQueue h);
//int FindRecursive(ElementType x, PriorityQueue h);
void Print(PriorityQueue h, int n, FILE* fp2);
int IsFull(PriorityQueue h);
int IsEmpty(PriorityQueue h);

int main() {

	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	int cnt, n;
	fscanf(fp1, "%d", &cnt);

	PriorityQueue h = InitHeap(cnt);
	PrintDebug("InitHeap is done\n");

	for (int i = 1; i <= cnt; i++) {
		fscanf(fp1, "%d", &n);

		PrintDebug("insert %d\n", n);

		h->elements[i] = n;
		h->size++;
	}

	HeapSort(h, cnt, fp2);

	fprintf(fp2, "after heapsort: ");
	Print(h, cnt, fp2);

	fclose(fp1);
	fclose(fp2);

	return 0;
}
void BuildHeap(PriorityQueue h) {
	//O(N)
	int i;
	for (i = h->size / 2; i > 0; i--) {
		MaxHeapify(h, i);
	}
}
void MaxHeapify(PriorityQueue h, int i) {
	int idx = i;
	int left = 2 * i;
	int right = left + 1;
	if (left <= h->size && h->elements[left] > h->elements[idx]) {
		idx = left;
	}
	if (right <= h->size && h->elements[right] > h->elements[idx]) {
		idx = right;
	}
	if (idx != i) {
		int maxValue = h->elements[idx];
		h->elements[idx] = h->elements[i];
		h->elements[i] = maxValue;

		MaxHeapify(h, idx);
	}
}
void HeapSort(PriorityQueue h, int cnt, FILE* fp2) {
	BuildHeap(h);

	fprintf(fp2, "after buildHeap: ");
	Print(h, cnt, fp2);
	fprintf(fp2, "\n");
	int i;
	for (i = h->size; i > 1; i--) {
		int maxValue = h->elements[1];
		h->elements[1] = h->elements[h->size];
		h->elements[h->size] = maxValue;
		h->size--;
		MaxHeapify(h, 1);
	}
}
PriorityQueue InitHeap(int heapsize) {
	PriorityQueue h = (PriorityQueue)malloc(sizeof(struct HeapStruct));
	h->capacity = heapsize + 1;
	h->size = 0;
	h->elements = (ElementType*)malloc(sizeof(int) * h->capacity);

	return h;
}
void Insert(ElementType x, PriorityQueue h, FILE* fp2) {
	if (IsFull(h)) {
		fprintf(fp2, "heap is full\n");
		return;
	}
	//after testing find -> no identities then, insert.
	int i;
	for (i = ++h->size; (h->size > 1) && h->elements[i / 2] < x; i / 2) {
		h->elements[i] = h->elements[i / 2];
	}
	h->elements[i] = x;
	fprintf(fp2, "insert %d\n", x);
	return;
}
ElementType DeleteMax(PriorityQueue h, FILE* fp2) {
	if (IsEmpty(h)) {
		fprintf(fp2, "heap is empty\n");
		return -1;
	}

	//find the right position for the last element.
	ElementType maxElement = h->elements[1];
	ElementType lastElement = h->elements[h->size--];

	//percolating down;
	int i, child;
	for (i = 1; (2 * i) >= h->size; i = child) {
		child = 2 * i;

		//select the min child between right and left
		if (child != h->size && h->elements[child] < h->elements[child + 1]) {
			child++;
		}
		//if the last element is bigger than the child
		if (lastElement < h->elements[child]) {
			h->elements[i] = h->elements[child];
		}
		else {
			break;
		}
	}
	h->elements[i] = lastElement;
	fprintf(fp2, "deleteMax %d", maxElement);
	return maxElement;
}
int Find(ElementType x, PriorityQueue h) {
	for (int i = 1; i <= h->size; i++) {
		if (h->elements[i] == x) {
			return 1;
		}
	}
	return 0;
}
void Print(PriorityQueue h, int n, FILE* fp2) {
	for (int i = 1; i <= n; i++) {
		fprintf(fp2, "%d ", h->elements[i]);
	}
}
int IsFull(PriorityQueue h) {
	return h->capacity == h->size;

}
int IsEmpty(PriorityQueue h) {
	return h->size == 0;
}