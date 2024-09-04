// https://www.spoj.com/submit/PRIME1/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define N (int)5e5+4
typedef long long int ll;


bool is_prime[N],seg_sieve[N];
ll primes[N];size_t pr_cnt = 0;

ll _max(ll a, ll b) {
	return (a >= b) ? (a) : (b);
}

void generate_sieve(ll limit){
	pr_cnt = 0;
	for(ll unq=2;unq<=limit;unq++){
		is_prime[unq] = true;
	}
	for(ll unq=2;unq <= limit;unq++){
		if(is_prime[unq]){
			primes[pr_cnt++]=unq;
			for(ll repi=unq*unq; repi <= limit; repi+=unq){
				is_prime[repi] = false;
			}
		}
	}
	return;
}

void segmented_sieve(ll l,ll r){
	generate_sieve(((ll)sqrt(r)));
	for(ll c=l;c<=r;c++){
		seg_sieve[c-l] = true;
	}
	for(ll c=0;c<pr_cnt;c++){
		ll unq_pr = primes[c];
		ll start_pr = (l/unq_pr)*unq_pr;// fix start number
		if(start_pr<l){
			start_pr += unq_pr;
		}
		for(ll c1=(((start_pr/unq_pr)>1)?(start_pr):(start_pr+unq_pr));c1<=r;c1+=unq_pr){
			seg_sieve[c1-l] = false;
		}
	}
	// 1 . 2. 3. 4 . 5. ...... 25 
	// factors of current high 
	if(l==1) seg_sieve[0] = false;
	return;
}

void solve(){
	ll l,r;
	scanf("%lld%lld",&l,&r);
	segmented_sieve(l,r);
	for(ll c=l;c<=r;c++){
		 if(seg_sieve[c-l])
		 	printf("%lld\n",c,c-l);
	}
	putchar('\n');
}

int main(){
	int tt;
	scanf("%d",&tt);
	while(tt--){
		solve();
	}
}
