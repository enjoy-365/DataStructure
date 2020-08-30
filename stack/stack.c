#include "stack.h"

#include <stdio.h>
#include <string.h>

int main(void){
    int test;
    char type[5];
    int num;
    
    FILE* read;
    FILE* write;
    read = fopen("input.txt", "r");
    write = fopen("output.txt", "w");

    fscanf(read, "%d", &test);

    while(test--){
        fscanf(read, "%s", type);

        if(strcmp(type, "push")==0){
            fscanf(read, "%d", &num);
        
            
        }else{
            
        }
    }

    fclose(read);
    fclose(write);
    return 0;
}
