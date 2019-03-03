#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv) {
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("THERE IS FAULT IN FILE\n");
  }
  char * line = NULL;
  size_t sz = 0;
  int n = 0;
  char ** str = NULL;
  while (getline(&line, &sz, f) >= 0) {
    if (n == 0) {
      str = realloc(str, sizeof(*str));
      str[0] = line;
      line = NULL;
      n = 1;
    }
    else {
      for (int i = 0; i < n; i++) {
        if (strcmp(str[i], line) != 0) {
          str = realloc(str, (n + 1) * sizeof(*str));
          str[n] = line;
          line = NULL;
        }
      }
      n++;
    }
  }
  free(line);
  for (int j = 0; j < n; j++) {
    printf("%s", str[j]);
    free(str[j]);
  }
  free(str);
  return 0;
}
