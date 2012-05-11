
#ifndef MYLEX_H
#define MYLEX_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX_ID 20

typedef enum SYMBOL {
    nul, eof, plus, minus, times, slash, lparen, rparen, comma, semicolon, period, becomes,
    eql, neq, lss, gtr, leq, geq, number, ident,
    beginsym, callsym, constsym, dosym, endsym, ifsym, oddsym, proceduresym, readsym, thensym, varsym, whilesym, writesym
} SYMBOL;

int read_ch();
int put_back(int);
SYMBOL getsym();
int w2f(int);

int find_tab(char *);
SYMBOL get_data(int);
int error();

#endif
