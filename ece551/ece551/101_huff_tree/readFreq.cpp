#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    perror("can't open the file!");
    exit(EXIT_FAILURE);
  }
  uint64_t * p = new uint64_t[257];
  for (int i = 0; i < 257; i++) {
    p[i] = 0;
  }
  int c = 0;
  while ((c = fgetc(f)) != EOF) {
    p[int(c)]++;
  }
  p[256] = 1;
  fclose(f);
  return p;
}
