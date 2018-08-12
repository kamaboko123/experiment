#include <cstdio>
#include <cstdint>
#include <unistd.h>
#include <fcntl.h>
#include "word.hpp"

int main(int argc, char *argv[]){
    
    if(argc != 2){
        fprintf(stderr, "You need specify output filename\n");
        return -1;
    }
    /*
    Word TEST_BIN[] = {
        INS_ENTRY, 0x00,
        INS_FRAME, 0x02,
        INS_PUSH, 0x02,
        INS_PUSH, 0x03,
        INS_STOREL, 0x00,
        INS_PUSH, 0x05,
        INS_POP, 0x00,
        INS_ADD, 0x00,
        INS_PUSH, 0x02,
        INS_SUB, 0x00,
        INS_JMP, 0x01,
        INS_DUM, 0x00,
        INS_DUM, 0x00,
        INS_DUM, 0x00,
        INS_DUM, 0x00,
        INS_DUM, 0x00,
        INS_DUM, 0x00,
        INS_DUM, 0x00,
        
        INS_LABEL, 0x01,
        INS_PUSH, 0x02,
        INS_PUSH, 0x03,
        INS_MUL, 0x00,
        INS_LT, 0x00,
        INS_BEQ0, 0x02,
        INS_CALL, 0x01,
        //INS_END, 0x00,
        
        INS_LABEL, 0x02,
        INS_PUSH, 0xFF,
        INS_PUSH, 0xFF,
        INS_PUSH, 0x11,
        INS_STOREL, 0x01,
        INS_LOADL, 0x00,
        INS_END, 0x00,
        
        INS_ENTRY, 0x01,
        INS_FRAME, 0x01,
        INS_PUSH, 0xAB,
        INS_STOREL, 0x00,
        INS_CALL, 0x02,
        INS_END, 0x00,
        
        INS_ENTRY, 0x02,
        INS_PUSH, 0xbb,
        INS_RET, 0x00,
        INS_END, 0x00,
    };*/
    
    /*
     * //こんな処理を書きたい
     * main(){
     *     hoge(0xAA, 0x05);
     * }
     * hoge(n1, n2){
     *     for(i = 0; i < n2; i++) print(n1);
     * }
     * */
    Word TEST_BIN[] = {
        INS_ENTRY, 0x00,
        INS_PUSH, 0x05, //n2
        INS_PUSH, 0xAA, //n1
        INS_CALL, 0x01,
        INS_POPR, 0x02,
        INS_POP, 0x00,
        INS_END, 0x00,
        
        //func(n1, n2)
        INS_ENTRY, 0x01,
        INS_FRAME, 0x01,
        
        //loop init
        INS_PUSH, 0x00,
        INS_STOREL, 0x00,
        INS_POP, 0x00,
        
        //loop continuous check
        INS_LABEL, 0x01,
        INS_LOADL, 0x00,
        INS_LOADA, 0x01, //n2
        INS_LT, 0x00,
        INS_BEQ0, 0x11,
        
        //procedure in loop
        INS_LOADA, 0x00, //n1
        INS_PRINT, 0x00,
        INS_POP, 0x00,
        
        //update loop veriable
        INS_LOADL, 0x00
        INS_PUSH, 0x01,
        INS_ADD, 0x00,
        INS_STOREL, 0x00,
        INS_POP, 0x00,
        
        INS_JMP, 0x01,
        
        //exit loop
        INS_LABEL, 0x11,
        INS_POP, 0x00,
        INS_RET, 0x00,
    };
    
    slbin_header header = {sizeof(TEST_BIN)};
    
    int fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    write(fd, &header, sizeof(slbin_header));
    write(fd, TEST_BIN, sizeof(TEST_BIN));
    close(fd);
    
    return 0;
}
