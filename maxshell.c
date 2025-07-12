#include "header.h"
#include <stdatomic.h>
#include <stdio.h>

void stdin_input();
void batch_file_input();

int main(int argc, char *argv[]) {
  if (argc == 1) {
    stdin_input();
  } else if (strcmp(argv[1], "batch") == 0) {
    batch_file_input();
  } else if (strcmp(argv[1], "help") == 0) {
    fprintf(stderr,
            "for stdin input just run the executable\nFor sending in a batch "
            "file, type in the name of the batch file as the second input\n");
    return 1;
  }
  return 0;
}

void stdin_input() { printf("Stdin input\n"); }

void batch_file_input() { printf("batch file input\n"); }
