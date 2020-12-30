#include <stdio.h>
#include <string.h>

int main() {
	int cnt;
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	char type[6];
	int element;

	fscanf(fp1, "%d", &cnt);
	printf("%d\n", cnt);

	while (cnt--) {
		fscanf(fp1, "%s", type);
		printf("%s\n", type);

		if (strcmp(type, "push") == 0) {
			fscanf(fp1, "%d", &element);
			printf("%d\n", element);
		}
		else {
			printf("\n");
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}