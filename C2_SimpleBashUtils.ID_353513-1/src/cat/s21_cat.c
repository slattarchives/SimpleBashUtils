#include "s21_cat.h"

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: s21_cat [FLAGS] file...\n");
    return 1;
  }

  Flags flagie = {0};
  char flag_chars[256] = {0};
  int flag_count = 0;
  int first_file_index = 0;

  parse_flags(argc, argv, &flagie, &flag_count, flag_chars, &first_file_index);

  if (first_file_index == 0) {
    fprintf(stderr, "no input files\n");
    return 1;
  }

  process_file(first_file_index, argc, argv, &flagie);

  return 0;
}
