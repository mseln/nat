/* Description: Untested matrix implementation
 * Source: Benjamin Ingberg */
template<typename T>
struct Matrix {
  typedef Matrix<T> const & In;
  typedef Matrix<T> M;

  int r, c; // rows columns
  vector<T> data;
  Matrix(int r_, int c_, T v = T()) : r(r_), 
      c(c_), data(r_*c_, v) { }
  explicit Matrix(Pt3<T> in)
    : r(3), c(1), data(3*1) {
    rep(i, 0, 3)
      data[i] = in[i];
  }
  explicit Matrix(Pt2<T> in)
    : r(2), c(1), data(2*1) {
    rep(i, 0, 2)
      data[i] = in[i];
  }
  // copy constructor, assignment 
  // and destructor compiler defined
  T & operator()(int row, int col) {
    return data[col+row*c];
  }
  T const & operator()(int row, int col) const {
    return data[col+row*c];
  }
  // implement as needed
  bool operator==(In rhs) const {
    return data == rhs.data;
  }
  M operator+(In rhs) const {
    assert(rhs.r == r && rhs.c == c);
    Matrix ret(r, c);
    rep(i, 0, c*r)
      ret.data[i] = data[i]*rhs.data[i];      
    return ret;
  }  
  M operator-(In rhs) const {
    assert(rhs.r == r && rhs.c == c);
    Matrix ret(r, c);
    rep(i, 0, c*r)
      ret.data[i] = data[i]-rhs.data[i];
    return ret;
  }
  M operator*(In rhs) const { // matrix mult
    assert(rhs.r == c);
    Matrix ret(r, rhs.c);
    rep(i, 0, r)
      rep(j, 0, rhs.c)
	      rep(k, 0, c) 
	        ret(i,j) += operator()(i, k)*rhs(k,j);
    return ret;
  }
  M operator*(T rhs) const { // scalar mult
    Matrix ret(*this);
    trav(it, ret.data)
      it = it*rhs;
    return ret;
  }
};

template<typename T> // create identity matrix
Matrix<T> id(int r, int c) {
  Matrix<T> m(r,c);
  rep(i, 0, r)
    m(i,i) = T(1);
}
