#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define N ((int)4e5)
#define L ((int)1.3e6)

long long int a[N],primes[N];
int pf_cnt=0,f_cnt=0;
bool canprime[L];

typedef long long unsigned  llu;
typedef long long int  lli;

typedef int (*sorting_comparator_t)(const void* arr1,int,int);
typedef void (*swap_items_t)(const void* arr,int,int);

// #define max(a,b) ((a>b)?(a):(b))
// #define min(a,b) ((a<b)?(a):(b))

#define PAIR_STRUCT(type1,type2)\
typedef struct pair_##type1##_##type2{\
    type1 first;type2 second;\
}pair_##type1##_##type2;

PAIR_STRUCT(int,int);
typedef pair_int_int pii;

#define swapGeneric(type,a,b)\
    type c = a;\
    a=b,b=c;

void swap_item_int(const void* arr,int first,int second) {
	long long int* temp = (long long int*)arr;
	swapGeneric(long long int,temp[first],temp[second]);
	return;
}

void swap_item_pii(const void* arr,int first,int second) {
	pii* temp=(pii*)arr;
	swapGeneric(pii,temp[first],temp[second]);
	return;
}

int compare_by_int_asc(const void* arr,int first,int second) {
	long long int* temp=(long long int*)arr;
	return temp[first]<=temp[second];
}
int compare_by_int_desc(const void* arr,int first,int second) {
	return compare_by_int_asc(arr,second,first);
}

int compare_by_pii_asc(const void* arr,int first,int second) {
	pii* temp=(pii*)arr;
	return temp[first].first<=temp[second].first;
}
int compare_by_pii_desc(const void* arr,int first,int second) {
	return compare_by_pii_asc(arr,second,first);
}

void heapify(const void* arr,int root,int size,sorting_comparator_t compfn,swap_items_t sfn,int offset) {
	int greatest = root;
	int left = (root*2)+1;
	int right= (root*2)+2;
	if(left<size && compfn(arr,greatest+offset,left+offset)) {
		greatest=left;
	}
	if(right<size && compfn(arr,greatest+offset,right+offset)) {
		greatest=right;
	}
	if(greatest!=root) {
		sfn(arr,greatest+offset,root+offset);
		heapify(arr,greatest,size,compfn,sfn,offset);
	}
}

void HeapSort(const void* arr,int offset,int n,sorting_comparator_t compfn,swap_items_t sfn) {
	int curr_root;
	for(curr_root=(n/2)-1; curr_root>=0; curr_root--) {
		heapify(arr,curr_root,n,compfn,sfn,offset);
	}
	for(curr_root=n-1; curr_root>0; curr_root--) {

		sfn(arr,0,curr_root);
		heapify(arr,0,curr_root,compfn,sfn,offset);
		//sz-=1;

	}
}
int min(int a,int b) {
	return ((a<b)?(a):(b));
}
int max(int a,int b) {
	return ((a>b)?(a):(b));
}
void regular_sieve(int H) {
	memset(canprime,true,sizeof(canprime));
	canprime[0] = false;
	canprime[1] = false;
	for(int pf = 2; pf <= 3000; pf++) {
		for(int mul=pf*pf; mul<H; mul+=pf) {
			canprime[mul] = false;
		}
	}
	for(int i=0; i<L; i++) {
		if(canprime[i]) {
			primes[pf_cnt++] = i;
			// primes[pf_cnt-1] += ((pf_cnt>=2)?(primes[pf_cnt-2]):(0));
		}
	}
	f_cnt = pf_cnt;
	return;
}
void segmented_seive(int low,int high) {
	memset(canprime,true,sizeof(canprime));
	for(int start=0;start<f_cnt;start++) {
	   int pr_num = primes[start];
	   int begin = ((low+pr_num-1)/pr_num)*pr_num;
		for(int mul=begin; mul<high; mul+= pr_num) {
			  canprime[mul-low] = false;
		}
	}
	 for(int i=low;i<high;i++){
       if((canprime[i-low])&&(pf_cnt<N)){
            primes[pf_cnt++] = i;
       }
    }
	return;
}
void init() {
	pf_cnt=0;
	f_cnt = 0;
	regular_sieve(L);
	int last = primes[pf_cnt-1];
	for(int l=last+1; l<=(int)6e6; l+=last) {
	   segmented_seive(l,l+last);
	}
	// fprintf(stderr,"%dth prime:%lld\n",N,primes[N-1]);
	for(int i=1; i<pf_cnt; i++) {
	   // 5,800,079 5800079
		primes[i] += primes[i-1];
	}
}
void solve() {
	int n,i=0;
	scanf("%d",&n);
	for(i=0; i<n; i++) {
		scanf("%lld",&a[i]);
	}
	// sorting
	HeapSort(a,0,n,compare_by_int_desc,swap_item_int);
	for(i=0; i<n; i++) {
		if(i) a[i] += a[i-1];
	}
	for(int i=n-1; i>=0; i--) {
		long long int entire = a[i], last = primes[i];
		if(entire>=last) {
			printf("%d\n",n-1-i);
			return;
		}
	}
	printf("%d\n",n);
	return;
}

int main()
{
	int tt=1;
	init();
	//fprintf(stdout,"%lld\n",primes[N-1]);
	scanf("%d",&tt);
	while(tt--) {
		solve();
	}
	return 0;
}
