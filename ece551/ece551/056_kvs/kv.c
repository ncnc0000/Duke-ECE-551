#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("can't open this file");
    exit(EXIT_FAILURE);
  }
  kvarray_t * array = malloc(sizeof(*array));
  char * line = NULL;
  char * str = NULL;

  size_t i = 0, sz = 0;
  array->pair = NULL;
  while (getline(&line, &sz, f) >= 0) {
    array->pair = realloc(array->pair, (i + 1) * sizeof(*array->pair));
    str = strchr(line, '=');
    array->pair[i].key = strndup(line, str - line);
    array->pair[i].value = strdup(str + 1);
    char * str1 = strchr(array->pair[i].value, '\n');
    array->pair[i].value[str1 - (array->pair[i].value)] = '\0';
    i++;
  }
  free(line);
  array->num = i;
  if (fclose(f) != 0) {
    perror("Fail to close the file!");
    exit(EXIT_FAILURE);
  }
  return array;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->num; i++) {
    free(pairs->pair[i].key);
    free(pairs->pair[i].value);
  }
  free(pairs->pair);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (size_t i = 0; i < pairs->num; i++) {
    printf("key = '%s' value = '%s' \n", pairs->pair[i].key, pairs->pair[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (size_t i = 0; i < pairs->num; i++) {
    if (strcmp(pairs->pair[i].key, key) == 0) {
      return pairs->pair[i].value;
    }
  }
  return NULL;
}
