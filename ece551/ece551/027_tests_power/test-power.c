#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  unsigned p = power(x, y);
  if (p == expected_ans) {
    printf("correct!");
    exit(EXIT_SUCCESS);
  }
  else {
    printf("Wrong!");
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(2, 2, 4);
}
