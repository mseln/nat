#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

struct AnsEdge{
	int f, t;
	bool operator<(const AnsEdge& oth) const{
		if(f == oth.f)
			return(t < oth.t);
		return(f < oth.f);
	}

	AnsEdge(){};
	AnsEdge(int a, int b){f = a; t = b;};
};
struct Tree{
	int w;
	bool complete;
	std::vector<AnsEdge> e;
	Tree(){
		w = 0;
		complete = true;
	}
};

struct Vertex{
	Vertex *p;
	Vertex *root(){
		if(p->p != p)
			p = p->root();
		return p;
	}
};
struct Edge{
	int f, t, w;

	bool operator<(const Edge& oth) const{
		if (w == oth.w)
			return(t < oth.t);
		return(w < oth.w);
	}
};


Tree kruskal(Vertex * v, Edge * e, int numv, int nume){
	Tree ans;
	int sum = 0;

	for(int i = 0; i < numv; ++i){
		v[i].p = &v[i];
	}

	sort(&e[0], &e[nume]);

	for(int i = 0; i < nume; ++i){
		if(v[e[i].f].root() != v[e[i].t].root()){
			v[e[i].t].root()->p = v[e[i].f].root();
			ans.w += e[i].w;

			if(e[i].t < e[i].f) ans.e.push_back(AnsEdge(e[i].t, e[i].f));
			else				ans.e.push_back(AnsEdge(e[i].f, e[i].t));
		}
	}

	Vertex * p = v[0].root();
	for(int i = 0; i < numv; ++i)
		if(p != v[i].root()){
			ans.complete = false;
			break;
		}

	sort(ans.e.begin(), ans.e.end());
	
	return ans;
}

int main(){
	int n, m; scanf("%d%d", &n, &m);
	while(n or m){
		Vertex v[n];
		Edge e[m];

		for(int i = 0; i < m; i++){
			int f, t;
			scanf("%d%d%d", &f, &t, &e[i].w);
			e[i].f = f; 
			e[i].t = t;
		} 

		Tree ans = mst(v, e, n, m);

		if(ans.complete){
			printf("%d\n", ans.w);
			for(int i = 0; i < ans.e.size(); i++){
				printf("%d %d\n", ans.e[i].f, ans.e[i].t);
			}
		}
		else printf("Impossible\n");

		scanf("%d%d", &n, &m);
	}

	return 0;
}