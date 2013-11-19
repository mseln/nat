/* Description: Untested homogenous coordinates
 * transformation geometry.
 * Source: Benjamin Ingberg 
 * Usage: Requires homogenous coordinates, handles
 * multiple rotations, translations and scaling in a
 * high precision efficient manner (matrix
 * multiplication) with homogenous coordinates.
 * Also keeps reverse transformation available. */
namespace h { // avoid name collisions
  struct Transform {
    enum ActionType {
      Scale, Rotate, TranslateX, TranslateY
    };
    typedef tuple<ActionType, fp> Action;
    typedef Matrix<fp> M;
    typedef vector<Action> History;
    History hist;
    M to, from;
    Transform(History h = History())
      : to(id<fp>(3,3)), from(id<fp>(3,3)) {
      doTransforms(h);
    }
    H transformTo(H in) {
      return H(to*M(in));
    }
    H transformFrom(H in) {
      return H(from*M(in));
    }
    Transform & scale(fp s) {
      doTransform(Scale, s);
    }
    Transform & translate(fp dx, fp dy) {
      doTransform(TranslateX, dx);
      doTransform(TranslateY, dy);
    }
    Transform & rotate(fp phi) {
      doTransform(Rotate, phi);
    }
    void doTransforms(History & h) {
      trav(it, h) {
        doTransform(get<0>(*it), get<1>(*it));
      }
    }
    void doTransform(ActionType t, fp v) {
      hist.push_back(make_tuple(t, v));
      if(t == Scale)
        doScale(v);
      else if(t == TranslateX)
        doTranslate(0,v);
      else if(t == TranslateY)
        doTranslate(1,v);
      else
        doRotate(v);
    }
  private:
    void doScale(fp s) {
      M sm(id<fp>(3,3)), ism(id<fp>(3,3));
      sm(1,1) = sm(0,0) = s;
      ism(1,1) = ism(1,1) = 1/s;
      to = to*sm; from = ism*from;
    }
    void doTranslate(int c, fp dx) {
      M sm(id<fp>(3,3)), ism(id<fp>(3,3));
      sm(c,2) = dx;
      ism(c,2) = -dx;
      to = to*sm; from = ism*from;
    }
    void doRotate(fp phi) {
      M sm(id<fp>(3,3)), ism(id<fp>(3,3));
      sm(0,0) = sm(1,1) = cos(phi);
      ism(0,0) = ism(1,1) = cos(-phi);
      ism(1,0) = sm(0,1) = sin(phi);
      ism(0,1) = sm(1,0) = sin(-phi);
      to = to*sm; from = ism*from;
    }
  };
}
