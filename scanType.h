#ifndef SCANTYPEH
#define SCANTYPEH
typedef struct token {
        int linenum;
        char *tokenstring;

        union type {
                int intVal;
                char charVal;
                char* strVal;
        } Type;

        int ival;
        char cval;
        char* sval;
} Token;

#endif
