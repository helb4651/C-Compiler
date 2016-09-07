#ifndef SCANTYPEH
#define SCANTYPEH
struct TokenData {
    int tokenclass;
    int linenum;
    char *tokenstring;
    bool bvalue;
};
#endif