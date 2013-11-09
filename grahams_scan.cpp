struct point {
  int x, y;
};
int det(const point& p1, const point& p2, const point& p3)
{
  int x1 = p2.x – p1.x;
  int y1 = p2.y – p1.y;
  int x2 = p3.x – p1.x;
  int y2 = p3.y – p1.y;
  return x1*y2 – x2*y1;
}

// bool ccw(const point& p1, const point& p2, const point& p3)
// { // Counterclockwise? Compare with determinant...
// return (det(p1, p2, p3) > 0);
// }

struct angle_compare {
  point p; // Leftmost lower point
  angle_compare(const point& p) : p(p) { }
  bool operator()(const point& lhs, const point& rhs) {
    int d = det(p, lhs, rhs);
    if(d == 0) // Furthest first if same direction will keep all
      return (x1*x1+y1*y1 > x2*x2+y2*y2); // points at the line
    return (d > 0); // Counterclockwise?
  }
};

int ConvexHull(const vector<point>& p, int* res)
{ // Returns number of points in the convex polygon
  int best = 0; // Find the first leftmost lower point
  for(int i = 1; i < p.size(); ++i)
    {
      if(p[i].y < p[best].y ||
	 (p[i].y == p[best].y && p[i].x < p[best].x))
	best = i;
    }
  sort(p.begin(), p.end(), angle_compare(p[best]));
  for(int i = 0; i < 3; ++i)
    res[i] = i;
  int n = 3;
  for(int i = 3; i < p.size(); ++i)
    {
      // All consecutive points should be counter clockwise
      while(n > 2 && det(res[n-2], res[n-1], i) < 0)
	--n; // Keep if det = 0, i.e. the same line, angle_compare
      res[n++] = i;
    }
  return n;
}
