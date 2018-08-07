#ifndef INCLUED_SLSTM_WORD
#define INCLUED_SLSTM_WORD

#define INS_PUSH 0x01
#define INS_POP 0x02
#define INS_ADD 0x03
#define INS_SUB 0x04
#define INS_END 0xFF

typedef uint16_t OPERAND_TYPE;

typedef struct Word{
    uint8_t op;
    OPERAND_TYPE arg;
} Word;

#endif
