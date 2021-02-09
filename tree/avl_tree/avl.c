#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

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
AVLTree Insert(int x, AVLTree T);
Position SingleRotateWithLeft(Position K);
Position SingleRotateWithRight(Position K);
Position DoubleRotateWithLeft(Position K);
Position DoubleRotateWithRight(Position K);

int main() {
	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = foepn("output.txt", "w");




	fclose(fp1);
	fclose(fp2);

	return 0;
}

int Height(Position P) {

}
AVLTree Insert(int x, AVLTree T) {

}
Position SingleRotateWithLeft(Position K) {

}
Position SingleRotateWithRight(Position K) {

}
Position DoubleRotateWithLeft(Position K) {

}
Position DoubleRotateWithRight(Position K) {

}