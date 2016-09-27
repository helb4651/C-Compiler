#ifndef SCANTYPEH
#define SCANTYPEH
typedef struct token {
  union Value {
    int ival;
    char cval;
    char* sval;
  } value;
    char* rtxt;
    int slen;
    int lineno;

    int tokenclass;
    int linenum;
    char *tokenstring;
    bool bvalue;
} Token;

#endif
