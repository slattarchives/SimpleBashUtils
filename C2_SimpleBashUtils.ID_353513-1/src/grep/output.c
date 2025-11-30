#include "s21_grep.h"

void output(int first_file_index, int argc, int line_num, const char *line, const char* filename, Flags *flagie, int *count_cflag){
    if (flagie->cflag == 1) 
        (*count_cflag)++;
    else if (flagie->lflag == 1) 
        printf("%s", filename);
    else {
        if (first_file_index == argc - 1){
            if (flagie->nflag == 1) printf("%d:%s", line_num, line);
            else printf("%s", line);
            //break;
        }
        else {
            if (flagie->nflag == 1) printf("%s:%d:%s", filename, line_num, line);
            else printf("%s:%s", filename, line);
            //break;
        }
    } 
}