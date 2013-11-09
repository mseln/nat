#include <stdio.h>
#include <queue>
#include <vector>

#define INF 100000000

using namespace std;

typedef pair<int, int> ii;

class comp{
public:
    int operator()(const ii& a, const ii& b){return (a.second > b.second);}
};

vector<int> dijkstras(vector<ii> G[], int n, int e, int s){
    priority_queue<ii, vector<ii>, comp> Q;

    vector<int> c; for(int i = 0; i < n; i++) c.push_back(INF); c[s] = 0;
    vector<int> p; for(int i = 0; i < n; i++) p.push_back(-1);
    
    Q.push(ii(s, c[s]));
    int u, sz, v, w;
    while(!Q.empty()){
        
        u = Q.top().first; Q.pop();
        sz = G[u].size();
        for(int i = 0; i < sz; i++){
            v = G[u][i].first;
            w = G[u][i].second;
            if( c[v] > c[u] + w ){
                c[v] = c[u] + w;
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
        vector<ii> G[n];
        for(int i = 0; i < e; i++){
            int f, t, w;
            scanf("%d%d%d", &f, &t, &w);
            G[f].push_back(ii(t, w));
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
