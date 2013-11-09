#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

int find(int * root, int x){
	if (root[x] == x) return x;
	root[x] = find(root, root[x]);
	return root[x];
}

void uni(int * root, int * deep, int x, int y){
	int a = find(root, x); 
	int b = find(root, y);
	if (deep[a] < deep[b]) root[a] = b;
	if (deep[a] > deep[b]) root[b] = a;
	if (deep[a] == deep[b]) {
		root[b] = a; 
		deep[a] += 1;
	}
}

bool issame(int * root, int a, int b){
	return(find(root, a) == find(root, b));
}

int main(){
	int n, no; scanf("%d%d", &n, &no);
	int root[n], deep[n];
	for(int i = 0; i < n; i++){
		root[i] = i;
		deep[i] = 0; 
	}

	for(int i = 0; i < no; i++){
		char op; int a, b;
		scanf("%*[ \n\t]%c", &op);
		scanf("%d%d", &a, &b);
		if(op == '?'){
			if(issame(root, a, b)) printf("yes\n");
			else                   printf("no\n");
		}
		if(op == '=')
			uni(root, deep, a, b);
	}

}