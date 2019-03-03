#include <stdio.h>
#include <stdlib.h>

unsigned powerhelper(unsigned x, unsigned y);

unsigned power(unsigned x, unsigned y) {
  return powerhelper(x, y);
}

unsigned powerhelper(unsigned x, unsigned y) {
  if (x == 0 && y == 0) {
    return 1;
  }
  else if (y == 0) {
    return 1;
  }
  else {
    return x * powerhelper(x, y - 1);
  }
}
