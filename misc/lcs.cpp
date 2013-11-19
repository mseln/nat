/* Longest common substring. */
int HadenIngberg(string const & s, string const & t){
    int n = s.size(), m = t.size(), best;
    for(int i = 0; i < n-best; ++i) { // Go through s
        int cur = 0;
        int e = min(n-i, m);

    // Can best grow?
        for(int j = 0; j < e && best+j < cur+e; ++j)
            best = max(best, 
          cur = (s[i+j] == t[j] ? cur+1 : 0));
    }

    for(int i = 1; i < m-best; ++i) { // Go through t
        int cur = 0;
        int e = min(m-i, n);
    // Can best grow?
        for(int j = 0; j < e && best+j < cur+e; ++j) 
      best = max(best,cur=(t[i+j] == s[j]?cur+1:0));
    }
    return best;
}
