#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#define N (int)4e5+4
#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)
typedef long long unsigned llu;
typedef char* str_t;

#define swap(type,a,b)\
	type c = a;\
	a = b,b = c;

typedef void (*swap_func_t)(const void* arr,int first,int second);
typedef int (*comparator_t)(const void* arr,int first,int second);

char chSet[N];int ch[26];

void swap_int(const void* arr,int start,int end){int* temp=(int*)arr;swap(int,temp[start],temp[end]);}
void swap_char(const void* arr,int start,int end){char* temp=(char*)arr;swap(char,temp[start],temp[end]);}
void swap_str(const void* arr,int start,int end){char** temp=(char**)arr;swap(str_t,temp[start],temp[end]);}
int compare_int(const void* arr,int first,int second){int* temp1=(int*)arr;return temp1[first]<temp1[second];}
int compare_char(const void* arr,int first,int second){char* temp1=(char*)arr;return temp1[first]<temp1[second];}
int compare_str(const void* arr,int first,int second)
{char** temp1=(char**)arr;return (strcmp(temp1[second],temp1[first])>0);}


llu fact(int n){
	return (n<=1)?(1):(n*fact(n-1));
}

void reverse(const void* arr,int start,int end,swap_func_t swpfn){
	for(int i=start,offset=0;i<=end-offset;i++,offset++){
		swpfn(arr,i,end-offset);
	}
	return;
}

int prev_permutation(const void* arr,int low,int high,comparator_t cmfn,swap_func_t swpfn){
	int prev=-1,curr=-1,index=-1,isFound=0,offset=0,i;
	FOR(i,low,(high)){
		if(cmfn(arr,i+1,i)){
			prev=i,curr=i+1,isFound=1;
		}
	}
	if(isFound){
		index=-1;
		FOR(i,curr,(high+1)){
			if(cmfn(arr,i,prev))
			{
				index=i;
			}
		}
		if(index!=-1){
			swpfn(arr,prev,index);
			offset=0;
			for(i=curr;i<=high-offset;i++,offset++){
				swpfn(arr,i,high-offset);
			}
		}
	}	
	return isFound;
}

int next_permutation(const void* arr,int low,int high,comparator_t cmfn,swap_func_t swpfn){
	int prev=-1,curr=-1,index=-1,isFound=0,offset=0,i;
	FOR(i,low,(high)){
		if(cmfn(arr,i,i+1)){
			prev=i,curr=i+1,isFound=1;
		}
	}
	if(isFound){
		index=-1;
		FOR(i,curr,(high+1)){
			if(cmfn(arr,prev,i))
			{
				index=i;
			}
		}
		if(index!=-1){
			swpfn(arr,prev,index);
			offset=0;
			for(i=curr;i<=high-offset;i++,offset++){
				swpfn(arr,i,high-offset);
			}
		}
	}	
	return isFound;	
}

void solve(){
	int n,i,j=0;
	llu total=1;
	assert(fscanf(stdin,"%s",chSet)>0);
	memset(ch,0,sizeof(ch));
	n=strlen(chSet);
	total=1llu*fact(n);
	FOR(i,0,n){
		ch[chSet[i]-'a']+=1;
	}
	FOR(i,0,26){
		if(ch[i])
		  total/=fact(ch[i]);
		while((ch[i]--)){
			chSet[j]=(char)(i+'a');
			j+=1;
		}
	}
	printf("%llu\n",total);
	do{
		printf("%s\n",chSet);
	}while(next_permutation(chSet,0,n-1,compare_char,swap_char));
	// reverse(chSet,0,n-1,swap_char);
	// do{
	// 	printf("%s\n",chSet);
	// }while(prev_permutation(chSet,0,n-1,compare_char,swap_char));
	
}

int main(int argc, char const *argv[])
{
	int tt=1;
	//assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}	
	return 0;
}
