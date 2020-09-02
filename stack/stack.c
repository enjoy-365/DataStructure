#include "stack.h"

#include <stdio.h>
#include <string.h>

#define MaxSize 100

int main(void){
    int test;
    char type[5];
    int num;
    
    FILE* read;
    FILE* write;
    read = fopen("input.txt", "r");
    write = fopen("output.txt", "w");

    fscanf(read, "%d", &test);

    Stack S1 = CreateStack(MaxSize);

    while(test--){
        fscanf(read, "%s", type);

        if(strcmp(type, "push")==0){
            fscanf(read, "%d", &num);
            push(num, S1, write); 
        }else{
            pop(S1, write); 
        }
    }

    fclose(read);
    fclose(write);
    return 0;
}
