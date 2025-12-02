#include "s21_cat.h"

void flag_v(int *c) {
  if ((*c >= 0 && *c <= 31 && *c != 9 && *c != 10)) {
    *c += 64;
    printf("^");
  } else if (*c == 127) {
    *c -= 64;
    printf("^");
  } else if (*c > 126 && *c < 160) {
    *c = *c - 128 + 64;
    printf("M-^");
  }
}
