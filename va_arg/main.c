#include<stdio.h>
#include "stdlibc.h"

int return_arg_1(void *dummy, ...);
double return_arg_2(void *dummy, ...);
char return_arg_3(void *dummy, ...);
int return_arg_4(void *dummy, ...);

int main(void){
    char buf[64] = {0};
    
    printf("[int]    %d\n", return_arg_1(NULL, (int)1, (double)2.1, (char)'a', (int)0x12));
    printf("[double] %lf\n", return_arg_2(NULL, (int)1, (double)2.1, (char)'a', (int)0x12));
    printf("[char]   %c\n", return_arg_3(NULL, (int)1, (double)2.1, (char)'a', (int)0x12));
    printf("[int]    0x%x\n", return_arg_4(NULL, (int)1, (double)2.1, (char)'a', (int)0x12));
    
    _sprintf(buf, "%d %d %c %x", (int)1, (int)2, (char)'c', (int)0x12);
    printf("%s\n", buf);
    
    return 0;
}



int return_arg_1(void *dummy, ...){
    my_va_list arg;
    my_va_start(arg, dummy);
    return my_va_arg(arg, int);
}

double return_arg_2(void *dummy, ...){
    my_va_list arg;
    my_va_start(arg, dummy);
    my_va_arg(arg, int);
    return my_va_arg(arg, double);
}

char return_arg_3(void *dummy, ...){
    my_va_list arg;
    my_va_start(arg, dummy);
    my_va_arg(arg, int);
    my_va_arg(arg, double);
    return my_va_arg(arg, char);
}

int return_arg_4(void *dummy, ...){
    my_va_list arg;
    my_va_start(arg, dummy);
    my_va_arg(arg, int);
    my_va_arg(arg, double);
    my_va_arg(arg, char);
    return my_va_arg(arg, int);
}

