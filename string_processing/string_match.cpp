// Knuth Morris Prat : Search for a string in another one
// Alternative STL algorithms : strstr in <ctring> find in <string> 
// Time complexity : O(n)

#include <cstdio>
#include <cstring>

#define MAX_N 100010

char T[MAX_N], P[MAX_N];    // T = text, P = pattern
int b[MAX_N], n, m;         // b = back table, n = length of T, m = length of P

void kmpPreprocess() {
    int i = 0, j = -1; b[0] = -1;
    while (i < m){
        while(j >= 0 && P[i] != P[j]) j = b[j];
        i++; j++;
        b[i] = j;
    }
}

void kmpSearch() {
    int i = 0, j = 0;
    while(i < n){
        while(j >= 0 && T[i] != P[j]) j = b[j];
        i++; j++;
        if(j==m){
            printf("P is found at index %d in T\n", i - j);
            j = b[j];
        }
    }
}

int main(){
    strcpy(T, "asdhasdhejasdasdhejasdasd");
    strcpy(P, "hej");
    
    n = 25; m = 3;

    kmpPreprocess();
    kmpSearch();

    return 0;
}