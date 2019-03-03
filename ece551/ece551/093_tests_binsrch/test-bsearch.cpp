
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high);

class SinFunc : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinearFunc : public Function<int, int>
{
 public:
  virtual int invoke(int arg) { return arg; }
};
class CountedIntFn : public Function<int, int>
{
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n),
      f(fn),
      mesg(m) {}
  // invoke n times
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

void check(Function<int, int> * f, int low, int high, int expected_ans, const char * mesg) {
  int max = high > low ? log(high - low) / log(2) + 1 : 1;
  CountedIntFn * f1 = new CountedIntFn(max, f, mesg);
  int ans = binarySearchForZero(f1, low, high);
  if (ans != expected_ans) {
    fprintf(stderr, "%s", mesg);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  SinFunc * sf = new SinFunc();
  LinearFunc * lf = new LinearFunc();
  int a = -1 / 2;
  printf("%d", a);
  check(sf, 0, 150000, 52359, "SinCase");
  check(lf, -1, 1, 0, "1 test case. -1,1,0\n");
  check(lf, 0, 8, 0, "2 test case. 0, 8, 0\n");
  check(lf, 3, 8, 3, "3 test case. 3, 8, 3\n");
  check(lf, 3, 3, 3, "4 test case. 3, 3, 3\n");
  check(lf, 2, 3, 2, "5 test case. 2, 3, 2\n");
  check(lf, 3, 2, 3, "6 test case. 3, 2, 3\n");
  check(lf, 0, 0, 0, "7 test case. 0, 0, 0\n");
  check(lf, -4, -3, -4, "8 test case. -4,-3,-4\n");
  check(lf, -99999999, -1, -2, "9 test case. -99999999, -1, -2\n");
  check(lf, -1, 10000000, 0, "10 test case. -1,10000000, 0\n");
  check(lf, 1, 10000000, 1, "11 test case. 1, 10000000, 1\n");
  check(lf, -99999999, 10000000, 0, "12 test case. -99999999, 10000000, 0\n");
  check(lf, -1, -1, -1, "13 test case. -1, -1, -1\n");
  check(lf, -2, 0, -1, "14 test case. -2, 0, -1\n");
  check(lf, 100000000, 10000000, 100000000, "15 test case. -1, -1, -1\n");
  //check(lf, -3, -4, -5, "8 test case. -3,-4,-5\n");
  return EXIT_SUCCESS;
}
