#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void openfile(char * argv) {
  char ** str = NULL;
  char * line = NULL;
  size_t i = 0, sz = 0;
  FILE * f = fopen(argv, "r");
  if (f == NULL) {
    fprintf(stderr, "Can't open file!");
    exit(EXIT_FAILURE);
  }
  while (getline(&line, &sz, f) >= 0) {
    str = realloc(str, (i + 1) * sizeof(*str));
    str[i] = line;
    line = NULL;
    i++;
  }
  free(line);
  sortData(str, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", str[j]);
    free(str[j]);
  }
  free(str);
  if (fclose(f) != 0) {
    fprintf(stderr, "Failed close input file!");
    exit(EXIT_FAILURE);
  }
}
int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    char ** str = NULL;
    char * line = NULL;
    size_t i = 0, sz = 0;
    while (getline(&line, &sz, stdin) >= 0) {
      str = realloc(str, (i + 1) * sizeof(*str));
      str[i] = line;
      line = NULL;
      i++;
    }
    free(line);
    sortData(str, i);
    for (size_t j = 0; j < i; j++) {
      printf("%s", str[j]);
      free(str[j]);
    }
    free(str);
  }
  else if (argc > 1) {
    for (int n = 1; n < argc; n++) {
      openfile(argv[n]);
    }
  }
  else {
    fprintf(stderr, "Invaild input!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
