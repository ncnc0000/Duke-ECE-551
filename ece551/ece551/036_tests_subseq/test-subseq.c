#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void run_check(int * array, size_t n, size_t expected_ans) {
  size_t p = maxSeq(array, n);
  if (p == expected_ans) {
    printf("correct!");
    return;
  }
  else {
    printf("Wrong!");
    exit(EXIT_FAILURE);
  }
}

int main() {
  int a[] = {1, 2, 3, 4, 5, 4, 3, 2, 1};
  int c[] = {1};
  int d[4] = {1, 2};
  int e[] = {-1, 0, -1, 0, -1, 0};
  int f[] = {-3, -2, -1};
  int g[] = {3, 2, 1};
  int h[] = {-1, -1};
  int i[] = {-2147483647, 65535};
  int j[] = {2147483647, 2147483647};
  int k[] = {-1, -5, -4, -3, -2, -1};
  run_check(NULL, 0, 0);
  run_check(a, 9, 5);
  run_check(a, 0, 0);
  run_check(c, 1, 1);
  run_check(d, 4, 2);
  run_check(e, 6, 2);
  run_check(f, 3, 3);
  run_check(g, 3, 1);
  run_check(h, 2, 1);
  run_check(i, 2, 2);
  run_check(j, 2, 1);
  run_check(k, 6, 5);
}
