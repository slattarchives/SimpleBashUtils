#include "s21_grep.h"
char **parse_flags(int argc, const char *argv[], int *flag_count,
                   char *flag_chars, int *first_file_index,
                   int *pattern_count) {
  int e_exist = 0;
  int pattern_found = 0;
  char **patterns = NULL;
  for (int i = 1; i < argc; i++) {
    if (e_exist) {
      char **tmp = realloc(patterns, ((*pattern_count) + 1) * sizeof(char *));
      if (tmp == NULL) {
        for (int k = 0; k < *pattern_count; k++) {
          free(patterns[k]);
        }
        free(patterns);
        return NULL;
      }
      patterns = tmp;
      patterns[*pattern_count] = malloc(strlen(argv[i]) + 1);
      if (patterns[*pattern_count] == NULL) {
        for (int k = 0; k <= *pattern_count; k++) {
          free(patterns[k]);
        }
        free(patterns);
        return NULL;
      }
      strcpy(patterns[*pattern_count], argv[i]);
      (*pattern_count)++;

      pattern_found = 1;
      e_exist = 0;
    } else if (argv[i][0] == '-' && argv[i][1] == 'e') {
      e_exist = 1;
    } else if (argv[i][0] == '-' && argv[i][1] != 'e') {
      for (int j = 1; argv[i][j] != '\0'; j++) {
        flag_chars[(*flag_count)++] = argv[i][j];
      }
    } else {
      if (!pattern_found) {
        char **tmp = realloc(patterns, ((*pattern_count) + 1) * sizeof(char *));
        if (tmp == NULL) {
          for (int k = 0; k < *pattern_count; k++) {
            free(patterns[k]);
          }
          free(patterns);
          return NULL;
        }
        patterns = tmp;
        patterns[*pattern_count] = malloc(strlen(argv[i]) + 1);
        if (patterns[*pattern_count] == NULL) {
          for (int k = 0; k <= *pattern_count; k++) {
            free(patterns[k]);
          }
          free(patterns);
          return NULL;
        }
        strcpy(patterns[*pattern_count], argv[i]);
        (*pattern_count)++;
        pattern_found = 1;
      } else if (*first_file_index == -1) {
        *first_file_index = i;
      }
    }
    // printf("Аргумент %d: '%s'\n", i, argv[i]);
    // printf("pattern_found = %d, first_file_index = %d\n", pattern_found,
    // *first_file_index);
  }
  return patterns;
}
