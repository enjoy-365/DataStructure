#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

//#define DEBUG

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
AVLTree Insert(int x, AVLTree T, FILE* fp2, int* chk);
Position SingleRotateWithLeft(Position K);
Position SingleRotateWithRight(Position K);
Position DoubleRotateWithLeft(Position K);
Position DoubleRotateWithRight(Position K);
void PrintInorder(AVLTree root, FILE* fp2);

int main() {
	FILE* fp1, * fp2;
	int chk = 0;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	int data;
	AVLTree root = NULL;
	while (fscanf(fp1, "%d", &data) != EOF) {
		PrintDebug("%d ", data);
		root = Insert(data, root, fp2, &chk);
		if (chk) {
			PrintInorder(root, fp2);
			fprintf(fp2, "\n");
		}
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
AVLTree Insert(int x, AVLTree T, FILE* fp2, int* chk) {
	if (T == NULL) {
		*chk = 1;
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
	else if (x < T->element) {
		*chk = 1;
		T->left = Insert(x, T->left, fp2, chk);
		if (Height(T->left) - Height(T->right) == 2) {
			if (x < T->left->element) {
				T = SingleRotateWithLeft(T);
			}
			else {
				T = DoubleRotateWithLeft(T);
			}
		}
	}
	else if (x > T->element) {
		*chk = 1;
		T->right = Insert(x, T->right, fp2, chk);
		if (Height(T->right) - Height(T->left) == 2) {
			if (x > T->right->element) {
				T = SingleRotateWithRight(T);
			}
			else {
				T = DoubleRotateWithRight(T);
			}
		}
	}
	else {
		fprintf(fp2, "%d already in the tree!\n", x);
		*chk = 0;
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
	Position temp;
	temp = K->right;
	K->right = temp->left;
	temp->left = K;

	K->h = Max(Height(K->right), Height(K->left)) + 1;
	temp->h = Max(Height(temp->right), Height(temp->left)) + 1;
	return temp;
}
Position DoubleRotateWithLeft(Position K3) {
	//LR situation
	K3->left = SingleRotateWithRight(K3->left);
	return SingleRotateWithLeft(K3); // at here the function returns temp(the new top node);
}
Position DoubleRotateWithRight(Position K3) {
	//RL situation

	K3->right = SingleRotateWithLeft(K3->right);//K2& TEMP
	return SingleRotateWithRight(K3);
}
void PrintInorder(AVLTree root, FILE* fp2) {
	if (root) {
		PrintInorder(root->left, fp2);
		fprintf(fp2, "%d(%d)", root->element, root->h);
		PrintInorder(root->right, fp2);
	}
}
