#pragma once

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct flags {
  int b;  // b
  int n;  // n
  int e;  // E
  int t;  // T
  int s;  // s
  int v;  // v
} flags;

static struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                       {"number", no_argument, 0, 'n'},
                                       {"squeeze-blank", no_argument, 0, 's'},
                                       {0, 0, 0, 0}};

int print_file(char *file_name);
void non_print(char c);

int count_line = 0;
flags options = {0, 0, 0, 0, 0, 0};
