#include "s21_cat.h"

int main(int argc, char *argv[]) {
  char arg;
  int err = 0, index = 0;

  while (!err && (arg = getopt_long(argc, argv, ":benstvET", long_options,
                                    &index)) != -1) {
    switch (arg) {
      case 'b':
        options.b = 1;
        options.n = 0;
        break;
      case 'e':
        options.e = 1;
        options.v = 1;
        break;
      case 't':
        options.t = 1;
        options.v = 1;
        break;
      case 'n':
        options.n = !options.b;
        break;
      case 's':
        options.s = 1;
        break;
      case 'v':
        options.v = 1;
        break;
      case 'E':
        options.e = 1;
        break;
      case 'T':
        options.t = 1;
        break;
      default:
        err = 1;
        break;
    }
  }

  if (!err) {
    while (optind < argc) {
      if (print_file(argv[optind]))
        printf("s21_cat: --%s No such file or directory\n", argv[optind]);
      optind++;
    }
  } else
    printf("s21_cat: invalid options");
  return 0;
}

int print_file(char *file_name) {
  FILE *fp = fopen(file_name, "r");
  char sumbol = '\0';
  int result;
  int new_line_count = 1;

  !fp ? (result = 0) : (result = 1);

  while (result && feof(fp) == 0 && (sumbol = fgetc(fp)) != -1) {
    if (sumbol == '\n' && options.s && new_line_count >= 2) {
      while (sumbol == '\n') {
        sumbol = fgetc(fp);
      }
      new_line_count = 1;
    }

    if (new_line_count && (options.n || (sumbol != '\n' && options.b)))
      printf("%6d\t", ++count_line);

    if (options.e && sumbol == '\n') printf("$");

    if (options.t && sumbol == '\t')
      printf("^I");

    else {
      sumbol == '\n' ? new_line_count++ : (new_line_count = 0);
      if (options.v) {
        non_print(sumbol);
      } else if (sumbol != EOF) {
        printf("%c", sumbol);
      }
    }
  }
  if (result) {
    fclose(fp);
  }
  return !result;
}

void non_print(char c) {
  if (c < -96)
    printf("M-^%c", c + 192);
  else if (c < 0)
    printf("M-%c", c + 128);
  else if (c == 9 || c == 10)
    printf("%c", c);
  else if (c < 32)
    printf("^%c", c + 64);
  else if (c < 127)
    printf("%c", c);
  else
    printf("^?");
}
