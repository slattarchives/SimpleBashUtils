#include "s21_grep.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "usage: s21_cat [FLAGS] file...\n");
        return 1;
    }

    Flags flagie = {0};
    char flag_chars[256] = {0};
    int flag_count = 0;
    int first_file_index = 0;
    int pattern_index = 0;
    char **pattern = NULL;
    int pattern_count = 0;

    pattern = parse_flags(argc, argv, &flagie, &flag_count, flag_chars, &first_file_index, &pattern_index, &pattern_count);
    if (first_file_index == 0 || pattern_index == 0) {
        fprintf(stderr, "no input files\n");
        return 1;
    }
    
    

    process_file(first_file_index, argc, argv, &flagie, pattern, pattern_count);
    free(pattern);
    return 0;
}