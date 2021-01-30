#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int cnt;
	char c;
	FILE* fp1, fp2;
	fopen(fp1,"input.txt", "r");
	fopen(fp2, "output.txt", "w");

	fscanf(fp1, "%d", &cnt);
	while (cnt--) {
		fscanf(fp1, "%c", &c);
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}