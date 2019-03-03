#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * count_array = malloc(sizeof(*count_array));
  count_array->num = 0;
  count_array->array = NULL;
  count_array->NULL_counts = 0;
  count_array->_NULL = NULL;
  return count_array;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  char * str = NULL;
  int flag = 0;
  if (name == NULL) {
    c->NULL_counts++;
    c->_NULL = "<UNKNOWN>";
  }

  else {
    if (c->num == 0) {
      c->array = realloc(c->array, sizeof(*c->array));
      str = strdup(name);
      c->array[0].key = str;
      c->array[0].counts = 1;
      str = NULL;
      c->num = 1;
    }
    else {
      for (size_t i = 0; i < c->num; i++) {
        if (strcmp(c->array[i].key, name) == 0) {
          c->array[i].counts++;
          flag = 1;
        }
      }
      if (flag == 0) {
        str = strdup(name);
        c->array = realloc(c->array, (c->num + 1) * sizeof(*c->array));
        c->array[c->num].key = str;
        c->array[c->num].counts = 1;
        c->num++;
        str = NULL;
      }
    }
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->num; i++) {
    fprintf(outFile, "%s : %d\n", c->array[i].key, c->array[i].counts);
  }
  if (c->NULL_counts != 0) {
    fprintf(outFile, "%s : %d\n", c->_NULL, c->NULL_counts);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (size_t i = 0; i < c->num; i++) {
    free(c->array[i].key);
  }
  free(c->array);
  free(c);
}
