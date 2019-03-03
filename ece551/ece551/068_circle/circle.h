#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "point.h"
class Circle
{
 private:
  const double radius;
  Point center;

 public:
  Circle(Point p, double n);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};

#endif
