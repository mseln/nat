#include <stdio.h>
#include <queue>
#include <vector>

#define INF 100000000

using namespace std;

struct A{
    A(int a, int b, int c){t0=a; tn = b; w = c;}
    int t0, tn, w; 
};

typedef pair<int, int> ii;
typedef pair<int, A> iA;

class comp{
public:
    int operator()(const ii& a, const ii& b){return (a.second > b.second);}
};

vector<int> dijkstras(vector<iA> G[], int n, int e, int s){
    priority_queue<ii, vector<ii>, comp> Q;

    vector<int> c; for(int i = 0; i < n; i++) c.push_back(INF); c[s] = 0;
    vector<int> p; for(int i = 0; i < n; i++) p.push_back(-1);
    
    Q.push(ii(s, c[s]));
    int u, sz, v, t0, tn, w, wt;
    while(!Q.empty()){
        
        u = Q.top().first; Q.pop();
        sz = G[u].size();
        for(int i = 0; i < sz; i++){
            v = G[u][i].first;
            tn = G[u][i].second.tn;
            t0 = G[u][i].second.t0;
            w = G[u][i].second.w;

            wt = t0 - c[u];
            if (wt < 0 and tn == 0) continue;
            while(wt < 0) wt+=tn;

            if( c[v] > c[u] + w + wt){
                c[v] = c[u] + w + wt;
                p[v] = u;
                Q.push(ii(v, c[v]));
            }
        }
    }

    //printf("Path to follow: ");
    //for(int i = 0; i < n; i++) printf("%d ", p[i]);
    //printf("\n");

    return c;
}

int main(){
    int n, e, q, s; 
    scanf("%d%d%d%d", &n, &e, &q, &s);
    while(n!=0 or e!=0 or q!=0 or s!=0){
        vector<iA> G[n];
        for(int i = 0; i < e; i++){
            int f, t, t0, tn, w;
            scanf("%d%d%d%d%d", &f, &t, &t0, &tn, &w);
            G[f].push_back(iA(t, A(t0, tn, w)));
        }
        vector<int> c = dijkstras(G, n, e, s);

        for(int i = 0; i < q; i++) {
            int d; scanf("%d", &d);
            if(c[d] == INF)   printf("Impossible\n");
            else              printf("%d\n", c[d]);
        }
        printf("\n");
        
        scanf("%d%d%d%d", &n, &e, &q, &s);
    }

    return 0;
}
