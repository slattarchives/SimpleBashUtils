#ifndef S21_GREP_H
#define S21_GREP_H

// #define  _GNU_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  bool eflag;  //-e
  bool iflag;  //-i
  bool vflag;  //-v
  bool cflag;  //-c
  bool lflag;  //-l
  bool nflag;  //-n
  bool hflag;  //-h
  bool sflag;  //-s
  bool fflag;  //-f file
  bool oflag;  //-o
} Flags;

char **parse_flags(int argc, const char *argv[], int *flag_count,
                   char *flag_chars, int *first_file_index, int *pattern_count);
void raise_flag(int flag_count, Flags *flagie, const char *flag_chars);
void process_file(int first_file_index, int argc, const char *argv[],
                  const Flags *flagie, char **pattern, int pattern_count);
bool line_matches(const char *line, regex_t *regex, int pattern_count);
void output(int *printed_lflag, int first_file_index, int argc, int line_num,
            const char *line, const char *filename, const Flags *flagie,
            int *count_cflag);

#endif