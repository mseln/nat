// All pairs shortest path (Floyd Warshall). Assign nodes which are part of a
// negative cycle to minus infinity.

#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

#define INF 1000000000
using namespace std;

vector< vector <int> > floyd_warshall(vector< vector<int> > d, int n){
    for(int i = 0; i < n; i++) d[i][i] = 0;

    for (int k = 0; k < n; k++)
      for (int i = 0; i < n; i++)
         for (int j = 0; j < n; j++)
            if (d[i][k] != INF and d[k][j] != INF)
                d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
 
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            for(int k = 0; d[i][j] != -INF && k < n; k++)
                if(d[i][k] != INF && d[k][j] != INF && d[k][k] < 0)
                    d[i][j] = -INF;

    return d;
}

int main(){
    int n, m, q; scanf("%d%d%d", &n, &m, &q);
    while(n!=0 or m!=0 or q!=0){
        vector< vector<int> > d;
        d.resize(n);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                d[i].push_back(INF);
        
        for(int i = 0; i < m; i++){
            int f, t, w; scanf("%d%d%d", &f, &t, &w);
            d[f][t] = min(w, d[f][t]);
        }

        d = floyd_warshall(d, n);
        for(int i = 0; i < q; i++){
            int f, t; scanf("%d%d", &f, &t);
            if(d[f][t] == INF)          printf("Impossible\n");
            else if(d[f][t] == -INF)    printf("-Infinity\n");
            else                        printf("%d\n", d[f][t]);
        }
        printf("\n");
        scanf("%d%d%d", &n, &m, &q);
    }
    return 0;
}