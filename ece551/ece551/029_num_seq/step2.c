// This file is for Step 2.
// You should do
//  Step 2 (A): write seq2
//  Step 2 (B): write main to test seq2
//  Step 2 (C): write sumSeq2
//  Step 2 (D): add test cases to main to test sumSeq2
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq2(int x) {
  int ans = -1;
  if (x > -1) {
    for (int i = 0; i <= x; i++) {
      ans += 2 * i + 2;
    }
  }
  else if (x < -2) {
    for (int j = -3; j >= x; j--) {
      ans += 2 * (-j - 2);
    }
  }
  else {
    ans = -1;
  }
  return ans;
}

int sumSeq2(int low, int high) {
  int sum = 0;
  if (low < high) {
    for (int i = low; i < high; i++) {
      sum += seq2(i);
    }
  }
  else if (low == high) {
    sum = seq2(low);
  }
  else {
    return 0;
  }
  return sum;
}

int main() {
  printf("seq2(%d) = %d\n", 0, seq2(0));
  printf("seq2(%d) = %d\n", 1, seq2(1));
  printf("seq2(%d) = %d\n", 2, seq2(2));
  printf("seq2(%d) = %d\n", 3, seq2(3));
  printf("seq2(%d) = %d\n", 4, seq2(4));
  printf("seq2(%d) = %d\n", 5, seq2(5));
  printf("seq2(%d) = %d\n", 6, seq2(6));
  printf("seq2(%d) = %d\n", 7, seq2(7));
  printf("seq2(%d) = %d\n", 8, seq2(8));
  printf("seq2(%d) = %d\n", 9, seq2(9));
  printf("seq2(%d) = %d\n", 11, seq2(11));
  printf("seq2(%d) = %d\n", 12, seq2(12));
  printf("seq2(%d) = %d\n", 13, seq2(13));
  printf("seq2(%d) = %d\n", 14, seq2(14));
  printf("seq2(%d) = %d\n", 10, seq2(10));
  printf("seq2(%d) = %d\n", -5, seq2(-5));
  printf("seq2(%d) = %d\n", -1, seq2(-1));
  printf("seq2(%d) = %d\n", -2, seq2(-2));
  printf("seq2(%d) = %d\n", -3, seq2(-3));
  printf("seq2(%d) = %d\n", -4, seq2(-4));
  printf("seq2(%d) = %d\n", -6, seq2(-6));
  printf("seq2(%d) = %d\n", -7, seq2(-7));
  printf("seq2(%d) = %d\n", -8, seq2(-8));
  printf("seq2(%d) = %d\n", -9, seq2(-9));
  printf("sumSeq2(%d, %d) = %d\n", 0, 2, sumSeq2(0, 2));
  printf("sumSeq2(%d, %d) = %d\n", 3, 6, sumSeq2(3, 6));
  printf("sumSeq2(%d, %d) = %d\n", 9, 7, sumSeq2(9, 7));
  printf("sumSeq2(%d, %d) = %d\n", -5, -3, sumSeq2(-5, -3));
  printf("sumSeq2(%d, %d) = %d\n", -3, -5, sumSeq2(-3, -5));
  printf("sumSeq2(%d, %d) = %d\n", 0, 0, sumSeq2(0, 0));
  return 0;
}
