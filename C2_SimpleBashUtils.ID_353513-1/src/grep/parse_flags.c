#include "s21_grep.h"
char** parse_flags(int argc, char *argv[], Flags *flagie, int *flag_count, char *flag_chars, int *first_file_index, int *pattern_index, int *pattern_count) {
    int e_exist = 0;
    int pattern_found = 0;
    char **patterns = NULL;
    for (int i = 1; i < argc; i++) {
        if (e_exist){
            patterns = realloc(patterns, ((*pattern_count) + 1) * sizeof(char*));
            patterns[*pattern_count] = malloc(strlen(argv[i]) + 1);
            strcpy(patterns[*pattern_count], argv[i]);
            (*pattern_count)++;

            pattern_found = 1;
            e_exist = 0;
        }
        else if (argv[i][0] == '-' && argv[i][1] == 'e') {
            e_exist = 1;
        } 
        else if (argv[i][0] == '-' && argv[i][1] != 'e'){
            for (int j = 1; argv[i][j] != '\0'; j++) {
                flag_chars[(*flag_count)++] = argv[i][j];
            }
        } 
        else {
            if (!pattern_found){
                patterns = realloc(patterns, ((*pattern_count) + 1) * sizeof(char*));
                patterns[*pattern_count] = malloc(strlen(argv[i]) + 1);
                strcpy(patterns[*pattern_count], argv[i]);
                (*pattern_count)++;
                pattern_found = 1;
            } else {
                if (*first_file_index == -1)
                    *first_file_index = i;
            }
        }
        //printf("Аргумент %d: '%s'\n", i, argv[i]);
        //printf("pattern_found = %d, first_file_index = %d\n", pattern_found, *first_file_index);
    }
    //use just because gcc swearing on it 
    if (*first_file_index != 0 && *pattern_index != 0)
        printf("%d", flagie->eflag);
    return patterns;
}
