#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>

#define DEBUG

void PrintDebug(const char* format, ...) {
#ifdef DEBUG
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
#endif
}

int main(void) {
	srand((unsigned int)time(NULL)); //generate seed
	int x = rand(); //returns integer from 0 to 32767
	int y = rand() % 10; // y is form 0 to 9

	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	int cnt;
	fscanf(fp1, "%d", &cnt);



	fclose(fp1);
	fclose(fp2);

	return 0;
}