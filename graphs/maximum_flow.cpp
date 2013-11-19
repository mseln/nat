int res[MAX_V][MAX_V], mf, f, s, t;
vi p;

void augment(int v, int minEdge) {
    if(v == s){f = minEdge; return;}
    else if(p[v] != -1){augment(p[v], min(minEdge, res[v][p[v]]));
                        res[p[v]][v] -= f; res[v][p[v]] += f; }
}

int solve(){
    mf = 0; // Max Flow

    while(1){
        f = 0;
        vi dist(MAX_V, INF); dist[s] = 0; queue<int> q; q.push(s);
        p.assign(MAX_V, -1);
        while(!q.empty()){
            int u = q.front(); q.pop();
            if(u == t) break;
            for(int v = 0; v < MAX_V; v++)
                if (res[u][v] > 0 && dist[v] == INF)
                    dist[v] = dist[u] + 1, q.push(v), p[v] = u;
        }
        augument(t, INF);
        if(f == 0) break;
        mf += f;
    }

    printf("%d\n", mf);
}