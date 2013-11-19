#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <list>

typedef vector<int> vi;

using namespace std;

list<int> cyc;

void euler_tour(list<int>::iterator i, int u) {
    for(int j = 0; j < (int)AdjList[u].size(); j++){
        ii v = AdjList[u][j];
        if (v.second){
            v.second = 0;
            for(int k = 0; k < (int)AdjList[u].size(); k++){
                ii uu = AdjList[v.first][k];
                if(uu.first == u && uu.second) {uu.second = 0; break;}
            }
            euler_tour(cyc.insert(i, u), v.first)
        }
    }
}

int main(){
    cyc.clear();
    euler_tour(cyc.begin(), A);
    for(list<int>::iterator it = cyc.begin(); it != cyc.end(); it++;)
        printf("%d\n", *it);
}