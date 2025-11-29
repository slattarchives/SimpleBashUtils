#include "s21_cat.h"

void process_file(int first_file_index, int argc, char *argv[], Flags *flagie) {
    for (int fi = first_file_index; fi < argc; fi++) {
        const char *filename = argv[fi];
        FILE *fp = fopen(filename, "r");

        if (fp != NULL) {
            int c;
            int before_char = '\n';
            int count = 0;
            int line_number = 1;

            while ((c = fgetc(fp)) != EOF) {
                if (flagie->sflag && c == '\n' && (before_char == '\n' || before_char == '\0')) {
                    count++;
                } else {
                    count = 0;
                }
                
                if (count <= 1) {
                    if (((flagie->nflag && before_char == '\n') && !flagie->bflag) || 
                        (flagie->bflag && before_char == '\n' && c != '\n')) {
                        printf("%6d\t", line_number++);
                    }
                    flags_left(&c, flagie);
                    if (c != -1) {
                        putchar(c);
                    }
                    before_char = c;
                }
            }
            fclose(fp);
        } else {
            fprintf(stderr, "cat: cannot open %s\n", filename);
        }
    }
}