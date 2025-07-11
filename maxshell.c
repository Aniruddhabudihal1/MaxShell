#include "header.h"

void stdin_input();
void batch_file_input();

int main(int argc, char *argv[]) {
  if (argc == 2) {
    batch_file_input();
    return EXIT_SUCCESS;
  } else if (argc == 1) {
    stdin_input();
    return EXIT_SUCCESS;
  } else if (strcmp(argv[1], "--help")) {
    printf("Just run the executable if you want a stdin based input\nbut if "
           "you want enter the commands through a batch file then run in the "
           "form : <execcutable> <batch file>\n");
    exit(0);
  } else {
    fprintf(stderr, "enter in the correct format\nexiting\n");
    return EXIT_FAILURE;
  }
}

void stdin_input() {
  char *buffer = (char *)malloc(1000);
  size_t buf_size = 1000;
  while (1) {
    printf("maxshell>");
    if (getline(&buffer, &buf_size, stdin) == -1) {
      fprintf(stderr, "something went wrong while reading the input\n");
    }
  }
}

void batch_file_input();
