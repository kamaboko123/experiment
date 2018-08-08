#include <cstdio>
#include <cstdint>
#include <unistd.h>
#include "easy_stack.hpp"
#include "word.hpp"

#define BUF_SIZE 256
#define STACK_SIZE 256

easy_stack::stack<DATA_TYPE> st(STACK_SIZE);

void push(DATA_TYPE n){
    st.push(n);
}

DATA_TYPE pop(){
    int n = st.top();
    st.pop();
    
    return n;
}

void add(){
    int n1 = pop();
    int n2 = pop();
    push(n1 + n2);
}

void sub(){
    int n1 = pop();
    int n2 = pop();
    push(n2 - n1);
}

int main(void){
    fprintf(stderr, "word length : %ld\n", sizeof(Word));
    
    uint8_t buf[BUF_SIZE] = {0};
    read(0, buf, BUF_SIZE);
    
    Word *p = (Word *)buf;
    
    while(p->op != INS_END){
        switch(p->op){
            case INS_PUSH:
                fprintf(stderr, "(PUSH 0x%.2x) ", p->arg);
                push(p->arg);
                st._dump();
                break;
            case INS_POP:
                fprintf(stderr, "(POP)       ");
                pop();
                st._dump();
                break;
            case INS_ADD:
                fprintf(stderr, "(ADD)       ");
                add();
                st._dump();
                break;
            case INS_SUB:
                fprintf(stderr, "(SUB)       ");
                sub();
                st._dump();
                break;
            case INS_JMP:
                fprintf(stderr, "(JMP 0x%.2x)  ", p->arg);
                p = (Word *)buf + p->arg;
                st._dump();
                continue;
                break;
            default:
                break;
        }
        
        p++;
    }
    
    return(0);
}
