#ifndef INCLUED_SLSTM_WORD
#define INCLUED_SLSTM_WORD

#define INS_DUM 0x00
#define INS_PUSH 0x01
#define INS_POP 0x02
#define INS_ADD 0x03
#define INS_SUB 0x04
#define INS_JMP 0x05
#define INS_END 0xFF

typedef uint16_t DATA_TYPE;

typedef struct Word{
    uint8_t op;
    DATA_TYPE arg;
} Word;

#endif
