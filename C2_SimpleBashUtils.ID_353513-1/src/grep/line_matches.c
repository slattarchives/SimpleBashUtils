#include "s21_grep.h"

bool line_matches(const char *line, regex_t *regex, int pattern_count) {
  bool flag = false;
  int i = 0;
  while (i < pattern_count && !flag) {
    if (regexec(&regex[i], line, 0, NULL, 0) == 0) {
      flag = true;
    }
    i++;
  }

  return flag;
}