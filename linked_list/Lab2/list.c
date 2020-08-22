#include "list.h"
#include <stdio.h>
#include <string.h>
#include "stringtrim.h"

#define MAX_LINE 100

int main(void){
    char line[100];
    char lineNoType[100];
    char type[2];
    int num;
    char name[20];
    //char last[20];
    //char surname[20];
    //char* firstname;
    //char* surname;

    FILE* read;
    FILE* write;
    read = fopen("input.txt", "r");
    write = fopen("output.txt", "w");

    //printf("before while\n");
    
    List L1 = MakeEmpty();
    ElementType bind;
    List temp = (List)malloc(sizeof(struct Node));

    while(fgets(line, 100, read)!= NULL){
        //printf("%s", line);
        sscanf(line, "%s%[^\n]s", type, lineNoType);
        //sscanf(line, "%s%s%[^\n]s", type, num, name);
        //printf("%s %s %s %s\n", type, num, firstname, surname);
        if(strcmp(type, "i")==0){
            sscanf(lineNoType, "%d%[^\n]s", &num, name);
            //sscanf(last, "%s", name);
            //printf("This is insert\n");
            //printf("num: %s\n", num);
            //printf("name: %s\n", name);

            char* name_without_space = LeftTrim(name);

            bind.studentID = num;
            bind.studentName = (char*)malloc(sizeof(strlen(name_without_space))+1);
            bind.studentName = name_without_space;

            if(Find(bind, L1) != NULL){
                fprintf(write, "Insertion Failed. ID %d already exists.\n", num);
            }
            else{
                Insert(bind, L1,FindInsertPos(bind, L1));
            
                fprintf(write, "Insertion Success : %d\n", num);
                //temp = Find(bind, L1);
                //printf("temp's id:%s temp's name:%s\n", temp->element.studentID, temp->element.studentName);
                //PrintList(L1);
                PrintCurrent(L1, write);
            }
        }
        else if(strcmp(type, "d")==0){
            sscanf(lineNoType, "%d", &num);
            int check = Delete(num, L1);
            //printf("This is delete!\n");
            //sscanf(line, "%d", num);
            
            //Delete(num, L1);
            //PrintCurrent(L1);

            if(check == 0){
                fprintf(write,"Deletion Failed : Student ID %d is not in the list.\n", num);
            }else{
                fprintf(write, "Deletion Success : %d\n", num);
                PrintCurrent(L1, write);
            }
            
        }
        else if(strcmp(type, "f")==0){
            sscanf(lineNoType, "%d", &num);
            temp = FindNum(num, L1);
            if(temp == NULL){
                fprintf(write, "Find %d Failed. There is no student ID\n", num);
            }else{
                fprintf(write, "Find Success : %d %s\n", temp->element.studentID, temp->element.studentName);
            }
        
        }else if(strcmp(type, "p")==0){
            //printf("This is print\n");
            PrintList(L1, write);
        }
    }

    //printf("after while\n");

    fclose(read);
    fclose(write);
    return 0;
}
