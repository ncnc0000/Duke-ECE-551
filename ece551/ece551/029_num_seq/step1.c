// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq1(int x) {
  int ans = 4 * x - 3;
  return ans;
}

void printSeq1Range(int low, int high) {
  int i;
  if (low < high) {
    for (i = low; i < (high - 1); i++) {
      printf("%d, ", seq1(i));
    }
    if (i == (high - 1)) {
      printf("%d\n", seq1(i));
    }
  }
  else {
    printf("\n");
  }
}

int main() {
  printf("seq1(%d) = %d\n", 1, seq1(1));
  printf("seq1(%d) = %d\n", 2, seq1(2));
  printf("seq1(%d) = %d\n", 11, seq1(11));
  printf("seq1(%d) = %d\n", -1, seq1(-1));
  printf("printSeq1Range(%d, %d)\n", -2, 6);
  printSeq1Range(-2, 6);
  printf("printSeq1Range(%d, %d)\n", 7, 3);
  printSeq1Range(7, 3);
  printf("printSeq1Range(%d, %d)\n", 0, 0);
  printSeq1Range(0, 0);
  printf("printSeq1Range(%d, %d)\n", 0, 4);
  printSeq1Range(0, 4);
  return 0;
}
