/* Name: Bipartite DFS
 * Description: Simple bipartite matching.
 * Slower than HopcroftKarp but shorter.
 * Graph g should be a list of neighbours 
 * of the left partition.
 * n is the size of the left partition 
 * and m is the size of the right partition. 
 * Ifyou want to get the matched pairs, 
 * \lstinline|match[i]| contains match for vertex i on
 * the right side or -1 if it's not matched.
 * Time: \(\mathcal{O}(EV)\)
 * Usage example:
 * \begin{lstlisting}[frame=none, aboveskip=-0.6cm, ]
 * Graph left(n);
 * trav(it, edges){
 *   l[it->left].push_back(it->right);
 * }
 * dfs_matching(left, size_left, size_right);
 * \end{lstlisting}
 * Source: KACTL */

typedef vector<vector<int> > Graph;

vector<int> match;
vector<bool> visited;
template<class G>
bool find(int j, G &g) {
  if (match[j] == -1) return true;
  visited[j] = true; int di = match[j];
  trav(e, g[di])
  if (!visited[*e] && find(*e, g)) {
    match[*e] = di;
    match[j] = -1;
    return true;
  }
  return false;
}
int dfs_matching(Graph &g, int n, int m) {
  match.assign(m, -1);
  rep(i,0,n) {
    visited.assign(m, false);
    trav(j,g[i])
    if (find(*j, g)) {
      match[*j] = i;
      break;
    }
  }
  return m - count(match.begin(), match.end(), -1);
}

