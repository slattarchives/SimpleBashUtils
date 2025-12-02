#include "s21_grep.h"

void output(int *printed_lflag, int first_file_index, int argc, int line_num,
            const char *line, const char *filename, const Flags *flagie,
            int *count_cflag) {
  if (flagie->cflag == 1)
    (*count_cflag)++;
  else if (flagie->lflag == 1) {
    if ((*printed_lflag) == 0) {
      printf("%s\n", filename);
      (*printed_lflag) = 1;
    }
  } else {
    if (first_file_index != argc - 1) {
      printf("%s:", filename);
    }
    if (flagie->nflag == 1) {
      printf("%d:", line_num);
    }
    printf("%s", line);

    // завершаем строку \n
    if (strlen(line) == 0 || line[strlen(line) - 1] != '\n') {
      printf("\n");
    }
  }
}