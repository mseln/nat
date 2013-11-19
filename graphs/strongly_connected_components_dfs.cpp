/* Name: Strongly Connected Components - Double DFS
 * Description: Untested SCC algorithm. Calculates a new graph where all strongly connected components are merged. Does not require the graph to be connected.
 * Source: Fredrik Svensson - 2009 */
struct vertex
{
	vector<vertex*> from, to;
	bool visited;
};
vector<vertex> v;
vector<vector<vertex*> > res;

vector<vertex*> sorted;
vector<vertex*>::reverse_iterator visitIt;
vector<vertex*>* curRes;

void dfs(vertex* p)
{
	if(p->visited) return;
	p->visited = true;
	if(curRes) curRes->push_back(p);
	for(vector<vertex*>::iterator it = p->to.begin();
		it != p->to.end(); ++it)
		dfs(*it);
	*(visitIt++) = p;
}

void run()
{
	sorted.resize(v.size());
	visitIt = sorted.rbegin();
	for(vector<vertex>::it it = v.begin();
      it != v.end(); ++it)
		it->visited = false;
	for(vector<vertex>::it it = v.begin(); 
      it != v.end(); ++it)
		dfs(&(*it));
	for(vector<vertex>::it it = v.begin(); 
      it != v.end(); ++it)
	{
		it->visited = false;
		it->from.swap(it->to);
	}
	for(vector<vertex>::iterator it = sorted.begin();
		it != sorted.end(); ++it)
		if(!(*it)->visited)
		{
			curRes = &(*res.insert(res.end()));
			dfs(&(*it));
		}
}
