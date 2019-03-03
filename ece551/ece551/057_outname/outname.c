#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * str = NULL;
  str = malloc(80 * sizeof(*str));
  strcpy(str, inputName);
  char * str1 = strncat(str, ".counts", 7);
  return str1;
}
