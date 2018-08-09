#ifndef INCLUED_SLSTM_WORD
#define INCLUED_SLSTM_WORD

#define INS_DUM 0x00
#define INS_PUSH 0x01
#define INS_POP 0x02
#define INS_ADD 0x03
#define INS_SUB 0x04
#define INS_MUL 0x05
#define INS_GT 0x06
#define INS_LT 0x07
#define INS_JMP 0x08
#define INS_LABEL 0x09
#define INS_BEQ0 0x10
#define INS_ENTRY 0x11
#define INS_FRAME 0x12
#define INS_LOADL 0x13
#define INS_STOREL 0x14
#define INS_END 0xFE

typedef uint16_t DATA_TYPE;

typedef struct Word{
    uint8_t op;
    DATA_TYPE arg;
} Word;

typedef struct slbin_header{
    size_t size;
} slbin_header;

#endif
