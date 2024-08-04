#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define M (int)2e5+9
#define FOR(n) for(int i=0;i<n;i++)
int min(int a,int b){return (a<=b)?(a):(b);}
int max(int a,int b){return (a>=b)?(a):(b);}
typedef long long unsigned llu;
typedef long long int lli ;

int fenwickTree[M],fsz=0;

void writeInt(int n){
    if(n<0){
        putchar('-');
        n= -n;
    }
    int N=n,rev=n,count=0;
    while((rev%10)==0){count++;rev/=10;}
    rev=0;
    if(N==0) {putchar('0');putchar('\n');return;}
    while(N>=1){
        //printf("%d,",rev); to print character in reverse 
        rev=rev*10+(N%10);N/=10;}
    while(rev>=1){putchar(rev%10 +'0');rev/=10;}
    while(count--){putchar('0');}
    putchar(' ');
    return;
}

bool isD(char _ch){return (_ch>='0' && _ch<='9');}

int readInt(){
   char _ch;
   do{
        _ch = getchar();
   }while( _ch!='-' && !isD(_ch)  );
   bool neg = (_ch=='-');
   int ans = neg ? 0:(_ch-'0');
   while(isD(_ch = getchar())){
       ans = 10*ans + (_ch-'0'); 
   }
   return neg?-ans:ans;
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

int query(int index){
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

void solve(void){
    //int n = 123456789;
    int N=readInt();
    FOR(N)
    {
        int n=readInt();
        printf("%d\n",n);
    }    
    //writeInt(n);
    return;
}


int main(int argc,char* argv[]){
    int tt=1;
    /*assert(fscanf(stdin,"%d",&tt)>0)*/
    while(tt--){
        solve();
    }
    return 0-0;
}

// treap,multiplicative inverse,red black tree,SplayTree
// SCC,DSU,Bipartite,EulerTour,HamiltonPath,SPF,MST,A*

// https://www.geeksforgeeks.org/problems/numbers-with-same-first-and-last-digit4228/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card

