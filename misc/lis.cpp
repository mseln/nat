#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;
int bin_search(int a[], int t[], int l, int r, int k) {
   int m;
   while( r - l > 1 ) {
      m = l + (r - l)/2;
      if( a[t[m]] >= k )
         r = m;
      else
         l = m;
   }
   return r;
}

vector<int> lis(int a[], int n){
    std::vector<int> lis;
    if(n == 0) return lis;
    int c[n]; memset(c, 0, sizeof(c));
    int p[n]; memset(p, 0xFF, sizeof(p));
    int s = 1;

    c[0] = 0;
    p[0] = -1;
    for(int i = 1; i < n; i++){
        if(a[i] < a[c[0]]){
            c[0] = i;
        }
        else if(a[i] > a[c[s-1]]){
            p[i] = c[s-1];
            c[s] = i;
            s++;
        }
        else{
            int pos = bin_search(a, c, -1, s-1, a[i]);
            p[i] = c[pos-1];
            c[pos] = i;
        }
    }


    int d = c[s-1];
    for( int i = 0; i < s; i++ ){
        lis.push_back(d);
        d = p[d];
    }


    reverse(lis.begin(),lis.end()); 
    return lis;
}
int main(){
    int n;
    while(scanf("%d", &n) == 1){
        int a[n]; for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        vector<int> lseq = lis(a, n);
        
        printf("%d\n", (int)lseq.size());
        for(int i = 0; i < lseq.size(); i++){
            printf("%d ", lseq[i]);
        }
        printf("\n");

        lseq.clear();
    }
}