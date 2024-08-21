#include <stdio.h>
#include <stdbool.h>

#define M (int)3e5+7

typedef long long int ll_t;
typedef long long unsigned llu_t;
typedef long double ld_t;

int fenwickTree[M],fsz=0;

int edges[M][2];

// __getchar_nolock
// __fwrite_nolock

ll_t readi(){
	bool minus = false;
	int result = 0;
	char ch;
	ch = getchar();
	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true; else result = ch-'0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result*10 + (ch - '0');
	}
	if (minus)
		return -result;
	else
		return result;
}

void printi(ll_t ret){
	ll_t rev = 0,zero=0,rev1=0;
	rev = ret;
	if(rev<0){
		putchar('-');
		rev = -rev;
	}
	while((rev>0)&&((rev%10)==0)){
		rev /= 10;
		zero++;
	}
	rev1 = 0;
	while(rev>0){
		rev1 += (rev%10);
		rev /= 10; 
		if(rev>0)
		    rev1 *=10; // scaling is needed only if we still have next 
	}
	while(rev1>0){
		char c = (char)((rev1%10)+'0');
		putchar(c);
		rev1 /= 10;
	}
	while(zero--){
		putchar('0');
	}
	return;
}

int query(int u,int v){
	int inp;
	putchar('?');putchar(' ');printi(u);putchar(' ');printi(v);putchar('\n');
	fflush(stdout);
	inp = readi();
	return inp;
}



void update(int index,int value){
    for(int i=index;i<fsz;){
        fenwickTree[i] += value; 
        index |= (index+1);
        // 0 1 3 7 15 31 63 .... 
        // 2 3 7 15 31 63 
        // 5 7 15 31 63 
        // 4 5 7 15 ... 
        // 6 7 15 ... 
        // 8 9 11 15 (1000,1001,1011,1111,...)
        // 9 11 15 31 63
        // 10 11 15 31 63 (1010,1011,1111,...)
    }
    return;
}

int query1(int index){
    int answer = 0;
    for(int i=index;i>=0;){
        answer += fenwickTree[i];
        i &= (i+1); // inverting all bits set till current
        i--;   // reduce 0 to -1 for loop to break
        // 1011(11<=t), 1100&1011 -> 1000-0001 -> 0111 (7<=t)
        // 0111 & 1000 -> 0000 - 1 terminating case  
        // https://codeforces.com/contest/20/submission/18621092
    }
    return answer;
}

void solve(){
	int n,sz=0;
	n=readi();
	for(int u=2;u<=n;u++){
        int par = 1;
        while(1){
            int newPar = query(par,u);
            if(newPar==par)
                break;
            par=newPar;
        }
        edges[sz][0] = par; 
        edges[sz][1] = u;
        sz++;
    }
	putchar('!');putchar(' ');
	for(int i=0;i<sz;i++){
		printi(edges[i][0]);putchar(' ');printi(edges[i][1]);putchar(' ');
	}
	
	putchar('\n');
	fflush(stdout);
}

int main(){
	int tt=readi();
	while(tt--){
		solve();
	}
}

//to connect n vertices i need n-1 edges to form a tree 
