#include <cstdio>
#include <cstdlib>

#include "function.h"
int binarySearchForZero_helper(Function<int, int> * f, int low, int high);

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if (low == high) {
    return low;
  }
  if (f->invoke(low) >= 0) {
    return low;
  }
  if (f->invoke(high - 1) <= 0) {
    return high - 1;
  }
  return binarySearchForZero_helper(f, low, high - 1);
}

int binarySearchForZero_helper(Function<int, int> * f, int low, int high) {
  int mid;
  int ans;
  while (low <= high) {
    mid = (low + high) / 2;
    ans = f->invoke(mid);
    if (ans == 0) {
      return mid;
    }
    else if (ans > 0) {
      high = mid - 1;
    }
    else {
      low = mid + 1;
    }
  }
  if (high < mid) {
    return mid - 1;
  }
  return mid;
}
