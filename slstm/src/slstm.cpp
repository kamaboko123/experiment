#include <cstdio>
#include <cstdint>
#include <unistd.h>
#include <unordered_map>
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

void mul(){
    int n1 = pop();
    int n2 = pop();
    push(n2 * n1);
}

void gt(){
    int n1 = pop();
    int n2 = pop();
    push(n1 < n2);
}

void lt(){
    int n1 = pop();
    int n2 = pop();
    push(n1 > n2);
}

int main(void){
    
    std::unordered_map<DATA_TYPE, std::size_t> label;
    
    std::size_t buf[BUF_SIZE] = {0};
    read(0, buf, BUF_SIZE);
    
    Word *head = (Word *)buf;
    
    size_t pc = 0;
    Word *p = head + pc;
    while(p->op != INS_END){
        p = head + pc;
        if(p->op == INS_LABEL){
            label[p->arg] = pc;
        }
        pc++;
    }
    
    fprintf(stderr, "word length : %ld\n", sizeof(Word));
    for(auto itr = label.begin(); itr != label.end(); itr++){
        fprintf(stderr, "[label : offset] %d : %ld\n", itr->first, itr->second);
    }
    
    pc = 0;
    p = head + pc;
    while(p->op != INS_END){
        p = head + pc;
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
            case INS_MUL:
                fprintf(stderr, "(MUL)       ");
                mul();
                st._dump();
                break;
            case INS_GT:
                fprintf(stderr, "(GT)        ");
                gt();
                st._dump();
                break;
            case INS_LT:
                fprintf(stderr, "(LT)        ");
                lt();
                st._dump();
                break;
            case INS_JMP:
                fprintf(stderr, "(JMP 0x%.2x)  ", p->arg);
                pc = label[p->arg];
                st._dump();
                continue;
                break;
            default:
                break;
        }
        
        pc++;
    }
    
    return(0);
}
