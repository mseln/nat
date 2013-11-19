// Problem 12173 on UVa (accepted there)

#include <cstdio>
#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

typedef unsigned int nat;

template <class T>
class Point {
public:
  T x, y;

  Point() : x(), y() {}
  Point(T x, T y) : x(x), y(y) {}

  Point<T> operator -(const Point &o) const { return Point<T>(x - o.x, y - o.y); }
  Point<T> operator /(T o) const { return Point<T>(x / o, y / o); }
  T operator |(const Point &o) const {
    return x * o.x + y * o.y;
  }
};


template <class T>
class Vector {
public:
  T x, y, z;

  Vector() : x(), y(), z() {}
  Vector(const Point<T> &pt, T z) : x(pt.x), y(pt.y), z(z) {}
  Vector(T x, T y, T z) : x(x), y(y), z(z) {}

  Vector<T> operator -(const Vector &o) const { return Vector<T>(x - o.x, y - o.y, z - o.z); }
  Vector<T> operator /(T o) const { return Vector<T>(x / o, y / o, z / o); }
  T operator |(const Vector &o) const { return x * o.x + y * o.y + z * o.z; }
  Vector<T> operator %(const Vector &o) const {
    return Vector<T>(y*o.z - z*o.y, z*o.x - x*o.z, x*o.y - y*o.x);
  }
};

// distance between two points or vectors.
template <class T>
T dist(const Point<T> &a, const Point<T> &b) {
  Point<T> d = a - b;
  return sqrt(d | d);
}

// Normalize a line
template <class T>
void normLine(Vector<T> &v) {
  T l = sqrt(v.x * v.x + v.y * v.y);
  v = v / l;
}

// Normalize a point
template <class T>
void normPoint(Vector<T> &v) {
  v = v / v.z;
}

template <class T>
T dist(const Point<T> &point, const Point<T> &lineFrom, const Point<T> &lineTo) {
  // Outside first endpoint?
  if (((point - lineFrom) | (lineTo - lineFrom)) < 0) {
    return dist(point, lineFrom);
  }

  // Outside second endpoint?
  if (((point - lineTo) | (lineFrom - lineTo)) < 0) {
    return dist(point, lineTo);
  }

  // Ok, in the middle of the line!

  // Create the homogenous representation of the line...
  Vector<T> line = Vector<T>(lineFrom, 1) % Vector<T>(lineTo, 1);

  // The signed distance is then the dot product of the line
  // and the point.
  normLine(line);
  T distance = Vector<T>(point, 1) | line;

  // Don't return negative distances...
  return abs(distance);
}

vector<Point<double> > readPoints() {
  nat size = 0;
  scanf("%d", &size);

  vector<Point<double> > result;

  for (nat i = 0; i < size; i++) {
    double x, y;
    scanf("%lf %lf", &x, &y);
    result.push_back(Point<double>(x, y));
  }

  return result;
}

void solve() {
  vector<Point<double> > inner = readPoints();
  vector<Point<double> > outer = readPoints();

  double longest = 1e100;

  for (nat i = 0; i < inner.size(); i++) {
    nat iNext = (i + 1) % inner.size();
    for (nat j = 0; j < outer.size(); j++) {
      nat jNext = (j + 1) % outer.size();

      longest = min(longest, dist(outer[j], inner[i], inner[iNext]));
      longest = min(longest, dist(inner[i], outer[j], outer[jNext]));
    }
  }

  printf("%.8lf\n", longest / 2.0);
}

int main() {

  int tc;
  scanf("%d", &tc);

  while (tc--) solve();

  return 0;
}
