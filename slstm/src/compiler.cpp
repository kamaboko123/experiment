#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <unordered_map>

#define SYMBOLS_MAX 128

enum code{
    SYM,
    NUM,
    PLUS,
    MINUS
};

typedef struct Ast{
    enum code op;
    int val;
    struct Symbol *sym;
    struct Ast *l, *r;
} Ast;

typedef struct Symbol {
    char name[16];
    int val;
    Ast *func_params;
    Ast *func_body;
} Symbol;

Symbol sym_tbl[SYMBOLS_MAX];
uint16_t sym_tbl_size = 0;

Ast *make_ast(code op, Ast *l, Ast *r){
    Ast *p;
    
    p = (Ast *)malloc(sizeof(Ast));
    p->op = op;
    p->r = r;
    p->l = l;
    
    return p;
}

Ast *make_num(int val){
    Ast *p;
    p = (Ast *)malloc(sizeof(Ast));
    p->op = NUM;
    p->val = val;
    
    return p;
}

Symbol *find_sym(const char *name){
    Symbol *sp = nullptr;
    
    for(int i = 0; i < SYMBOLS_MAX; i++){
        if(strcmp(sym_tbl[i].name, name) == 0){
            sp = &sym_tbl[i];
            break;
        }
    }
    
    if(sp == nullptr){
        sp = &sym_tbl[sym_tbl_size++];
        strncpy(sp->name, name, sizeof(sp->name));
    }
    
    return sp;
}

Ast *make_sym(const char *name){
    Ast *p;
    
    p = (Ast *)malloc(sizeof(Ast));
    p->op = SYM;
    p->sym = find_sym(name);
    
    return p;
}

Symbol *get_sym(Ast *p){
    if(p->op != SYM){
        fprintf(stderr, "bad access to symbol.\n");
        exit(-1);
    }
    return p->sym;
}

int main(void){
    return 0;
}
