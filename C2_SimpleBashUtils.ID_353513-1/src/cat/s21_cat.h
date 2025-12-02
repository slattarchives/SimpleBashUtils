#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    //cat
    bool bflag;//-b
    bool eflag;//-e
    bool nflag;//-n
    bool sflag;//-s
    bool tflag;//-t
    bool vflag;//-v
}Flags;

void flags_left(int *c, const Flags *flagie);
void flag_v(int *c);
void parse_flags(int argc, const char *argv[], Flags *flagie, int *flag_count, char *flag_chars, int *first_file_index);
void raise_flag(int flag_count, Flags *flagie, const char *flag_chars);
void process_file(int first_file_index, int argc, const char *argv[], const Flags *flagie);


#endif