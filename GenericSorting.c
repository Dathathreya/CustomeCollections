#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

#define N (int)4e5+5
#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)

typedef long long unsigned  llu;

typedef int (*sorting_comparator_t)(const void* arr1,int,int);
typedef void (*swap_items_t)(const void* arr,int,int);

#define PAIR_STRUCT(type1,type2)\
typedef struct pair_##type1##_##type2{\
    type1 first;type2 second;\    
}pair_##type1##_##type2;

PAIR_STRUCT(int,int);
typedef pair_int_int pii;

#define swapGeneric(type,a,b)\
    type c = a;\
    a=b,b=c;\

void swap_item_int(const void* arr,int first,int second) {
    int* temp = (int*)arr;swapGeneric(int,temp[first],temp[second]);return;}

void swap_item_pii(const void* arr,int first,int second){
    pii* temp=(pii*)arr;swapGeneric(pii,temp[first],temp[second]);return;}

int compare_by_int_asc(const void* arr,int first,int second){int* temp=(int*)arr;return temp[first]<=temp[second];}
int compare_by_int_desc(const void* arr,int first,int second){return compare_by_int_asc(arr,second,first);}

int compare_by_pii_asc(const void* arr,int first,int second){pii* temp=(pii*)arr;return temp[first].first<=temp[second].first;}
int compare_by_pii_desc(const void* arr,int first,int second){return compare_by_pii_asc(arr,second,first);}

// TLE for MergeSort
void Imerger(const void* arr,int low,int mid,int high,sorting_comparator_t compfn,swap_items_t sfn){     
     int start=low,start2=mid+1;
     if(compfn(arr,mid,start2)){
        return;
     }
     while((start<=mid)&&(start2<=high)){
        if(compfn(arr,start,start2)){
            start++;
        }
        else
        {
            int index = start2;
            while(index!=start){
                if(compfn(arr,index,index-1))  
                    sfn(arr,index,index-1);
                index--;
            }
            start++;start2++,mid++;
        }
     }
}

void IMergeSort(const void* arr,int low,int high,sorting_comparator_t compfn,swap_items_t sfn){
    int m;
    if(low>=high){
        return;
    }
    m = low + (high-low)/2;
    IMergeSort(arr,low,m,compfn,sfn);
    IMergeSort(arr,m+1,high,compfn,sfn);
    Imerger(arr,low,m,high,compfn,sfn);
    return;
}

// Accepted Solution for HeapSort https://codeforces.com/contest/1909/submission/239793284
void heapify(const void* arr,int root,int size,sorting_comparator_t compfn,swap_items_t sfn,int offset){
    int greatest = root;
    int left = (root*2)+1;
    int right= (root*2)+2;
    if(left<size && compfn(arr,greatest+offset,left+offset)){
        greatest=left;
    }
    if(right<size && compfn(arr,greatest+offset,right+offset)){
        greatest=right;
    }
    if(greatest!=root){
        sfn(arr,greatest+offset,root+offset);
        heapify(arr,greatest,size,compfn,sfn,offset);
    }
}

void HeapSort(const void* arr,int offset,int n,sorting_comparator_t compfn,swap_items_t sfn){
    int curr_root;
    for(curr_root=(n/2)-1;curr_root>=0;curr_root--){
        heapify(arr,curr_root,n,compfn,sfn,offset);
    }
    for(curr_root=n-1;curr_root>0;curr_root--){

        sfn(arr,0,curr_root);
        heapify(arr,0,curr_root,compfn,sfn,offset);
        //sz-=1;
        
    }
}

pii pairs[N];
int C[N],intervals[N],Stack[N];

void solve(){
    int n,i,x,j=0,stk=0;
    assert(fscanf(stdin,"%d",&n)>0);
    llu ans=0;

    FOR(i,0,n){
        assert(fscanf(stdin,"%d",&x)>0);
        pii item={.first=x,.second=0};
        pairs[i]=item;
    }
    FOR(i,0,n){
        assert(fscanf(stdin,"%d",&x)>0);
        pii item={.first=x,.second=1};
        pairs[i+n]=item;
    }
    FOR(i,0,n){
        assert(fscanf(stdin,"%d",&C[i])>0);
    }

    HeapSort(pairs,0,2*n,compare_by_pii_asc,swap_item_pii);
    HeapSort(C,0,n,compare_by_int_asc,swap_item_int);
    stk=0,j=0;
    
    FOR(i,0,(2*n)){
        if(pairs[i].second==0){
            Stack[stk]=pairs[i].first;
            stk+=1;
        }
        else{
            int atmost = Stack[stk-1];
            stk-=1;
            intervals[j] = pairs[i].first - atmost;
            j+=1;
        }
    }
    
    HeapSort(intervals,0,n,compare_by_int_asc,swap_item_int);

    FOR(i,0,n){
        llu product = C[n-i-1];
        product = product*intervals[i];
        ans += (product);
    }
    printf("%llu\n",ans);
}


int main(){
    int tt;
    assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--){
        solve();
    }
}
