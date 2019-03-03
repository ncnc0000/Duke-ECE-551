#include "circle.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "point.h"

Circle::Circle(Point p, double n) : radius(n), center(p) {}

void Circle::move(double dx, double dy) {
  //this->move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double d = center.distanceFrom(otherCircle.center);
  if (d >= (radius + otherCircle.radius)) {
    return 0;
  }
  if (d <= (radius - otherCircle.radius)) {
    return otherCircle.radius * otherCircle.radius * M_PI;
  }
  if (d <= (otherCircle.radius - radius)) {
    return radius * radius * M_PI;
  }
  double d1 = 2 * acos((radius * radius + d * d - otherCircle.radius * otherCircle.radius) /
                       (2 * radius * d));
  double d2 = 2 * acos((otherCircle.radius * otherCircle.radius + d * d - radius * radius) /
                       (2 * otherCircle.radius * d));
  double area1 = radius * radius * d1 / 2 - radius * radius * sin(d1) / 2;
  double area2 = otherCircle.radius * otherCircle.radius * d2 / 2 -
                 otherCircle.radius * otherCircle.radius * sin(d2) / 2;
  double area = area1 + area2;
  return area;
}
