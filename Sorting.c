#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Quick Sorting
typedef void    (*swap_self_t)(const void* arr,int f,int s);
typedef int (*compare_self_t)(const void* arr,int f,int s);

int compare_self_int(const void* arr,int f,int s){
    int* a1 =(int*)arr;
    return (a1[f]<a1[s]);}

void swap_self_int(const void *arr,int f,int s){
    int* a1 =(int*)arr; 
    int t=a1[f];
    a1[f]=a1[s];
    a1[s]=t;
    return;}

int find_pivot(const void* arr,int low,int high,int want){
    int prev = low-1;
    int randPos =  ((rand())%(high-low+1));
    if(randPos<0){
        randPos += (high-low+1);
    }
    randPos += low;
    swapfn(arr,randPos,high);
    for(int curr=low;curr<high;curr++){
        if(compfn(arr,curr,high)){
            prev++;
            swapfn(arr,prev,curr);
        }
    }
    swapfn(arr,prev+1,high);
    return prev+1;
}

int quickSelect(const void* arr,int low,int high,int want){
    if(low>high) return -1;
    int have = find_pivot(arr,low,high,want);
    if(want>have) {return quickSelect(arr,have+1,high,want);}  // less difference means go right
    else if(want<have) {return quickSelect(arr,low,have-1,want);} // more difference means go left
    return have;
}
void QuickSort(const void *arr,int low,int high,swap_self_t swapfn,compare_self_t comparefn){
    if(low>=high) return;
    int pivot = do_partition(arr,low,high,swapfn,comparefn);
    QuickSort(arr,low,pivot-1,swapfn,comparefn);
    QuickSort(arr,pivot+1,high,swapfn,comparefn);
    return;
}

// Merge Sort 
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef void    (*swap_self_t)(const void* arr,int f,int s);
typedef int  (*compare_self_t)(const void* arr,int f,int s);
typedef void         (*swap_t)(const void* arr,const void* temp,int f,int s);

int compare_self_int(const void* arr,int f,int s){
    int* a1 =(int*)arr;
    return (a1[f]<=a1[s]);
}
int min(int a,int b){ return (a<=b)?(a):(b);}
void swap_self_int(const void *arr,int f,int s){
    int* a1 =(int*)arr; 
    int t=a1[f];
    a1[f]=a1[s];
    a1[s]=t;
    return;
}
void swap_int(const void *arr,const void *temp,int f,int s){
    int* a1 =(int*)arr;  // at f  (middle) big
    int* a2 =(int*)temp;  // at s (high)   small or random
    int t = a1[f];
    a1[f] = a2[s]; // small or random
    a2[s] = t;     // big
    return;
}

void merger(const void* arr,const void* temp,int low,int mid,int high,swap_t swapfn,compare_self_t compfn){
    int l=low,h=high,middle=mid,hightemp=high; 
    while((high>=(mid+1))&&(middle>=low)){
        if(compfn(arr,middle,high)){
            swapfn(arr,temp,high--,hightemp--); // copy greatest to temp array and move high to left 
        }
        else{
            swapfn(arr,temp,middle--,hightemp--); // copy greatest to temp array and move high to left 
        }
    }
    while(high>=(mid+1)){
        swapfn(arr,temp,high--,hightemp--); // copy greatest to temp array and move high to left 
    }
    while(middle>=low){
        swapfn(arr,temp,middle--,hightemp--); // copy greatest to temp array and move high to left 
    }
    //  copy sorted list from temp array to ori array 
    for(int curr=l;curr<=h;curr++){
        swapfn(arr,temp,curr,curr); 
    }
    return;
}
// top-down MergeSort with SC:O(N) , TC:(NlogN)
void mergeSort(const void *arr,const void* temp,int low,int high,swap_t swapfn,compare_self_t comparefn){
    if(low>=high) return;
    int mid = low + ((high-low)/2);
    mergeSort(arr,temp,low,mid,swapfn,comparefn);
    mergeSort(arr,temp,mid+1,high,swapfn,comparefn);
    merger(arr,temp,low,mid,high,swapfn,comparefn);
    return;
}

//bottom-up MergeSort with SC:O(N) , TC:(NlogN)
void mergeSortI(const void *arr,const void* temp,int low,int high,swap_t swapfn,compare_self_t comparefn){
    int half = low + (high-low+1)/2,gap;
    for( gap=0;(1<<gap)<=high;gap++){
        for(int curr=low;curr<=high;curr+=(1<<(gap+1))){
            int l = curr;
            int middle = min(curr + (1<<(gap))-1,high) ;
            int h = min(curr + (1<<(gap+1)) -1,high);
            merger(arr,temp,l,middle,h,swapfn,comparefn);    
        }
    }
    // entire slot of 2 ==((1<<(0+1)))
    // [low,low+(1<<(gap=0))-1] , [low+(1<<(gap=0)),low+(1<<(gap=0+1))]
    return;
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    int * ret = (int*)malloc(numsSize*sizeof(int));
    printf("%d\n",numsSize);
    int temp[50004]; /*temp array for sorting*/ // SC:O(N)
    //QuickSort(nums,0,numsSize-1,swap_self_int,compare_self_int);
    mergeSortI(nums,temp,0,numsSize-1,swap_int,compare_self_int);
    memcpy(ret,nums,numsSize*sizeof(int));
    return ret;
}
void solve()
{
  
}
int main()
{
  int tt;
  assert(fscanf(stdin,"%d",&tt));
  while(tt--)
    {
      solve();
    }
}
