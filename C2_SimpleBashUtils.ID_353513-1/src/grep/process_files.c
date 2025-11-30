#include "s21_grep.h"

void process_file(int first_file_index, int argc, char *argv[], Flags *flagie, char** pattern, int pattern_count) {
    for (int fi = first_file_index; fi < argc; fi++) {
        const char *filename = argv[fi];
        FILE *fp = fopen(filename, "r");

        if (fp != NULL) {

            char *line = NULL;
            size_t len = 0;
            ssize_t read;

            regex_t regex[pattern_count];
            regmatch_t match;//переменная для отлова совпадений

            for (int i = 0; i < pattern_count; i++) {
                if (flagie->iflag == 1){
                    regcomp(&regex[i], pattern[i], REG_ICASE);
                }
                else {
                    regcomp(&regex[i], pattern[i], 0);
                }
            }

            

            while ((read = getline(&line, &len, fp)) != -1) {
                for (int k = 0; k < pattern_count; k++){
                    if (regexec(&regex[k], line, 1, &match, 0) == 0) {
                        if (first_file_index == argc - 1){
                            printf("%s", line);
                            break;
                        }
                        else {
                            printf("%s:%s", filename, line);
                            break;
                        }
                    }
                }
            }
            //for (int i = 0; i < 2; i++) regfree(&regex[i]); //освобождение ресурсов
            fclose(fp);
        } else {
            fprintf(stderr, "grep: cannot open %s\n", filename);
        }
    }
}