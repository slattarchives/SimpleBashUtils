#include "s21_grep.h"

bool line_matches(const char *line, regex_t *regex, int pattern_count) {
    bool flag;
    for (int k = 0; k < pattern_count; k++){
        if (regexec(&regex[k], line, 0, NULL, 0) == 0) {
            flag = true;
        } else
            flag = false;
    }

    return flag;
}