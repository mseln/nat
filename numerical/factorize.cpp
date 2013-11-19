int factor[1000000]; 
int numf[1000000]; 
int numfactors;

void calcfactors(int n){
    numfactors = 0;
    for(int i = 0; n > 1; ++i){
        if(n % prime[i] == 0){
            factor[numfactors] = prime[i]; 
            numf[numfactors] = 0; 
            do {
                numf[numfactors]++;
                n /= prime[i]; 
            } while(n % prime[i] == 0); numfactors++;
        }
    }
}