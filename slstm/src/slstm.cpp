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
    
    std::unordered_map<DATA_TYPE, std::uint16_t> label;
    std::unordered_map<DATA_TYPE, std::uint16_t> func;
    
    std::uint16_t buf[BUF_SIZE] = {0};
    read(0, buf, BUF_SIZE);
    
    slbin_header *header = (slbin_header *)buf;
    Word *phead = (Word *)(header + 1);
    
    uint16_t pc = 0;
    Word *p = phead + pc;
    
    uint16_t bp = 0;
    
    DATA_TYPE ret;
    
    uint16_t length = header->size / sizeof(Word);
    while(pc <= length){
        p = phead + pc;
        if(p->op == INS_LABEL){
            label[p->arg] = pc;
        }
        
        else if(p->op == INS_ENTRY){
            func[p->arg] = pc;
        }
        
        pc++;
    }
    
    fprintf(stderr, "----------[debug info]----------\n");
    fprintf(stderr, "word length(bytes) : %ld\n", sizeof(Word));
    fprintf(stderr, "program length(bytes) : %d\n", header->size);
    fprintf(stderr, "program length(steps) : %d\n", length);
    fprintf(stderr, "\n");
    
    for(auto itr = label.begin(); itr != label.end(); itr++){
        fprintf(stderr, "[label : offset] %d : %d\n", itr->first, itr->second);
    }
    for(auto itr = func.begin(); itr != func.end(); itr++){
        fprintf(stderr, "[func  : offset] %d : %d\n", itr->first, itr->second);
    }
    fprintf(stderr, "--------------------------------\n");
    
    pc = 0;
    p = phead + pc;
    while(pc <= length){
        p = phead + pc;
        
        fprintf(stderr, "pc=0x%04X, ", pc);
        fprintf(stderr, "bp=0x%04X ", bp);
        switch(p->op){
            case INS_PUSH:
                fprintf(stderr, "(PUSH 0x%.2X)   ", p->arg);
                push(p->arg);
                st._dump();
                break;
            case INS_POP:
                fprintf(stderr, "(POP)         ");
                pop();
                st._dump();
                break;
            case INS_ADD:
                fprintf(stderr, "(ADD)         ");
                add();
                st._dump();
                break;
            case INS_SUB:
                fprintf(stderr, "(SUB)         ");
                sub();
                st._dump();
                break;
            case INS_MUL:
                fprintf(stderr, "(MUL)         ");
                mul();
                st._dump();
                break;
            case INS_GT:
                fprintf(stderr, "(GT)          ");
                gt();
                st._dump();
                break;
            case INS_LT:
                fprintf(stderr, "(LT)          ");
                lt();
                st._dump();
                break;
            case INS_JMP:
                fprintf(stderr, "(JMP 0x%.2X)    ", p->arg);
                pc = label[p->arg];
                st._dump();
                continue;
                break;
            case INS_BEQ0:
                fprintf(stderr, "(BEQ0 0x%.2X)   ", p->arg);
                if(pop() == 0){
                    pc = label[p->arg];
                    st._dump();
                    continue;
                }
                st._dump();
                break;
            case INS_ENTRY:
                bp = st.offset();
                fprintf(stderr, "(ENTRY 0x%.2X, bp=%04d)\n", p->arg, bp);
                break;
            case INS_FRAME:
                if ((p - 1)->op != INS_ENTRY){
                    fprintf(stderr, "ERROR! INS_FRAME must be used first of functions.\n");
                    exit(-1);
                }
                fprintf(stderr, "(FRAME 0x%.2X)  ", p->arg);
                for(int i = 0; i < p->arg; i++){
                    push(0x00);
                }
                st._dump();
                break;
            case INS_STOREL:
                fprintf(stderr, "(STOREL 0x%.2X) ", p->arg);
                *(st.bottom() + bp + p->arg) = st.top();
                st._dump();
                break;
            case INS_LOADL:
                fprintf(stderr, "(LOADL 0x%.2X)  ", p->arg);
                push(*(st.bottom() + bp + p->arg));
                st._dump();
                break;
            case INS_CALL:
                fprintf(stderr, "(CALL 0x%.2X)   ", p->arg);
                push(pc);
                push(bp);
                pc = func[p->arg];
                bp = st.offset();
                st._dump();
                continue;
                break;
            case INS_RET:
                fprintf(stderr, "(RET 0x%.2X)    ", p->arg);
                ret = st.top();
                st.sp(bp);
                bp = pop();
                pc = pop();
                push(ret);
                st._dump();
                break;
            case INS_LOADA:
                fprintf(stderr, "(LOADA 0x%.2X)  ", p->arg);
                push(*(st.bottom() + bp - (p->arg) - 3));
                st._dump();
                break;
            case INS_STOREA:
                fprintf(stderr, "(STOREA 0x%.2X) ", p->arg);
                *(st.bottom() + bp - (p->arg) - 3) = pop();
                st._dump();
                break;
            case INS_POPR:
                fprintf(stderr, "(POPR 0x%.2X)   ", p->arg);
                ret = pop();
                for(int i = 0; i < p->arg; i++){
                    pop();
                }
                push(ret);
                st._dump();
                break;
            case INS_END:
                fprintf(stderr, "(END)\n");
                goto end;
            default:
                fprintf(stderr, "\n");
                break;
        }
        
        pc++;
    }
    
end:
    return(0);
}
