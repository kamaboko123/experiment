#include <cstdio>
#include <stack>
#include <cstdint>
#include <unistd.h>
#include "word.hpp"

#define BUF_SIZE 256

void dump_stack(std::stack<OPERAND_TYPE> st){
    printf("----[Stack]----\n");
    for(int i = 0; st.size() > 0; i++){
        fprintf(stderr, "%2x: %2x\n", i, st.top());
        st.pop();
    }
    printf("---------------\n\n");
}

int main(void){
    fprintf(stderr, "word length : %ld\n", sizeof(Word));
    uint8_t buf[BUF_SIZE] = {0};
    read(0, buf, BUF_SIZE);
    
    std::stack<OPERAND_TYPE> st;
    
    Word *p = (Word *)buf;
    
    dump_stack(st);
    for(int i = 0; p->op != INS_END; i += sizeof(Word)){
        switch(p->op){
            OPERAND_TYPE n1, n2;
            
            case INS_PUSH:
                st.push(p->arg);
                break;
            case INS_POP:
                st.pop();
                break;
            case INS_ADD:
                n1 = st.top();
                st.pop();
                n2 = st.top();
                st.pop();
                st.push(n1 + n2);
                break;
            case INS_SUB:
                n1 = st.top();
                st.pop();
                n2 = st.top();
                st.pop();
                st.push(n2 - n1);
                break;
            default:
                break;
        }
        p++;
        dump_stack(st);
    }
    
    return(0);
}
