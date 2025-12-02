#include "s21_grep.h"
void raise_flag(int flag_count, Flags *flagie, const char *flag_chars) {
  for (int i = 0; i < flag_count; i++) {
    switch (flag_chars[i]) {
      case 'e':
        flagie->eflag = true;
        break;
      case 'i':
        flagie->iflag = true;
        break;
      case 'v':
        flagie->vflag = true;
        break;
      case 'c':
        flagie->cflag = true;
        break;
      case 'l':
        flagie->lflag = true;
        break;
      case 'n':
        flagie->nflag = true;
        break;
      case 'h':
        flagie->hflag = true;
        break;
      case 's':
        flagie->sflag = true;
        break;
      case 'f':
        flagie->fflag = true;
        break;
      case 'o':
        flagie->oflag = true;
        break;
      default:
        fprintf(stderr, "unknown option: -%c\n", flag_chars[i]);
        break;
    }
  }
}