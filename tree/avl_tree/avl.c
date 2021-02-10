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

struct AVLNode;
typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;

struct AVLNode {
	int element;
	AVLTree left;
	AVLTree right;
	int h;
};

int Height(Position P);
int Max(int a, int b);
AVLTree Insert(int x, AVLTree T);
Position SingleRotateWithLeft(Position K);
Position SingleRotateWithRight(Position K);
Position DoubleRotateWithLeft(Position K);
Position DoubleRotateWithRight(Position K);

int main() {
	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	int data;
	while (fscanf(fp1, "%d", &data) != EOF) {
		PrintDebug("%d ", data);
	}


	fclose(fp1);
	fclose(fp2);

	return 0;
}

int Height(Position P) {
	if (P == NULL) {
		return -1;
	}
	else {
		return P->h;
	}
}
int Max(int a, int b) {
	return a > b ? a : b;
}
AVLTree Insert(int x, AVLTree T) {
	if (T == NULL) {
		T = (AVLTree)malloc(sizeof(struct AVLNode));
		if (T == NULL) {
			PrintDebug("Out of Space!\n");
		}
		else {
			T->element = x;
			T->h = 0;
			T->left = T->right = NULL;
		}
	}
	else if () {

	}
	else if () {

	}

	T->h = Max(Height(T->left), Height(T->right)) + 1;

	return T;
}
Position SingleRotateWithLeft(Position K2) {
	//LL situation
	Position temp;
	temp = K2->left;
	K2->left = temp->right;
	temp->right = K2;

	K2->h = Max(Height(K2->left), Height(K2->right)) + 1;
	temp->h = Max(Height(temp->left), Height(temp->right)) + 1;

	return temp;
}
Position SingleRotateWithRight(Position K) {
	//RR situation
}
Position DoubleRotateWithLeft(Position K3) {
	//LR situation
	K3->left = SingleRotateWithRight(K3->left);
	return SingleRotateWithLeft(K3); // at here the function returns temp(the new top node);
}
Position DoubleRotateWithRight(Position K) {
	//RL situation
}
