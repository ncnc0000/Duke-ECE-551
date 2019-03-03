// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>

int seq3(int x, int y) {
  int y_axis = 2 * y;
  int ans = 0;
  if (x == 0) {
    ans = y_axis;
  }
  else {
    ans = y_axis - (x * (3 - y));
  }
  return ans;
}

int countEvenInSeq3Range(int xLow, int xHi, int yLow, int yHi) {
  int count = 0;
  if ((xLow < xHi) && (yLow < yHi)) {
    for (int i = yLow; i < yHi; i++) {
      for (int j = xLow; j < xHi; j++) {
        if (seq3(j, i) % 2 == 0) {
          count++;
        }
      }
    }
  }
  else if ((xLow == xHi) && (yLow < yHi)) {
    for (int i = yLow; i < yHi; i++) {
      if (seq3(xLow, i) % 2 == 0) {
        count++;
      }
    }
  }
  else if ((yLow == yHi) && (xLow < xHi)) {
    for (int i = xLow; i < xHi; i++) {
      if (seq3(i, yLow) % 2 == 0) {
        count++;
      }
    }
  }
  else if ((yLow == yHi) && (xLow == xHi)) {
    if (seq3(xLow, yLow) % 2 == 0) {
      count++;
    }
  }
  else {
    count = 0;
  }

  return count;
}

int main() {
  for (int i = -5; i < 6; i++) {
    for (int j = -5; j < 6; j++) {
      printf("seq3(%d, %d) = %d\n", j, i, seq3(j, i));
    }
    printf("\n");
  }

  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 2, 0, 3, countEvenInSeq3Range(0, 2, 0, 3));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 0, countEvenInSeq3Range(0, 0, 0, 0));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 3, countEvenInSeq3Range(0, 0, 0, 3));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 3, countEvenInSeq3Range(0, 3, 0, 0));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 3, countEvenInSeq3Range(1, 0, 0, 3));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 3, countEvenInSeq3Range(1, 0, 4, 3));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 3, countEvenInSeq3Range(0, 0, 4, 3));
  printf(
      "countEvenInSeq3Range(%d, %d, %d, %d) = %d\n", 0, 0, 0, 3, countEvenInSeq3Range(4, 0, 0, 0));
  return 0;
}
