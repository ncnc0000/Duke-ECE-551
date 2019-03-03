#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  int count = 0;
  int count_end = 0;
  int max_count = 0;
  if (n == 0) {
    return 0;
  }
  else if (n == 1) {
    return 1;
  }
  else {
    for (int i = 0; i < n - 1; i++) {
      if ((*(array + (i + 1))) > (*(array + i))) {
        count++;
      }
      else {
        if (count > max_count) {
          max_count = count;
        }
        count = 0;
      }
    }
    count_end = count;
    if (count_end > max_count) {
      max_count = count_end;
    }
  }
  return max_count + 1;
}
