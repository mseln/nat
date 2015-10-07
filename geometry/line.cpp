/*
 * Simple line segment representation.
 */
template <class T>
class Line2 {
public:
  typedef T Type;
  typedef Point2<T> Point;

  Point from, to;

  Line2() {}
  Line2(const Point &from, const Point &to) : from(from), to(to) {}

  /*
   * The line's direction, measured from "from".
   */
  Point dir() const { return to - from; }

  /*
   * The line's angle. This angle is the angle of "dir", relative the vector (1, 0).
   */
  double angle() const {
    Point pt = dir();
    return atan2(pt.y, pt.x);
  }

  /*
   * Orthogonal projection of a point onto this line. Returns where on the line the point
   * is located, 0 = from, 1 = to. May be outside this range.
   */
  double project(Point pt) const {
    return double((pt - from) | dir()) / lengthSq(dir());
  }

  /*
   * Orthogonal projection of the two points of another line onto this line.
   */
  pair<double, double> project(Line2<T> line) const {
    return make_pair(project(line.from), project(line.to));
  }
};

/*
 * Point - line-segment intersection.
 */
template <class T>
bool intersects(Point2<T> point, Line2<T> line) {
  if (line.from == line.to) {
    return line.from == point;
  } else {
    Point2<T> dir = line.to - line.from;
    Point2<T> pt = point - line.from;
    Point2<T> pt2 = point - line.to;

    return (dir % pt) == 0 && (dir | pt) >= 0 && (-dir | pt2) >= 0;
  }
}

/*
 * Distance between a point and a line segment.
 */
template <class T>
double distance(Point2<T> point, Line2<T> line) {
  if (line.from == line.to)
    return distance(line.from, point);

  /* Project pt unto the line. */
  double projection = line.project(point);

  if (projection <= 0)
    return distance(line.from, point);
  else if (projection >= 1)
    return distance(line.to, point);

  Point2<double> proj = Point2<double>(line.dir()) * projection;
  return length(proj - Point2<double>(point - line.from));
}


/*
 * line-segment - line-segment intersection. Reports wether the lines intersect
 * or not.
 */
template <class T>
bool intersects(Line2<T> a, Line2<T> b) {
  typedef Point2<T> Pt;

  Pt aDir = a.dir();
  Pt bDir = b.dir();
  Pt delta = a.from - b.from;

  if (aDir == Pt() && bDir == Pt()) {
    return a.from == b.from;
  } else if (aDir == Pt()) {
    /* We can manage if bDir == 0 */
    return intersects(b, a);
  }

  T cross = aDir % bDir;
  if (cross == 0) {
    /* Parallel lines, project the two points in B onto A and see where they are located. */

    /* Check if the lines are on the same line. */
    if (delta % aDir != 0)
      return false;

    double from = a.project(b.from);
    double to = a.project(b.to);

    double low = min(from, to);
    double high = max(from, to);

    return low <= 1 && high >= 0;
  } else {
    /* The lines intersect, where? */

    /* Distance along bDir * cross */
    T u = aDir % delta;
    /* Distance along aDir * cross */
    T v = bDir % delta;

    return between(T(0), u, cross) && between(T(0), v, cross);
  }
}

/*
 * Helper to intersection() below. Adds two points, only if they are distinct.
 */
template <class T>
inline void addPoints(vector<Point2<double> > &result, const Point2<T> &a, const Point2<T> &b) {
  result << Point2<double>(a);
  if (a != b) result << Point2<double>(b);
}

/*
 * Compute the intersection between two line segments.
 * Returns zero, one or two points depending on if there is an intersection
 * and if that intersections is a point or a line.
 * If there are two points, this always returns the intersection points
 * sorted along the direction of line a.
 */
template <class T>
vector<Point2<double> > intersection(Line2<T> a, Line2<T> b) {
  typedef Point2<T> Pt;
  typedef Point2<double> PtD;

  vector<PtD> result;

  Pt aDir = a.dir(), bDir = b.dir();
  Pt delta = a.from - b.from;

  if (aDir == Pt() && bDir == Pt()) {
    if (a.from == b.from)
      result << PtD(a.from);
    return result;
  } else if (aDir == Pt()) {
    return intersection(b, a);
  }

  T cross = aDir % bDir;
  if (cross == 0) {
    /* The lines are parallel. */

    /* Are they in the same line? */
    /* See if vectors from a.from to b.from is parallel with a.from to a.to */
    if (delta % aDir == 0) {
      double low = a.project(b.from);
      double high = a.project(b.to);

      Pt lowPt(b.from);
      Pt highPt(b.to);

      if (low > high) {
	swap(low, high);
	swap(lowPt, highPt);
      }

      if (b.from == b.to) {
	if (low >= 0 && low <= 1)
	  result << PtD(b.from);
      } else {
	if (low < 0 && high >= 0 && high <= 1)
	  addPoints(result, a.from, highPt);
	else if (low < 0 && high >= 1)
	  addPoints(result, a.from, a.to);
	else if (low >= 0 && high <= 1)
	  addPoints(result, lowPt, highPt);
	else if (low >= 0 && low <= 1)
	  addPoints(result, lowPt, a.to);
      }
    }
  } else {
    /* Distance along bDir * cross */
    T u = aDir % delta;
    /* Distance along aDir * cross */
    T v = bDir % delta;

    if (between(T(0), u, cross) && between(T(0), v, cross)) {
      result << PtD(a.from) + PtD(aDir) * v / double(cross);
    }
  }

  return result;
}

/*
 * Distance between two line segments.
 */
template <class T>
double distance(Line2<T> a, Line2<T> b) {
  if (intersects(a, b))
    return 0.0;

  /*
   * Now that we know that the lines are not intersecting, we can easily
   * compute the shortest distance between all endpoints on the lines
   * to the other line.
   */
  double shortest =
    min(min(distance(a.from, b),
	    distance(a.to, b)),
	min(distance(b.from, a),
	    distance(b.to, a)));

  return shortest;
}
