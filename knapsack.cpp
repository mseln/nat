/*  
 *  Magnus Selin 2013-06-02
 *  AAPS LiU
 *  Task 1.2: Knapsack
 */

#include <iostream>
#include <vector>
#include <string.h>

using namespace std;

typedef vector<int> vi;

vi knapsack(int C, int n, int * v, int * w){
    int  m[n+1][C+1]; memset(m[0], 0, sizeof(m[0]));
    bool k[n+1][C+1]; memset(k, 0, sizeof(k));

    // Starting with the first item, then the first and second etc. until all items are included
    for (int i = 1; i <= n; i++){
        // Starting with a bag of size 0 then 1 up to C
        for (int j = 0; j <= C; j++){
            // If you chose to pack item i-1 or stay with the ones before
            if (j >= w[i-1]){
                if(m[i-1][j] >= m[i-1][j-w[i-1]] + v[i-1]){
                    m[i][j] = m[i-1][j];
                    k[i][j] = false;
                }
                else{
                    m[i][j] = m[i-1][j-w[i-1]] + v[i-1];
                    k[i][j] = true;
                }
            }
            else{
                m[i][j] = m[i-1][j];
                k[i][j] = false;
            }
        }
    }

    for(int i = 0; i < n+1; i++){
        for(int j = 0; j < C+1; j++){
            cout << m[i][j] << ' ';
        }
        cout << '\n';
    }
    cout << '\n';
    for(int i = 0; i < n+1; i++){
        for(int j = 0; j < C+1; j++){
            cout << k[i][j] << ' ';
        }
        cout << '\n';
    }

    int c = (int)C;
    vi obj;
    // Get the index of which items too pack
    for(int i = n; i > 0; i--){
        if(k[i][c]){
            obj.push_back(i-1);
            c -= w[i-1];
            if(c <= 0) break;
        }
    }
    return obj;
}

int main(){
    double C; int n; 
    while(cin >> C >> n){
        int v[n], w[n];
        for(int i = 0; i < n; i++) cin >> v[i] >> w[i];

        vi obj = knapsack(C, n, v, w);

        cout << obj.size() << '\n';
        for (int i = 0; i < obj.size(); i++){
            cout << obj[i] << ' ';
        }
        cout << "\n";
    }

    return 0;
}