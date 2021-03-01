#include <stdio.h>
#include <stdlib.h>

#define order 3

typedef struct B_node {
	int n_keys;
	B_node* child[order];
	int key[order - 1];
};

B_node* find(B_node x, int key);
void Insert(int key);
void Inorder(struct B_node* ptr);

int main(void) {
	FILE* fp1, * fp2;

	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	char cmd, n;
	while (fscanf(fp1, "%c", &cmd) != EOF) {
		if (cmd == 'i') {
			fscanf(fp1, "%d", &n);
		}
		else if (cmd == 'p') {

		}
		else {
			fprintf(fp2, "undefined command\n");
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}
B_node* find(B_node x, int key) {

}
void Insert(int key) {
	//node split


}
void Inorder(struct B_node* ptr) {

}