#include <stdio.h>
#include <string.h>
#include <vector>

#define INF 2000000000

using namespace std;

struct Vertex{
    int d, p;
    bool nc;
    vector<int> n;
};
struct Edge{
    int f, t, w;
};

void negative_loop(Vertex * v, int curr){
    v[curr].nc = true;
    for(int i = 0; i < v[curr].n.size(); i++){
        if(!v[v[curr].n[i]].nc)
            negative_loop(v, v[curr].n[i]);
    }
}

vector<int> bellman_ford(Vertex v[], Edge e[], int n, int m, int s){
    for(int i = 0; i < n; i++){
        if(i == s)  v[i].d = 0;
        else        v[i].d = INF;
        v[i].nc = false;
        v[i].p = -1;
    }

    for(int i = 0; i < n-1; i++){
        for(int j = 0; j < m; j++){
            if(v[e[j].f].d + e[j].w < v[e[j].t].d and v[e[j].f].d != INF){
                v[e[j].t].d = v[e[j].f].d + e[j].w;
                v[e[j].t].p = e[j].f;
            }
        }
    }

    for(int i = 0; i < m; i++){
        if(v[e[i].f].d + e[i].w < v[e[i].t].d and v[e[i].f].d != INF){
            negative_loop(v, e[i].t);
        }
    }

    vector<int> d;
    for(int i = 0; i < n; i++) {
        if(v[i].nc) d.push_back(-INF);
        else        d.push_back(v[i].d);
    }
    return d;
}

int main(){
    int n, m, q, s; scanf("%d%d%d%d", &n, &m, &q, &s);
    while(n!=0 or m!=0 or q!=0 or s!=0){
        Edge e[m];
        Vertex v[n];
        for(int i = 0; i < m; i++){
            scanf("%d%d%d", &e[i].f, &e[i].t, &e[i].w);
            v[e[i].f].n.push_back(e[i].t);
        }

        vector<int> d = bellman_ford(v, e, n, m, s);

        for(int i = 0; i < q; i++){
            int t; scanf("%d", &t);
            if(d[t] == INF) printf("Impossible\n");
            else if(d[t] == -INF) printf("-Infinity\n");
            else printf("%d\n", d[t]);
        }
        printf("\n");
        scanf("%d%d%d%d", &n, &m, &q, &s);
    }

    return 0;
}
