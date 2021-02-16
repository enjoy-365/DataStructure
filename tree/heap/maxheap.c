#include <stdio.h>
#include <stdlib.h>

struct HeapStruct {
	int capacity;
	int size;
	elementType* elements;
};

int main() {

	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");


	fclose(fp1);
	fclose(fp2);
	
	return 0;
}
