#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * count_array = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("can't open input file!\n");
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t sz = 0;
  int flag = 0;
  while (getline(&line, &sz, f) >= 0) {
    flag = 0;
    for (size_t n = 0; n < strlen(line); n++) {
      if (line[n] == '\n') {
        line[n] = '\0';
      }
    }
    for (size_t i = 0; i < kvPairs->num; i++) {
      if (strcmp(line, kvPairs->pair[i].key) == 0) {
        addCount(count_array, kvPairs->pair[i].value);
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      addCount(count_array, NULL);
    }
  }
  free(line);
  if (fclose(f) != 0) {
    perror("fail to close inputfile!\n");
    exit(EXIT_FAILURE);
  }
  return count_array;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 2) {
    perror("Invaild input argument!\n");
    return EXIT_FAILURE;
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * pairs = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * count = countFile(argv[i], pairs);
    //compute the output file name from argv[i] (call this outName)
    char * str = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(str, "w");
    if (f == NULL) {
      perror("can't open the outputfile!\n");
      return EXIT_FAILURE;
    }
    //print the counts from c into the FILE f
    //printf("%d\n", count->NULL_counts);
    printCounts(count, f);
    //close f
    if (fclose(f) != 0) {
      perror("fail to close outputfile!\n");
      return EXIT_FAILURE;
    }
    //free the memory for outName and c
    free(str);
    freeCounts(count);
  }

  //free the memory for kv
  freeKVs(pairs);
  return EXIT_SUCCESS;
}
