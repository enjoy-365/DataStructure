#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG

void PrintDebug(const char* format, ...) {
#ifdef DEBUG
	va_list ap;
	va_start(ap, format);
	vprintf(format, ap);
	va_end(ap);
#endif
}

typedef struct TreeNode* TreePtr;
typedef struct TreeNode {
	int value;
	TreePtr left;
	TreePtr right;
};
TreePtr InsertNode(int value, TreePtr root, FILE* fp2);
TreePtr DeleteNode(int value, TreePtr root, FILE* fp2);
TreePtr FindNode(int value, TreePtr root, FILE* fp2);
void PrintInorder(TreePtr root, FILE* fp2);
void PrintPreorder(TreePtr root, FILE* fp2);
void PrintPostorder(TreePtr root, FILE* fp2);
TreePtr FindMin(TreePtr root) {
	if (root == NULL) return NULL;
	else {
		while (root->left != NULL) {
			root = root->left;
		}
	}
	return root;
}
TreePtr FindMax(TreePtr root) {
	if (root == NULL) return NULL;
	else if (root->right == NULL) {
		return root;
	}
	else {
		return FindMax(root->right);
	}
}

int main() {
	FILE* fp1, * fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	char cmd[5];
	int v;

	TreePtr proot = NULL;

	while (fscanf(fp1, "%s", cmd) != EOF) {
		if (strcmp(cmd, "i") == 0) {
			fscanf(fp1, "%d", &v);
			PrintDebug("input %d\n", v);
			proot = InsertNode(v, proot, fp2);
		}
		else if (strcmp(cmd, "d") == 0) {
			fscanf(fp1, "%d", &v);
			PrintDebug("delete %d\n", v);
		}
		else if (strcmp(cmd, "f") == 0) {
			fscanf(fp1, "%d", &v);
			PrintDebug("find %d\n", v);
			FindNode(v, proot, fp2);
		}
		else if (strcmp(cmd, "pi") == 0) {
			PrintDebug("pi\n");
			fprintf(fp2, "pi -");
			PrintInorder(proot, fp2);
			fprintf(fp2, "\n");
		}
		else if (strcmp(cmd, "pr") == 0) {
			PrintDebug("pr\n");
			fprintf(fp2, "pr -");
			PrintPreorder(proot, fp2);
			fprintf(fp2, "\n");
		}
		else if (strcmp(cmd, "po") == 0) {
			PrintDebug("po\n");
			fprintf(fp2, "po -");
			PrintPostorder(proot, fp2);
			fprintf(fp2, "\n");
		}
		else {
			PrintDebug("ERROR: type cmd\n");
		}

	}


	fclose(fp1);
	fclose(fp2);

	return 0;
}
TreePtr InsertNode(int value, TreePtr root, FILE* fp2) {
	if (root == NULL) {
		root = (TreePtr)malloc(sizeof(struct TreeNode));
		if (root == NULL) {
			printf("Out of space!\n");
		}
		else {
			root->value = value;
			root->left = root->right = NULL;
		}
	}
	else if (value < root->value) {
		root->left = InsertNode(value, root->left, fp2);
	}
	else if (value > root->value) {
		root->right = InsertNode(value, root->right, fp2);
	}
	else {
		//the value is already in the tree
		fprintf(fp2, "%d already exists.\n", value);
	}
	return root;
}
TreePtr DeleteNode(int value, TreePtr root, FILE* fp2) {
	TreePtr Tmp;
	if (root == NULL) fprintf(fp2, "Element not found\n");
	else if (value < root->value) {
		DeleteNode(value, root->left, fp2);
	}
	else if (value > root->value) {
		DeleteNode(value, root->right, fp2);
	}
	else if (root->left && root->right) {
		Tmp = FindMin(root->right);
		root->value = Tmp->value;
		root->right = DeleteNode(root->value, root->right, fp2);
	}
	else {
		Tmp = root;
		if (root->left == NULL) {
			root = root->right;
		}
		else if (root->right == NULL) {
			root = root->left;
		}
		free(Tmp);
	}
	return root;
}
TreePtr FindNode(int value, TreePtr root, FILE* fp2) {
	if (root == NULL) {
		fprintf(fp2, "%d is not in the tree.\n", value);
		return NULL;
	}
	if (value < root->value) {
		FindNode(value, root->left, fp2);
	}
	else if (value > root->value) {
		FindNode(value, root->right, fp2);
	}
	else {
		fprintf(fp2, "%d is in the tree.\n", value);
		return root;
	}
}
void PrintInorder(TreePtr root, FILE* fp2) {
	if (root) {
		PrintInorder(root->left, fp2);
		fprintf(fp2, " %d", root->value);
		PrintInorder(root->right, fp2);
	}
}
void PrintPreorder(TreePtr root, FILE* fp2) {
	if (root) {
		fprintf(fp2, " %d", root->value);
		PrintPreorder(root->left, fp2);
		PrintPreorder(root->right, fp2);
	}
}
void PrintPostorder(TreePtr root, FILE* fp2) {
	if (root) {
		PrintPostorder(root->left, fp2);
		PrintPostorder(root->right, fp2);
		fprintf(fp2, " %d", root->value);
	}
}
