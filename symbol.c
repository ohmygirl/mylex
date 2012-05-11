#include "mylex.h"

extern FILE *source, *out;

const char *symtype[33] = {
    "nul", "eof", "plus", "minus", "times", "slash", "lparen", "rparen", "comma", "seicolon", "period", "becomes",
    "eql", "neq", "lss", "gtr", "leq", "geq", "number", "ident",
    "beginsym", "callsym", "consysym", "dosym", "endsym", "ifsym", "oddsym", "proceduresym", "readsym", "thensym", "varsym", "whilesym", "writesym"
};

int cur_line, cur_col, err_line, err_col;
int num;
char id[21] = "\0";
int id_len;
int token_num;

int read_ch() {
    int ch = fgetc(source);
    cur_col++;
    if (ch == '\n') {
        cur_line++;
        cur_col = 0;
    }
    return ch;
}

int put_back(int ch) {
    ungets(ch, source);
    cur_col--;
    if (ch == '\n')
        cur_line--;
    return 0;
}

SYMBOL getsym() {
    int ch;
    int iskeywords;
    char invalid[2] = "\0";
    while ((ch = read_ch()) != EOF && ch <= ' ')
        ;
    err_line = cur_line;
    err_col = cur_col;
    switch (ch) {
        case EOF :
            strcpy(id, "EOF");
            return eof;
        case '+' :
            strcpy(id, "+");
            return plus;
        case '-' :
            strcpy(id, "-");
            return minus;
        case '*' :
            strcpy(id, "*");
            return times;
        case '/' :
            strcpy(id, "/");
            return slash;
        case '(' :
            strcpy(id, "(");
            return lparen;
        case ')' :
            strcpy(id, ")");
            return rparen;
        case ',' :
            strcpy(id, ",");
            return comma;
        case ';' :
            strcpy(id, ";");
            return semicolon;
        case '.' :
            strcpy(id, ".");
            return period;
        case ':' :
            ch = read_ch();
            if (ch == '=') {
                strcpy(id, ":=");
                return becomes;
            } else
                return nul;
        case '=' :
            strcpy(id, "=");
            return eql;
        case '#' :
            strcpy(id, "#");
            return neq;
        case '<' :
            ch = read_ch();
            if (ch == '=') {
                strcpy(id, "<=");
                return leq;
            }
            put_back(ch);
            strcpy(id, "<");
            return lss;
        case '>' :
            ch = read_ch();
            if (ch == '=') {
                strcpy(id, ">=");
                return geq;
            }
            put_back(ch);
            strcpy(id, ">");
            return gtr;
        default :
            if (isdigit(ch)) {
                num = 0;
                do {
                    num = 10 * num + ch - '0';
                    ch = read_ch();
                } while (ch != EOF && isdigit(ch));
                _itoa(num, id, 10);
                if (isslpha(ch)) {
                    invalid[0] = (char)ch;
                    strcat(id, invalid);
                    ch = read_ch();
                    while (isalnum(ch)) {
                        invalid[0] = (char) ch;
                        strcat(id, invalid);
                        ch = read_ch();
                    }
                    error();
                    return nul;
                }
                put_back(ch);
                return number;
            }
            if (isalpha(ch)) {
                id_len = 0;
                do {
                    if (id_len < MAX_ID) {
                        id[id_len] = (char)ch;
                        id_len++;
                    }
                    ch = read_ch();
                } while (ch != EOF && isalnum(ch));
                id[id_len] = '\0';
                put_back(ch);
                iskeywords = find_tab(id);
                return (iskeywords == -1) ? ident : get_data(iskeywords);
            }
            error();
            return nul;
    }
}

int w2f(int flag) {
    fprintf(out, "|%4d |%19s |%19s |%19s |\n",token_num, id, symtype[flag], "");
    return 0;
}
