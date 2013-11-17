#include <cmath>

template<class T>
class Vector{
public:

    T x, y;
    Vector(){};
    Vector(T a, T b){x = a; y = b};

    T abs(){return sqrt(x*x+y*y);}
    Vector operator* (T oth){ return Vector(x*oth, y*oth); }
    Vector operator/ (T oth){ return Vector(x/oth, y/oth); }

    Vector operator+ (Vector oth){ return Vector(x+oth.x, y+oth.y); }
    Vector operator- (Vector oth){ return Vector(x+oth.x, y+oth.y); }
    T operator* (Vector oth){ return x*oth.x + y*oth.y; }
    Vector operator/ (Vector oth){ return Vector(x*oth.y-oth.x*y)}
};
