
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
vector<bool> seq;
vector<bool> a;
int n, k;

void db(int t, int p){
	if (t > n){
		if (n % p == 0)
			for (int j = 1; j < p + 1; j++)
				seq.push_back(a[j]);
	}
	else{
		a[t] = a[t - p];
		db(t + 1, p);
		for (int j = a[t - p] + 1; j < 2; j++){
			a[t] = j;
			db(t + 1, t);
		}
	}
}

int de_bruijn(){	
	for(int i = 0; i < n; i++) 
		a.push_back(0);
	db(1, 1);

	int sum = 0;
	for(int i = 0; i < n; i++){
		sum += seq[(k+i) % (int)pow((double)2, n)] * pow((double)2, n-i-1);
	}
	cout << sum << '\n';
}

int main(){
	int tc;
	cin >> tc;
	for(int we = 0; we < tc; we++){
		cin >> n >> k;
		a.clear(); seq.clear();
		de_bruijn();
	}
}