#include "s21_cat.h"

void flags_left(int *c, Flags *flagie) {
    if (flagie->eflag) {
        if (*c == '\n') {
            printf("$");
        }
        if (flagie->vflag) {
            flag_v(c);
        }
    }

    if (*c == '\t' && flagie->tflag) {
        printf("^I");
        *c = -1;
        return;
    }

    if (flagie->vflag) {
        flag_v(c);
    }
}