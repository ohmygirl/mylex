#include "mylex.h"

extern FILE *out;
extern int cur_line, cur_col, err_line, err_col;
extern int num;
extern char id[21];
extern int token_num;

char *keywords[13] = {
    "begin", "call", "const", "do", "end", "if", "odd", "procedure", "read", "then", "var", "while", "write"
};

int find_tab(char id[21]) {
    int i;
    for (i = 0; i !=13; ++i) {
        if (!strcmp(keywords[i], id))
            return i;
        else
            continue;
    }
    return -1;
}

SYMBOL get_data(int No) {
    switch (No) {
        case 0 :
            return beginsym;
        case 1 :
            return callsym;
        case 2 :
            return constsym;
        case 3 :
            return dosym;
        case 4 :
            return endsym;
        case 5 :
            return ifsym;
        case 6 :
            return oddsym;
        case 7 :
            return proceduresym;
        case 8 :
            return readsym;
        case 9 :
            return thensym;
        case 10 :
            return varsym;
        case 11 :
            return whilesym;
        case 12 :
            return writesym;
        default :
            error(">>> Error : ");
            return nul;
    }
}

int error() {
    fprintf(out, "|%4d |%19s |%19s %19s |\n", token_num, id, "nul", "invalid character");
    return 0;
}
