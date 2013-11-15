#include <stdio.h>

using namespace std;

class Q{
private:
    long long int p, q;
    long long int gcd(long long int a, long long int b) {
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        if (0 == b) return a;
        else return gcd(b, a % b);
    }
public:
    Q(){}
    Q(long long int a, long long int b){
        p = a; q = b;
        if(q < 0){p = -p; q = -q;}
        if (p == 0) q = 1;
        if (q == 0){
            printf("ERR: den = 0!\n");
            q = 1;
        }
        long long int g = gcd(p, q);
        p /= g; q /= g;
    }
    
    Q operator + (Q a){
        Q b = * this;
        Q res = Q((a.p * b.q + b.p * a.q), (a.q * b.q));
        return res;
    }
    
    Q operator - (Q a){
        Q b = * this;
        Q res;
        if(a==b) res = Q(0,0);
        else res = Q((b.p * a.q - a.p * b.q), (a.q * b.q));
        return res;
    }

    Q operator * (Q a){
        Q b = * this;
        Q res = Q(a.p * b.p, a.q * b.q);
        return res;
    }
    
    Q operator / (Q a){
        Q b = * this;
        Q res = Q(b.p * a.q, b.q * a.p);
        return res;
    }

    bool operator == (Q a){
        Q f = * this;
        Q s = Q(a.p, a.q);
        return (f.p == s.p and f.q == s.q);
    }

    void operator = (Q a){
        this->p = a.p; 
        this->q = a.q;
    }

    void print(){
        printf("%lld / %lld\n", p, q);
    }
};

int main(){
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++){
        int tp, tn; 
        scanf("%d%d", &tp, &tn); Q a = Q(tp, tn);

        char t=' '; while (t == ' ') scanf("%c", &t);
        
        scanf("%d%d", &tp, &tn); Q b = Q(tp, tn);

        switch(t){
            case '+': (a+b).print(); break;
            case '-': (a-b).print(); break;
            case '*': (a*b).print(); break;
            case '/': (a/b).print(); break;
        }
    }

    return 0;
}