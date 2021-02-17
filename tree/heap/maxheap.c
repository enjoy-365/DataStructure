#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
struct HeapStruct {
	int capacity;
	int size;
	ElementType* elements;
};

void Insert(ElementType x, PriorityQueue h);
void Find(ElementType x, PriorityQueue h);
void Print(PriorityQueue h);

int main() {

	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");


	fclose(fp1);
	fclose(fp2);
	
	return 0;
}


void Insert(ElementType x, PriorityQueue h) {

}
void Find(ElementType x, PriorityQueue h) {

}
void Print(PriorityQueue h) {

}
