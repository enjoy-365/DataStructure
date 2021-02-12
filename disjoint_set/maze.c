#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <vector>
#include <utility>
#include <string.h>

#define DEBUG

using namespace std;

void PrintDebug(const char* format, ...);
void PrintMazeDebug(int cnt);
void PrintMaze(int cnt, FILE* fp2);

char mazemap[101][101];//max size of maze is 50*50

int main(void) {
	srand((unsigned int)time(NULL)); //generate seed
	int x = rand(); //returns integer from 0 to 32767
	int y = rand() % 10; // y is form 0 to 9

	vector<int> edges[2500];

	memset(mazemap, 0, sizeof(char) * 101 * 101);

	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	int cnt;
	fscanf(fp1, "%d", &cnt);
	//make initial map;
	for (int i = 0; i < 2 * cnt + 1; i++) {
		for (int j = 0; j < 2 * cnt + 1; j++) {
			if (i % 2 == 0) {
				if (j % 2 == 0) mazemap[i][j] = '+';
				else mazemap[i][j] = '-';
			}
			else {
				if (j % 2 == 0) mazemap[i][j] = '|';
				else mazemap[i][j] = ' ';
			}
		}
	}
	mazemap[1][0] = ' ';
	mazemap[2 * cnt - 1][2 * cnt];

	//printfor debugging
	PrintMazeDebug(cnt);

	//insert possible edges
	int temp;
	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; j <= cnt; j++) {
			temp = (i - 1) * cnt + j;
			if (i % cnt != 0 && j % cnt != 0) {
				edges[temp].push_back(temp + 1);
				edges[temp].push_back(temp + cnt);
			}
			else if (i % cnt != 0) {
				edges[temp].push_back(temp + cnt);
			}
			else if (j % cnt != 0) {
				edges[temp].push_back(temp + 1);
			}
		}
	}
	//print for debugging, edges
	for (int i = 1; i <= cnt * cnt; i++) {
		for (int j = 0; j < edges[i].size(); j++) {
			PrintDebug("(%d, %d) ", i, edges[i][j]);
		}
		PrintDebug("\n");
	}



	fclose(fp1);
	fclose(fp2);

	return 0;
}
void PrintDebug(const char* format, ...) {
#ifdef DEBUG
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
#endif
}
void PrintMazeDebug(int cnt) {
	for (int i = 0; i < 2 * cnt + 1; i++) {
		for (int j = 0; j < 2 * cnt + 1; j++) {
			PrintDebug("%c", mazemap[i][j]);
		}
		PrintDebug("\n");
	}
}
void PrintMaze(int cnt, FILE* fp2) {
	for (int i = 0; i < 2 * cnt + 1; i++) {
		for (int j = 0; j < 2 * cnt + 1; j++) {
			fprintf(fp2, "%c", mazemap[i][j]);
		}
		fprintf(fp2, "\n");
	}
}