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
    std::unordered_map<DATA_TYPE, std::size_t> func;
    
    std::size_t buf[BUF_SIZE] = {0};
    read(0, buf, BUF_SIZE);
    
    slbin_header *header = (slbin_header *)buf;
    Word *phead = (Word *)header + 1;
    
    size_t pc = 0;
    Word *p = phead + pc;
    
    DATA_TYPE* bp = 0;
    
    size_t length = header->size / sizeof(Word);
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
    
    fprintf(stderr, "word length : %ld\n", sizeof(Word));
    for(auto itr = label.begin(); itr != label.end(); itr++){
        fprintf(stderr, "[label : offset] %d : %ld\n", itr->first, itr->second);
    }
    for(auto itr = func.begin(); itr != func.end(); itr++){
        fprintf(stderr, "[func  : offset] %d : %ld\n", itr->first, itr->second);
    }
    
    pc = 0;
    p = phead + pc;
    while(pc <= length){
        p = phead + pc;
        switch(p->op){
            case INS_PUSH:
                fprintf(stderr, "(PUSH 0x%.2x)   ", p->arg);
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
                fprintf(stderr, "(JMP 0x%.2x)    ", p->arg);
                pc = label[p->arg];
                st._dump();
                continue;
                break;
            case INS_BEQ0:
                fprintf(stderr, "(BEQ0 0x%.2x)   ", p->arg);
                if(pop() == 0){
                    pc = label[p->arg];
                    st._dump();
                    continue;
                }
                st._dump();
                break;
            case INS_ENTRY:
                bp = st.sp();
                fprintf(stderr, "(ENTRY 0x%.2x, bp=%p)\n", p->arg, bp);
                break;
            case INS_FRAME:
                if ((p - 1)->op != INS_ENTRY){
                    fprintf(stderr, "ERROR! INS_FRAME must be used first of functions.\n");
                    exit(-1);
                }
                fprintf(stderr, "(FRAME 0x%.2x)  ", p->arg);
                for(int i = 0; i < p->arg; i++){
                    push(0x00);
                }
                st._dump();
                break;
            case INS_STOREL:
                fprintf(stderr, "(STOREL 0x%.2x) ", p->arg);
                *(bp + p->arg) = st.top();
                st._dump();
                break;
            case INS_LOADL:
                fprintf(stderr, "(LOADL 0x%.2x)  ", p->arg);
                push(*(bp + p->arg));
                st._dump();
                break;
            case INS_END:
                fprintf(stderr, "(END)\n");
                goto end;
            default:
                break;
        }
        
        pc++;
    }
    
end:
    return(0);
}
