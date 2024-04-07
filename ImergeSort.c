#include <stdio.h>
#include <assert.h>
#include <string.h>
typedef long long int lli;
typedef struct pair{
    lli want; lli ask;
}pll;
#define FOR(i,a,n) for(i=a;i<=n-1;i++)
#define M (int)2e5+4
pll a[M],t[M];

typedef int (*comparator_t)(const void* frr,const void* arr,int fr,int sc);
typedef void (*swap_t)(const void* frr,const void* arr, int fr,int sc);

void swapPairs(const void* frr,const void* arr,int fr,int sc){
    pll* t1 = (pll*)frr; 
    pll* t2 = (pll*)arr;
    if(t2==NULL){
        pll p1 = t1[fr];
        t1[fr] = t1[sc];
        t1[sc] = p1;
    }
    return;
}

int comparePairWant(const void* frr,const void* arr,int fr,int sc){
    pll* t1 = (pll*)frr; 
    pll* t2 = (pll*)arr;
    
        if(t1[fr].want==t1[sc].want){
            return t1[fr].ask<=t1[sc].ask;
        }
        return t1[fr].want<t1[sc].want;
    
    
}

int comparePairAsk(const void* frr,const void* arr,int fr,int sc){
    pll* t1 = (pll*)frr; 
    pll* t2 = (pll*)arr;
    
        if(t1[fr].ask==t1[sc].ask){
            return t1[fr].want<=t1[sc].want;
        }
        return t1[fr].ask<t1[sc].ask;
}

int nextGap(int gap)
{
    if (gap <= 1)
        return 0;
         
    return (int)((gap+1) / 2);
}

void ShellSort(const void* arr,int start,int end,swap_t swapfn,comparator_t compfn){
    
    for(int gap=nextGap(end-start+1);gap>0;gap=nextGap(gap)){
        for(int fr=start;fr<=end;fr++){
            for(int sc = fr;((sc-gap)>=0) && compfn(arr,NULL,sc,sc-gap); sc-=gap) /* insertion sort  */
                 swapfn(arr,NULL,sc,sc-gap);   
        }
    }
    
    return;
}

void inPlaceMerge(const void* arr, int s,
                              int e,swap_t swapfn,comparator_t compfn)
{
    int len = e - s + 1;
    for( int g=nextGap(len); g>0; g = nextGap(g)){ //larger gap to smaller shell
        for(int first=s; first+g <= e ;first++){ // sliding window
                if(compfn(arr,NULL,first+g,first)){
                    swapfn(arr,NULL,first+g,first);
                }
        }    
    }
}
 

void ImergeSort(const void* nums, int s,int e,swap_t swapfn,comparator_t compfn){
    int len = e-s+1;
    int gap=1;
    for(gap=2;gap<=len;gap*=2){              // gap start with 2
        for(int fr = s;fr+gap-1<=e;fr+=gap){ // think about [01] [23]
            int low = fr;
            int high = fr + gap-1;
            int mid = (low+high)/2;
            inPlaceMerge(nums, low, high,swapfn,compfn);
        }
    }
    if((gap/2)<len){
        inPlaceMerge(nums, s, e,swapfn,compfn);
    }
    return;
}

// void mergeSort(const void* nums, int s,
//                               int e,swap_t swapfn,comparator_t compfn)
// {
//     if (s == e)
//         return;
 
//     // Calculating mid to slice the
//     // array in two halves
//     int mid = (s + e) / 2;
 
//     // Recursive calls to sort left
//     // and right subarrays
//     mergeSort(nums, s, mid,swapfn,compfn);
//     mergeSort(nums, mid + 1, e,swapfn,compfn);
     
//     inPlaceMerge(nums, s, e,swapfn,compfn);
// }

void solve(){
    int n,i;
    assert(fscanf(stdin,"%d",&n)>0);
    FOR(i,0,n)     assert(fscanf(stdin,"%lli %lli",&a[i].want,&a[i].ask)>0);
    memcpy(t,a,M*sizeof(pll));
    ImergeSort(t,0,n-1,swapPairs,comparePairAsk);
    //ShellSort(t,0,n-1,swapPairs,comparePair);

    FOR(i,0,n)  printf("%lli %lli\n",t[i].want,t[i].ask);
}
int main()
{
    int tt=1;
    //assert(fscanf(stdin,"%d",&tt)>0);
    while((tt--)>0){
        solve();
    }
    return 0;
}
