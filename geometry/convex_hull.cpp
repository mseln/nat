#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef unsigned int nat;

template <class T>
struct Point {
  T x, y;

  Point(T x = T(), T y = T()) : x(x), y(y) {}

  bool operator <(const Point<T> &o) const {
    if (y != o.y) return y < o.y;
    return x < o.x;
  }

  Point<T> operator -(const Point<T> &o) const { return Point<T>(x - o.x, y - o.y); }
  Point<T> operator +(const Point<T> &o) const { return Point<T>(x + o.x, y + o.y); }

  T lenSq() const { return x*x + y*y; }
};

template <class T>
struct sort_less {
  const Point<T> &ref;
  
  sort_less(const Point<T> &p) : ref(p) {}

  double angle(const Point<T> &p) const {
    Point<T> delta = p - ref;
    return atan2(delta.y, delta.x);
  }

  bool operator() (const Point<T> &a, const Point<T> &b) const {
    double aa = angle(a);
    double ab = angle(b);
    if (aa != ab) return aa < ab;
    return (a - ref).lenSq() < (b - ref).lenSq();
  }
};

template <class T>
int ccw(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3) {
  return (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
}

template <class T>
vector<Point<T> > convex_hull(vector<Point<T> > input) {
  if (input.size() < 2) return input;
  nat size = input.size();

  vector<Point<T> > output;
  
  // Find the point with the lowest x and y value.
  int minIndex = 0;
  for (int i = 1; i < size; i++) {
    if (input[i] < input[minIndex]) {
      minIndex = i;
    }
  }

  // This is the "root" point in our traversal.
  Point<T> p = input[minIndex];
  output.push_back(p);
  input.erase(input.begin() + minIndex);

  // Sort the other elements according to the angle with "p"
  sort(input.begin(), input.end(), sort_less<T>(p));

  // Add the first point from "input" to the "output" as a candidate.
  output.push_back(input[0]);

  // Start working our way through the points...
  input.push_back(p);
  size = input.size();
  for (nat i = 1; i < size; i++) {
    while (output.size() >= 2) {
      nat last = output.size() - 1;
      int c = ccw(output[last - 1], output[last], input[i]);

      if (c == 0) {
	// Colinear points! Take away the closest.
	if ((output[last - 1] - output[last]).lenSq() <= (output[last - 1] - input[i]).lenSq()) {
	  if (output.size() > 1)
	    output.pop_back();
	  else
	    break;
	} else {
	  break;
	}
      } else if (c < 0) {
	if (output.size() > 1)
	  output.pop_back();
	else
	  break;
      } else {
	break;
      }
    }

    // Do not take the last point twice.
    if (i < size - 1)
      output.push_back(input[i]);
  }

  return output;
}


typedef Point<int> Pt;

bool solve() {
  nat count;
  scanf("%d", &count);

  if (count == 0) return false;

  vector<Pt> points(count);
  for (nat i = 0; i < count; i++) {
    scanf("%d %d", &points[i].x, &points[i].y);
  }

  vector<Pt> result = convex_hull(points);

  printf("%d\n", (int)result.size());
  for (nat i = 0; i < result.size(); i++) {
    printf("%d %d\n", result[i].x, result[i].y);
  }

  return true;
}

int main() {
  while(solve());

  return 0;
}
