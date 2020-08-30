#include <stdio.h>
#include <string.h>
#include <ctype.h> //isspace()

#define MAX_LEN 4000

char* RightTrim(char* s){
    //char t[MAX_LEN];
    char* t;
    char* right;
    
    strcpy(t, s);
    //int idx = strlen(t);

    //strcpy(t, s);
    right = s + strlen(t)-1;//the positon right before the NULL

    while(right != s && isspace(*right)){
        right--;
        //idx--;
        //t[idx] = '\0';
        *t = '\0';
    }// if (*right)is not space until right == t, that means the given string is empty string.
    //*(right+1) = "\0";
    //s = t;
    return t;
}

char* LeftTrim(char* s){
    char* left;
    left = s;

    while(*left != '\0'){
        if(isspace(*left)){
            left++;
        }else{
            s = left;
            break;
        }
    }
    return s;
}
