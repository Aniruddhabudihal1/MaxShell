#include "header.h"
#include <stdio.h>

// main functions
void stdin_input();
void batch_file_input();

// functionality for the shell
void ls(const char *buf);
void echo(char *, char *);

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

void stdin_input() {
  char *input_buffer = (char *)malloc(1000);
  int len_bait;
  char *bait = (char *)malloc(150);
  int cd_return;
  char test[100];

  while (1) {
    char *bait = (char *)malloc(150);
    printf("MaxShell> ");
    fgets(input_buffer, 1000, stdin);

    if (strncmp((const char *)input_buffer, "ls", 2) == 0) {
      ls(input_buffer);
    } else if (strncmp(input_buffer, "qui", 3) == 0 ||
               strncmp(input_buffer, "exit", 4) == 0) {
      printf("Simply lovely !\n");
      exit(0);
    } else if (strncmp(input_buffer, "cd", 2) == 0) {
      bait = strtok(input_buffer, " ");
      bait = strtok(NULL, "\0");
      for (int i = 0; i <= strlen(bait); i++) {
        if (bait[i] == '\n') {
          strcpy(&bait[i], "");
        }
      }
      if (getcwd(test, 100) == NULL) {
        fprintf(stderr,
                "An error occured while getting the present working directory "
                ": %s\n",
                strerror(errno));
      }
      strcat(test, "/");
      strcat(bait, "/");
      strcat(test, bait);

      if (chdir(test) != 0) {
        fprintf(stderr, "something went wrong while changing directory : %s\n",
                strerror(errno));
      }
      strcpy(bait, "");
    } else if (strncmp(input_buffer, "clear", 5) == 0) {
      system("clear");
    } else if (strncmp(input_buffer, "echo", 4) == 0) {
      echo(bait, input_buffer);
    } else {
      printf("MaxShell does not recognise : %sI gave my reasons !!\n",
             input_buffer);
    }

    strcpy(input_buffer, "");
    free(bait);
  }
  free(input_buffer);
}

void batch_file_input() { printf("batch file input\n"); }

void ls(const char *buf) {
  // need to add more functionality where it can call ls for any directory
  pid_t forking_status = fork();
  pid_t exec_status;
  if (forking_status == -1) {
    fprintf(stderr, "something went wrong while performing ls\n");
    exit(1);
  } else if (forking_status == 0) {
    char *arguments = strdup("/usr/bin/ls");
    char *arr[] = {arguments, NULL};
    exec_status = execv(arr[0], arr);
    if (exec_status == -1) {
      fprintf(stderr, "something went while running ls : %s\n",
              strerror(errno));
      exit(1);
    }
  } else {
    int signal = wait(NULL);
  }
}

void echo(char *bait, char *input_buffer) {
  bait = strtok(input_buffer, " ");
  for (bait = strtok(NULL, " "); bait != NULL; bait = strtok(NULL, " ")) {
    printf("%s ", bait);
  }
  // strcpy(bait, "");
}
