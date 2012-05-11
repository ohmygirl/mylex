#include "mylex.h"

extern int cur_line, cur_col, err_line, err_col;
extern char id[21];
extern int token_num;

FILE *source, *out;

int main() {
    clock_t start, finish;
    double duration;
    char filename[21] = "\0";
    char outname[21] = "\0";
    int flag;
    FILE *stream;
    char line[100];
    printf("PL/0 Lexical Analyzer\n\n");
    printf("Please enter the source file: ");
    gets_s(filename, 20);
    if ((source = fopen(filename, "r")) == NULL) {
        printf("Error: the file \"%s\" can not be opened, press any key to exit\n", filename);
        _getch();
        return 1;
    } else {
        int i;
        start = clock();
        for (i = 0; i < (int)strlen(filename) - 4; ++i)
            outname[i] = filename[i];
        strcat(outname, ".out");
        if ((out = fopen(outname, "w+")) == NULL) {
            printf("Error: can not create \"%s\" in current path, press any key to exit\n", outname);
            _getch();
            return 1;
        }
        cur_line = 1;
        cur_col = 0;
        token_num = 0;
        fprintf(out, "+-----+--------------------+--------------------+--------------------+\n");
        fprintf(out, "|%4s |%19s |%19s |%19s |\n", "No", "Symbol", "Symbol Type", "Notes");
        fprintf(out, "+-----+--------------------+--------------------+--------------------+\n");
        while (!feof(source)) {
            token_num++;
            flag = getsym();
            if (flag == 0)
                continue;
            w2f(flag);
        }
        fprintf(out, "+-----+--------------------+--------------------+--------------------+\n");
        fcloseall();
        stream = fopen(outname, "r");
        while (1) {
            fgets(line, 100, stream);
            if (feof(stream))
                break;
            else
                printf("%s", line);
        }
        fclose(stream);
        finish = clock();
        duration = (double)(finish - start) / CLOCKS_PER_SEC;
        printf("completed successfully. (%2.3f secs)\n", duration);
    }
    return 0;
}
