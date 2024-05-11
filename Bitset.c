#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define N (int)4e5+4
typedef long long unsigned llu;
llu bitset[N],prefixSum[N];
int a[N],n,size=0;llu maxi=0;
// bitsets 

void clearAll(){
	memset(bitset,0,sizeof(bitset));
}

int set(int bit){
	bitset[bit>>6] |= (1llu<<(bit&63));
	/*each one slot/block in bitset  has 64 bit*/ 
	/*so we divide pos by 64 to get its slot/block number*/
}

int get(int bit){
	return ((bitset[bit>>6] & (1llu<<(bit&63)))!=0); // &63 ->%64
											 // >>6 ->/64  	
}

int clear(int bit){
	bitset[bit>>6] &= (~(1llu<<(bit&63)));
}

int flip(int bit){
	bitset[bit>>6] ^= (1llu<<(bit&63));
}

void OrLeftShift(int bit){
	int whole = bit >> 6; // 64
	int rem   = bit & 63; // %64
	size=(N+63)/64;
	if(rem==0){
		for(int pos=size;pos>=whole;pos--)
				bitset[pos] |= bitset[pos-whole];
	}
	else{
		for(int pos=size;pos>=whole+1;pos--){
			bitset[pos] |= bitset[pos-(whole)] << (rem);
			bitset[pos] |= bitset[pos-(whole+1)] >> (64-rem);
		}
		bitset[whole] |= bitset[0]<<rem;
	}
}

void printBitSet(){
	for(int i=0;i<N;i++){
		if(bitset[i]){
			for(int j=0;j<64;j++){
				printf("%d",(((bitset[i])&(1llu<<j))!=0));
			}
			printf("\n");
		}

	}
}

llu  max(llu a,llu b){
	return ((a>=b)?(a):(b));
}

void solve(){
	int i;
	assert(fscanf(stdin,"%d",&n)>0);
	clearAll();
	for(i=0;i<n;i++){
		assert(fscanf(stdin,"%d",&a[i])>0);
		prefixSum[i] = ((!i)?(a[i]):(prefixSum[i-1]+a[i]));
	}
	size=(prefixSum[n-1]+63)/64;
	set(0);llu total=0;
	for(i=0;i<2*n;i++){
		if(i<n) total+=a[i];
		if(get(i)){
			maxi=max(maxi,total-i);
		}
		if(i<n) OrLeftShift(a[i]);
		clear(i); // it covers the edge case like 1 0 4 4 -> 
		// 0 1 2 3 4 
		// 1 0 0 0 0 
		// 1 1 0 0 0 
		// 0 1 0 0 0 
		// in second pass this will be also cleared 
		printBitSet();
	}
	
	printf("%llu\n",maxi);
}

int main(){
	int tt=1;
	//assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
