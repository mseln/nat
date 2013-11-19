/* Calculate the area of an arbitrary polygon
 * <vector> and "geometry.cpp" must be included
 * source: Magnus Selin
 */

template <class T>
int area(vector<Vector<T> > v){
    int area = 0;
    for(int i = 0; i < v.size()-1; i++)
        area += (v[i] % v[i+1]).z;
    area += (v[v.size()-1] % v[0]).z;
    return area;
}