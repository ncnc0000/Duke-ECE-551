#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int dencrypt(FILE * f) {
  int fre[26] = {0};
  int max = 0;
  int c = 0;
  int num = 0;
  int flag = 0;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      fre[tolower(c) - 'a']++;
    }
  }
  for (int i = 0; i < 26; i++) {
    if (fre[i] == max) {
      flag = 1;
    }
    if (fre[i] > max) {
      max = fre[i];
      num = i;
      flag = 0;
    }
  }
  if (flag == 1 || max == 1) {
    fprintf(stderr, "Can't decide it!\n");
    exit(EXIT_FAILURE);
  }
  return (num - 4 + 26) % 26;
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
  int key = dencrypt(f);
  printf("%d\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
