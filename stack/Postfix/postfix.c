#include <stdio.h>
#include <algorithm>
#include <string>
#include <string.h>
#include <stdlib.h>

using namespace std;

typedef int ElementType;
typedef struct Node* PtrToNode;
typedef PtrToNode Stack;

typedef struct Node {
	ElementType element;
	PtrToNode next;
};

Stack CreateStack() {
	Stack S;
	S = (PtrToNode)malloc(sizeof(struct Node));
	S->next = NULL;

	return S;
}
void Push(Stack S, ElementType x) {
	PtrToNode temp;
	temp = (PtrToNode)malloc(sizeof(struct Node));
	temp->element = x;
	temp->next = S->next;
	S->next = temp;
}
int IsEmpty(Stack S) {
	if (S->next == NULL) return 1;
	else return 0;
}
void Pop(Stack S) {
	PtrToNode first;
	if (IsEmpty(S)) {
		//fprintf(fp2,"Empty Stack\n");
		return;
	}
	else {
		first = S->next;
		S->next = first->next;
		free(first);
	}
}
char Top(Stack S) {
	return S->next->element;
}

int main() {
	FILE* fp1, * fp2;

	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");

	char str[105];
	char postfix[105];
	int idx = 0;
	fscanf(fp1, "%s", str);



	//print Infix Form
	fprintf(fp2, "Infix Form : ");
	for (int i = 0; str[i] != '#'; i++) {
		fprintf(fp2, "%c", str[i]);
	}
	fprintf(fp2, "\n");

	//print PostfixForm
	Stack S = CreateStack();

	for (int i = 0; str[i] != '#'; i++) {
		if (str[i] >= '0' && str[i] <= '9') {
			postfix[idx++] = str[i];
			//idx++;
		}
		else if (str[i] == '(') {
			Push(S, str[i]);
		}
		else if (str[i] == ')') {
			while (Top(S) != '(') {
				postfix[idx++] = Top(S);
				//idx++;
				Pop(S);
			}
			Pop(S);//erase the left parenthesis;

		}
		else if (str[i] == '+' || str[i] == '-') {
			if (IsEmpty(S) || Top(S) == '(') Push(S, str[i]);
			else {
				while (!IsEmpty(S) && Top(S) != '(') {
					postfix[idx++] = Top(S);
					//idx++;
					Pop(S);
				}
				Push(S, str[i]);
			}
		}
		else if (str[i] == '%' || str[i] == '/' || str[i] == '*') {
			if (IsEmpty(S) || Top(S) == '(' || Top(S) == '+' || Top(S) == '-') Push(S, str[i]);
			else {
				while (!IsEmpty(S) && Top(S) != '(') {
					postfix[idx++] = Top(S);
					//idx++;
					Pop(S);
				}
				Push(S, str[i]);
			}
		}

	}
	//end of expression -> pop the stack
	while (!IsEmpty(S)) {
		postfix[idx++] = Top(S);
		//idx++;
		Pop(S);
	}
	postfix[idx] = '\0';
	fprintf(fp2, "Postfix Form : %s\n", postfix);

	//if you use int postfix[105]
	/*
	fprintf(fp2, "Postfix Form : ");
	for (int i = 0; i < idx; i++) {
		fprintf(fp2, "%c", postfix[i]);
	}
	fprintf(fp2, "\n");
	*/

	//for checking postfix
	/*for (int i = 0; i < idx; i++) {
		printf("%c", postfix[i]);
	}*/


	fprintf(fp2, "Evaluation Result : ");

	//evaluation
	int n1, n2;
	for (int i = 0; i < idx; i++) {
		if (postfix[i] >= '0' && postfix[i] <= '9') {
			Push(S, postfix[i] - '0');
		}
		else {
			n2 = Top(S);
			Pop(S);
			n1 = Top(S);
			Pop(S);
			if (postfix[i] == '+') {
				Push(S, n1 + n2);
			}
			else if (postfix[i] == '-') {
				Push(S, n1 - n2);
			}
			else if (postfix[i] == '%') {
				Push(S, n1 % n2);
			}
			else if (postfix[i] == '*') {
				Push(S, n1 * n2);
			}
			else if (postfix[i] == '/') {
				Push(S, n1 / n2);
			}
		}
	}

	fprintf(fp2, "%d\n", Top(S));


	fclose(fp1);
	fclose(fp2);
	return 0;
}