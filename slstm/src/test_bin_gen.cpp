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
    
    Word TEST_BIN[] = {
        INS_PUSH, 0x02,
        INS_PUSH, 0x03,
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
        INS_DUM, 0x00,
        
        INS_LABEL, 0x01,
        INS_PUSH, 0x02,
        INS_PUSH, 0x03,
        INS_MUL, 0x00,
        INS_LT, 0x00,
        INS_END, 0x00
    };
    
    int fd = open(argv[1], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    write(fd, TEST_BIN, sizeof(TEST_BIN));
    close(fd);
    
    return 0;
}
