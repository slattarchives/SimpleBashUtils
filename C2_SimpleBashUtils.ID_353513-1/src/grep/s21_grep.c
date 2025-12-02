#include "s21_grep.h"

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: s21_grep [FLAGS] file...\n");
    return 1;
  }
  int exit_code = 0;

  Flags flagie = {0};
  char flag_chars[256] = {0};
  int flag_count = 0;
  int first_file_index = -1;
  char **pattern = NULL;
  int pattern_count = 0;

  pattern = parse_flags(argc, argv, &flag_count, flag_chars, &first_file_index,
                        &pattern_count);
  if (pattern == NULL) {
    fprintf(stderr, "s21_grep: error in arguments or memory allocation\n");
    exit_code = 1;
  } else if (first_file_index == -1) {
    fprintf(stderr, "no input files\n");
    exit_code = 1;
  }
  // шаблон не задан вообще
  else if (pattern_count == 0) {
    fprintf(stderr, "no pattern specified\n");
    exit_code = 1;
  } else {
    raise_flag(flag_count, &flagie, flag_chars);
    process_file(first_file_index, argc, argv, &flagie, pattern, pattern_count);
  }
  if (pattern != NULL) {
    int i = 0;
    while (i < pattern_count) {
      free(pattern[i]);
      i++;
    }
    free(pattern);
  }
  return exit_code;
}
