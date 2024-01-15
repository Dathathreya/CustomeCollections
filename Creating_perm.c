#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
 
#define SZ 201
 
#define min(a,b) (a<=b)?(a):(b) 
#define max(a,b) (a>=b)?(a):(b) 
#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)
 
typedef void (*swap_func_t)(const void *,const void*,int,int);
typedef int (*comparator_t)(const void *,const void*,int,int);
 
#define swapGeneric(type,a,b) \
		type c = a;a=b,b=c;
 
const int mod =(int)1e9+7;
int a[SZ];
int chSet[26];char ch[9];char perms[40320][9];
 
void swap_ints(const void* arr,const void* brr,int first,int second){
	if((first!=-1)&&(second!=-1)){
		int* temp =(int*)arr;
		swapGeneric(int,temp[first],temp[second]); 
	}
	return;
}
 
int compare_ints(const void* arr,const void* brr,int first,int second){
	if((first!=-1)&&(second!=-1)){
		int* temp =(int*)arr;
		return temp[first]<temp[second];
	}
	return 0;
}
 
void swap_chars(const void* arr,const void* brr,int first,int second){
	if((first!=-1)&&(second!=-1)){
		char* temp =(char*)arr;
		swapGeneric(char,temp[first],temp[second]); 
	}
	return;
}
 
int compare_chars(const void* arr,const void* brr,int first,int second){
	if((first!=-1)&&(second!=-1)){
		char* temp =(char*)arr;
		return temp[first]<temp[second];
	}
	return 0;
}
 
void reverse(const void* arr,swap_func_t swap_func,int low,int high){
	for(;low<=high;low++,high--){
		swap_func(arr,NULL,low,high);
	}
	return;
}

int prev_permutation(const void* arr,int low,int high,swap_func_t swap_func,comparator_t compare_func){
	int prev=-1,curr=-1,atmost=-1,isFound=0;
	for(int i=low;i<=high;i++){
		if(compare_func(arr,NULL,i,i-1)){
			prev=i-1;curr=i;isFound=1;
		}
	}
	if(isFound)
	{
		for(int i=curr;i<=high;i++){
			/* atmost character smaller than prev */
			if(compare_func(arr,NULL,i,prev)){
				atmost=i;
			}
		}
		if(atmost!=-1)
		{
			swap_func(arr,NULL,atmost,prev);
			reverse(arr,swap_func,curr,high); 
		}
	}
	return isFound;
}
 
int next_permutation(const void* arr,int low,int high,swap_func_t swap_func,comparator_t compare_func){
	int prev=-1,curr=-1,least=-1,isFound=0;
	for(int i=low;i<=high;i++){
		if(compare_func(arr,NULL,i-1,i)){
			prev=i-1;curr=i;isFound=1;
		}
	}
	if(isFound)
	{
		for(int i=curr;i<=high;i++){
			/* least character greater than prev */
			if(compare_func(arr,NULL,prev,i)){
				least=i;
			}
		}
		if(least!=-1)
		{
			swap_func(arr,NULL,least,prev);
			reverse(arr,swap_func,curr,high); 
		}
	}
	return isFound;
}
 
void solve(){
	int n,cnt=0,i,z=0;
	assert(fscanf(stdin,"%s",&ch)>0);
	n=strlen(ch);
	memset(chSet,0,sizeof(chSet));
	FOR(i,0,n){
		chSet[ch[i]-'a']+=1;
	}
	z=0;
	FOR(i,0,26){
		while(chSet[i]--){
			ch[z]= (char)(i+'a');
			z+=1;
		}
	}
	do{
		memcpy(perms[cnt],ch,n);
		cnt+=1;
	}while(next_permutation(ch,0,n-1,swap_chars,compare_chars)>0);

	// do{
	// 	memcpy(perms[cnt],ch,n);
	// 	cnt+=1;
	// }while(prev_permutation(ch,0,n-1,swap_chars,compare_chars)>0);
	
	printf("%d\n",cnt);
 
	FOR(i,0,cnt){
		printf("%s\n",perms[i]);
	}
	return;
}
 
// https://codeforces.com/problemset/problem/626/F
// https://codeforces.com/contest/1920
// https://www.hackerearth.com/practice/algorithms/graphs/hamiltonian-path/tutorial/
 
int main(int argc,char const* argv[]){
	int tt;
	//assert(fscanf(stdin,"%d",&tt)>0);
	tt=1;
	while(tt--){

		solve();
	}
}
