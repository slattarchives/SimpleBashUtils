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

            int count_cflag = 0;//for counting lines for cflag
            int line_num = 1;
            //regmatch_t match;//переменная для отлова совпадений

            for (int i = 0; i < pattern_count; i++) {
                if (flagie->iflag == 1){
                    regcomp(&regex[i], pattern[i], REG_ICASE);
                }
                else {
                    regcomp(&regex[i], pattern[i], 0);
                }
            }

            

            while ((read = getline(&line, &len, fp)) != -1) {
                bool match = line_matches(line, regex, pattern_count);
                if (flagie->vflag == 1){
                    match = !match;
                }
                if (match) {
                    
                    output(first_file_index, argc, line_num, line, filename, flagie, &count_cflag);
                }
                line_num++;
            }
            if (flagie->cflag == 1){
                printf("%s:%d", filename, count_cflag);
            }
            for (int i = 0; i < pattern_count; i++) regfree(&regex[i]); //освобождение ресурсов
            fclose(fp);
        } else {
            fprintf(stderr, "grep: cannot open %s\n", filename);
        }

    }
}