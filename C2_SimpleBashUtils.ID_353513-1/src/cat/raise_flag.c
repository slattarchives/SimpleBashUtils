#include "s21_cat.h"
void raise_flag(int flag_count, Flags *flagie, const char *flag_chars) {
  for (int i = 0; i < flag_count; i++) {
    switch (flag_chars[i]) {
    case 'b':
      flagie->bflag = true;
      break;
    case 'e':
      flagie->eflag = true;
      flagie->vflag = true;
      break;
    case 'n':
      flagie->nflag = true;
      break;
    case 's':
      flagie->sflag = true;
      break;
    case 't':
      flagie->tflag = true;
      flagie->vflag = true;
      break;
    case 'v':
      flagie->vflag = true;
      break;
    case 'T':
      flagie->tflag = true;
      break;
    case 'E':
      flagie->eflag = true;
      break;
    default:
      fprintf(stderr, "unknown option: -%c\n", flag_chars[i]);
      break;
    }
  }

  if (flagie->bflag) {
    flagie->nflag = false;
  }
}