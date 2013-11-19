#include <cstdio>

int prime[664579];
int numprimes; 

void calcprimes(int maxn){
    prime[0] = 2; numprimes = 1; prime[numprimes] = 46340; // 0xb504*0xb504 = 0x7FFEA810 
    for(int n = 3; n < maxn; n += 2) {
        for(int i = 1; prime[i]*prime[i] <= n; ++i) {
            if(n % prime[i] == 0) goto not_prime;
        } 
        prime[numprimes++] = n; prime[numprimes] = 46340; // 0xb504*0xb504 = 0x7FFEA810
not_prime: 
        ;
    }
}

int main(){
    calcprimes(10000000);
    for(int i = 0; i < 664579; i++) printf("%d\n", prime[i]);
}