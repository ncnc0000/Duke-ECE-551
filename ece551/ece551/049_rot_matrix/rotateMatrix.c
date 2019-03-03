#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotate(FILE * f) {
  int i = 0;
  int count = 0;
  int t = 0;
  char c;
  char buf[1024];
  char matrix[10][10];
  char * p = NULL;
  char str[100];
  while (NULL != (fgets(str, 100, f))) {
    count++;
    p = strchr(str, '\n');
    t = p - str;
  }

  if (count != 10 || t != 10) {
    fprintf(stderr, "Wrong input");
    exit(EXIT_FAILURE);
  }
  rewind(f);
  while ((c = fgetc(f)) != EOF) {
    buf[i] = c;
    i++;
  }

  for (int m = 0; m < 10; m++) {
    for (int n = 0; n < 10; n++) {
      matrix[m][n] = buf[11 * (9 - n) + m];
      printf("%c", matrix[m][n]);
    }
    printf("\n");
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  rotate(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
