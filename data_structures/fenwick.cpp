#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;


typedef long long int lli;
typedef vector<lli> vi;


#define last_dig(x) (x & (-x))

void fenwick_create(vi &t, lli n){
    t.assign(n + 1, 0);
}
lli fenwick_read(const vi &t, lli b){
    lli sum = 0;
    while(b > 0){
        sum += t[b];
        b -= last_dig(b);
    }
    return sum;
}

void fenwick_update(vi &t, lli k, lli v){
    while(k <= (lli)t.size()){
        t[k] += v;
        k += last_dig(k);
    }
}

int main(){
    lli N, Q; scanf("%lld%lld", &N, &Q);
    vi ft; fenwick_create(ft, N);

    char op; lli a, b;
    for(lli i = 0; i < Q; i++){
        scanf("%*[ \n\t]%c", &op);
        switch (op){
            case '+':
            scanf("%lld%lld", &a, &b);
            fenwick_update(ft, a+1, b);
            break;
            
            case '?':
            scanf("%lld", &a);
            printf("%lld\n", fenwick_read(ft, a));
            break;
        }
    }

    return 0;
}