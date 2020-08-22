#include "stringtrim.h"
#include <stdio.h>
#include <string.h>

int main(){
    char one[100] = "Shhh!  ";
    char two[100] = "  This has left space";
    
    //char* s3 = "hi  ";
    char* s4 = "  hello";

    //printf("Is right space disappeared?:%s!\n", s1);
    //printf("Is left space disappeared?:%s\n", s2);

    //printf("Is right space disappeared?:%s!\n", s3);
    //printf("Is left space disappeared?:%s\n", s4);

    //char new1[100] = RightTrim(s1);
    //char new2[100] = LeftTrim(s2);

    char* new1 = RightTrim(one);
    char* new2 = LeftTrim(two);

    //char* new3 = RightTrim(s3);
    char* new4 = LeftTrim(s4);

    printf("Is right space disappeared?:%s!\n", new1);
    //fflush(stdout);
    printf("Is left space disappeared?:%s\n", new2);

    //printf("Is right space disappeared?:%s!\n", new3);//-->This works well!!
    printf("Is left space disappeared?:%s\n", new4);//-->This works well!!
    
    //printf("Is right space disappeared?:%s!\n", s3);//doesn't work at all
    //printf("Is left space disappeared?:%s\n", s4);//doesn't work at all
}
