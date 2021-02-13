#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <vector>
#include <utility>
#include <string.h>

#define DEBUG

using namespace std;
typedef struct Map* PtrToMap;
typedef struct Map {
	int n;
	int height;
	int width;
	char** map;
};
typedef struct Edge {
	int e1;
	int e2;
};
typedef struct DisjointSet {
	int size;
	int cnt;
	int* S;
};

void PrintDebug(const char* format, ...);
void PrintMazeDebug(PtrToMap pamp);
void PrintMaze(PtrToMap pmap, FILE* fp2);
void CreateMaze(PtrToMap pmap);

//char mazemap[101][101];//max size of maze is 50*50

PtrToMap initMap(int n);
void deleteMap(PtrToMap pmap);

void CreateDisjointSet(DisjointSet* pset, int size);
void DeleteDisjointSet(DisjointSet* pset);
void Union(DisjointSet* pset, int r1, int r2);
int Find(DisjointSet* pset, int r);

int main(void) {

	srand((unsigned int)time(NULL)); //generate seed
	//int x = rand(); //returns integer from 0 to 32767
	//int y = rand() % 10; // y is form 0 to 9

	//vector<int> edges[2500];

	//memset(mazemap, 0, sizeof(char)*101*101);

	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	int n;
	fscanf(fp1, "%d", &n);

	//make initial map;
	PtrToMap pmap = initMap(n);

	//printfor debugging
	//PrintMazeDebug(pmap);

	//print for debugging(edges)
	CreateMaze(pmap);

	PrintMazeDebug(pmap);

	//insert possible edges
	/*int temp;
	for (int i = 1; i <= cnt; i++) {
		for (int j = 1; j <= cnt; j++) {
			temp = (i - 1) * cnt + j;
			if (i % cnt != 0 && j % cnt != 0) {
				edges[temp].push_back(temp + 1);
				edges[temp].push_back(temp + cnt);
			}else if (i % cnt != 0) {
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
	}*/

	free(pmap);
	fclose(fp1);
	fclose(fp2);

	return 0;
}

PtrToMap initMap(int n) {
	PtrToMap temp = (PtrToMap)malloc(sizeof(struct Map));
	if (temp == NULL) {
		printf("Out of Space!\n");
	}
	temp->n = n;
	temp->height = temp->width = 2 * n + 1;

	temp->map = (char**)malloc(sizeof(char*) * temp->height);
	for (int i = 0; i < temp->height; i++) {
		temp->map[i] = (char*)malloc(sizeof(char) * temp->width);
		for (int j = 0; j < temp->height; j++) {
			temp->map[i][j] = 0;
		}
	}

	for (int i = 0; i < temp->height; i++) {
		for (int j = 0; j < temp->width; j++) {
			if (i % 2 == 0) {
				if (j % 2 == 0) temp->map[i][j] = '+';
				else temp->map[i][j] = '-';
			}
			else {
				if (j % 2 == 0) temp->map[i][j] = '|';
				else temp->map[i][j] = ' ';
			}
		}
	}
	temp->map[1][0] = ' ';//start
	temp->map[2 * n - 1][2 * n] = ' ';//end

	return temp;
}
void deleteMap(PtrToMap pmap) {
	for (int i = 0; i < pmap->height; i++) {
		free(pmap->map[i]);
	}
	free(pmap->map);
}

void CreateMaze(PtrToMap pmap) {
	//Make edges
	int totalEdge = 2 * pmap->n * (pmap->n - 1);
	Edge* edges = (Edge*)malloc(sizeof(struct Edge) * totalEdge);
	int temp;
	int cntEdge = 0;
	for (int i = 1; i <= pmap->n; i++) {
		for (int j = 1; j <= pmap->n; j++) {
			temp = (i - 1) * (pmap->n) + j;
			if (i % (pmap->n) != 0 && j % (pmap->n) != 0) {
				edges[cntEdge].e1 = temp;
				edges[cntEdge].e2 = temp + 1;
				cntEdge++;
				edges[cntEdge].e1 = temp;
				edges[cntEdge].e2 = temp + pmap->n;
			}
			else if (i % (pmap->n) != 0) {
				edges[cntEdge].e1 = temp;
				edges[cntEdge].e2 = temp + pmap->n;
			}
			else if (j % (pmap->n) != 0) {
				edges[cntEdge].e1 = temp;
				edges[cntEdge].e2 = temp + 1;
			}
			cntEdge++;
		}
	}
	cntEdge--;

	//for debugging edges
	/*PrintDebug("num of edges is %d\n", cntEdge);
	for (int i = 0; i < cntEdge; i++) {
		PrintDebug("(%d, %d) ", edges[i].e1, edges[i].e2);
	}*/


	//Disjoint set operation
	int exit = (pmap->n) * (pmap->n);
	DisjointSet set;
	CreateDisjointSet(&set, exit);

	int target;
	int u, v;
	//Find(&set, 1) != Find(&set, exit)
	while (set.cnt != 1) {
		//randomly select edges
		target = rand() % cntEdge;
		u = edges[target].e1;
		v = edges[target].e2;
		if (Find(&set, u) != Find(&set, v)) {
			Union(&set, u, v);
			int w = (u - 1) % pmap->n + 1;
			int h = (u - 1) / pmap->n + 1;
			if (v - u == 1) {
				//right edge
				pmap->map[h * 2 - 1][w * 2] = ' ';
			}
			else {
				//down edge
				pmap->map[2 * h][2 * w - 1] = ' ';
			}
		}
		edges[target] = edges[--cntEdge];
	}


}

void CreateDisjointSet(DisjointSet* pset, int size) {
	pset->size = size;
	pset->cnt = size;
	pset->S = (int*)malloc(sizeof(int) * (size + 1));//not from 0, but from 1

	//each element is root, whose height is 0
	for (int i = 1; i <= size; i++) {
		pset->S[i] = 0;
	}
}
void DeleteDisjointSet(DisjointSet* pset) {
	pset->size = 0;
	free(pset->S);
}
void Union(DisjointSet* pset, int r1, int r2) {
	if (pset->S[r2] < pset->S[r1]) {
		//then r2 is bigger than r1
		pset->S[r1] = r2;
	}
	else {
		if (pset->S[r1] == pset->S[r2]) {
			pset->S[r1]--;
		}
		pset->S[r2] = r1;
	}
	pset->cnt--;
}
int Find(DisjointSet* pset, int r) {
	if (pset->S[r] <= 0) return r;
	else {
		return (pset->S[r] = Find(pset, pset->S[r]));
	}
}
void PrintDebug(const char* format, ...) {
#ifdef DEBUG
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
#endif
}
void PrintMazeDebug(PtrToMap pmap) {
	for (int i = 0; i < pmap->height; i++) {
		for (int j = 0; j < pmap->width; j++) {
			PrintDebug("%c", pmap->map[i][j]);
		}
		PrintDebug("\n");
	}
}
void PrintMaze(PtrToMap pmap, FILE* fp2) {
	for (int i = 0; i < pmap->height; i++) {
		for (int j = 0; j < pmap->height; j++) {
			fprintf(fp2, "%c", pmap->map[i][j]);
		}
		fprintf(fp2, "\n");
	}
}