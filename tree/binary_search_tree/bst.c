#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG

void PrintDebug(const char* format, ...) {
#ifdef DEBUG
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
#endif
}

int main() {
	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	char cmd[5];
	int v;

	while (fscanf(fp1, "%s", cmd) != EOF) {
		if (strcmp(cmd, "i") == 0) {
			fscanf(fp1, "%d", &v);
			PrintDebug("input %d\n", v);
		}
		else if (strcmp(cmd, "d") == 0) {
			fscanf(fp1, "%d", &v);
			PrintDebug("delete %d\n", v);
		}
		else if (strcmp(cmd, "f") == 0) {
			fscanf(fp1, "%d", &v);
			PrintDebug("find %d\n", v);
		}
		else if (strcmp(cmd, "pi") == 0) {
			PrintDebug("pi\n");
		}
		else if (strcmp(cmd, "pr") == 0) {
			PrintDebug("pr\n");
		}
		else if (strcmp(cmd, "po") == 0) {
			PrintDebug("po\n");
		}
		else {
			PrintDebug("ERROR: type cmd\n");
		}

	}


	fclose(fp1);
	fclose(fp2);

	return 0;
}