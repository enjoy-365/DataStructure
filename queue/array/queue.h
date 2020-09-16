#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int key;
}element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = 0;
