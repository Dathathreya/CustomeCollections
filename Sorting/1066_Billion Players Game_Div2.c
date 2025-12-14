#include <stdio.h>
#include <stdlib.h>

typedef long long unsigned  llu;
int arr[200005];

typedef int (*sorting_comparator_t)(const void* arr1,int,int);
typedef void (*swap_items_t)(const void* arr,int,int);

#define swapGeneric(type,a,b)\
    type c = a;\
    a=b,b=c;

void swap_item_int(const void* arr,int first,int second) {
    int* temp = (int*)arr;swapGeneric(int,temp[first],temp[second]);return;}

int compare_by_int_asc(const void* arr,int first,int second){int* temp=(int*)arr;return temp[first]<=temp[second];}

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

void solve(){
    int n,i,l,r,median=0;
    llu answer=0;
    scanf("%d%d%d",&n,&l,&r);
    for(i=0;i<n;i++){
        scanf("%d",&arr[i]);    
    }
    HeapSort(arr,0,n,compare_by_int_asc,swap_item_int);
    if(n&1){
        median = arr[(n-1)/2];
    }
    else{
        int p1 = arr[(n-1)/2];
        int p2 = arr[(n-1)/2+1];
        median = (p1+p2)/2;
    }
    if(l>median) median=l;
    if(median>r) median=r;
    for(i=0;i<n;i++){
        answer += abs(median-arr[i]);
    }
    printf("%llu\n",answer);
    return;
}

int main()
{
    int tt;
    scanf("%d",&tt);
    while(tt--){
        solve();
    }
    return 0;
}
