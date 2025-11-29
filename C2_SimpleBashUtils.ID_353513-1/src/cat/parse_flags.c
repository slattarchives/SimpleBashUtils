#include "s21_cat.h"
void parse_flags(int argc, char *argv[], Flags *flagie, int *flag_count, char *flag_chars, int *first_file_index) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            // GNU flags
            if (strncmp(argv[i], "--number-nonblank", 17) == 0)
                flagie->bflag = true;
            else if (strncmp(argv[i], "--number", 8) == 0)  
                flagie->nflag = true;
            else if (strncmp(argv[i], "--squeeze-blank", 15) == 0)  
                flagie->sflag = true; 
            // normal flags
            else {
                for (int j = 1; argv[i][j] != '\0'; j++) {
                    flag_chars[(*flag_count)++] = argv[i][j];
                }
            }
        } else {
            *first_file_index = i;
            break;
        }
    }
    
    if (*first_file_index != 0)
        raise_flag(*flag_count, flagie, flag_chars);
}
