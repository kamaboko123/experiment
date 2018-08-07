#include <cstdio>
#include <stack>
#include <cstdint>
#include <unistd.h>
#include "word.hpp"

#define BUF_SIZE 256

std::stack<OPERAND_TYPE> st;

void dump_stack(std::stack<OPERAND_TYPE> st){
    fprintf(stderr, "|Stack|");
    while(st.size() > 0){
        fprintf(stderr, " 0x%.2x", st.top());
        st.pop();
    }
    fprintf(stderr, "\n");
}

void push(OPERAND_TYPE n){
    st.push(n);
}

OPERAND_TYPE pop(){
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
    
    dump_stack(st);
    while(p->op != INS_END){
        switch(p->op){
            case INS_PUSH:
                fprintf(stderr, "(PUSH 0x%.2x) ", p->arg);
                push(p->arg);
                dump_stack(st);
                break;
            case INS_POP:
                fprintf(stderr, "(POP)       ");
                pop();
                dump_stack(st);
                break;
            case INS_ADD:
                fprintf(stderr, "(ADD)       ");
                add();
                dump_stack(st);
                break;
            case INS_SUB:
                fprintf(stderr, "(SUB)       ");
                sub();
                dump_stack(st);
                break;
            case INS_JMP:
                fprintf(stderr, "(JMP 0x%.2x)  ", p->arg);
                p = (Word *)buf + p->arg;
                dump_stack(st);
                continue;
                break;
            default:
                break;
        }
        
        p++;
    }
    
    return(0);
}
