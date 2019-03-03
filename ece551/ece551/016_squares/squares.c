int max(int a, int b) {
  if (a > b) {
    return a;
  }
  else
    return b;
}

int is_between(int x, int x_offset, int size2) {
  if ((x >= x_offset) && (x < (x_offset + size2)))
    return 1;
  else
    return 0;
}

int is_equal(int y, int y_offset, int size2) {
  if ((y == y_offset) || (y == (y_offset + size2 - 1)))
    return 1;
  else
    return 0;
}

int is_equal2(int x, int size1) {
  if ((x == 0) || (x == (size1 - 1)))
    return 1;
  else
    return 0;
}

int is_less(int x, int size1) {
  if (x < size1)
    return 1;
  else
    return 0;
}

void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, x_offset + size2);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, y_offset + size2);
  //count from 0 to h. Call the number you count with y

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      int m = is_between(x, x_offset, size2);
      int n = is_equal(y, y_offset, size2);
      int s = is_between(y, y_offset, size2);
      int t = is_equal(x, x_offset, size2);
      int c = is_less(x, size1);
      int d = is_less(y, size1);
      int e = is_equal2(y, size1);
      int f = is_equal2(x, size1);
      if ((m && n) || (s && t))
        printf("*");
      else if ((c && e) || (d && f))
        printf("#");
      else
        printf(" ");
    }
    printf("\n");
  }
  //count from 0 to w. Call the number you count with x

  //check if  EITHER
  //    ((x is between x_offset  and x_offset +size2) AND
  //     y is equal to either y_offset OR y_offset + size2 - 1 )
  //  OR
  //    ((y is between y_offset and y_offset + size2) AND
  //     x is equal to either x_offset OR x_offset + size2 -1)
  // if so, print a *

  //if not,
  // check if EITHER
  //    x is less than size1 AND (y is either 0 or size1-1)
  // OR
  //    y is less than size1 AND (x is either 0 or size1-1)
  //if so, print a #

  //else print a space
  //when you finish counting x from 0 to w,
  //print a newline
}
