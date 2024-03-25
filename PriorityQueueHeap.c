// untested code 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define SZ (int)1e5

/*constant prototype declaration*/
typedef int  compfn_t(const void* arr,int fr,int sc); 
typedef void swapfn_t(const void* arr,int fr,int sc); 

// custome types of PriorityQueue  used in custome swap and comparator
typedef struct pair{ 
    int data;
    int pos;
}pair;

pair maxi_nums[SZ];static int pq_size=-1;

void swapPairs(const void* temp,int fr,int sc){ 
    pair* parrays = (pair*)temp;
    pair t        =  parrays[fr] ;
    parrays[fr]   =  parrays[sc] ;
    parrays[sc]   =  t;
}

int comparePairs(const void* temp,int fr,int sc){ 
    pair* parrays = (pair*)temp;
    if(parrays[fr].data==parrays[sc].data) return parrays[fr].pos<parrays[sc].pos;
    return (parrays[fr].data>parrays[sc].data);
}

// used for pop elements in priority queue  
void down_heapify(const void* arr,int root,int sz,compfn_t compfn,swapfn_t swapfn){ 
    int greatest = root;
    int left     = 2*root+1;
    int right    = 2*root+2;
    if(left<sz && compfn(arr,left,greatest)){
        greatest = left;
    }
    if(right<sz && compfn(arr,right,greatest)){
        greatest = right;
    }
    if(greatest!=root){
        swapfn(arr,root,greatest);
        down_heapify(arr,greatest,sz,compfn,swapfn);
    }
}

// used for push elements in priority queue 
void up_heapify(const void* arr,int child,compfn_t compfn,swapfn_t swapfn){
    
    int parent = (child>0)?((child-1)/2):(0);
    
    if((child==parent)||(compfn(arr,parent,child))){
        return;
    }
    else{
        swapfn(arr,parent,child);
        up_heapify(arr,parent,compfn,swapfn);
    }

}

void push_heap(const void* arr,int sz,compfn_t compfn,swapfn_t swapfn){
    up_heapify(arr,sz,compfn,swapfn);
}

void pop_heap(const void* arr,int sz,compfn_t compfn,swapfn_t swapfn){
    swapfn(arr,0,sz); // highest/least element removed from top of heap
    down_heapify(arr,0,sz,compfn,swapfn); // build new highest / least
}

int main()
{
    int ar[]={1,3,-1,-3,5,3,6,7};
    fprintf(stderr,"pushing elements into priority queue\n");
    for(int i=0;i<8;i++){
       pq_size+=1;
       maxi_nums[pq_size].data = ar[i];maxi_nums[pq_size].pos = i;
       push_heap(maxi_nums,pq_size,comparePairs,swapPairs);
       for(int i=0;i<=pq_size;i++){
            printf("(%d,%d)",maxi_nums[i].data,maxi_nums[i].pos);
       }
       printf("\n");
    }
  
    //fprintf(stderr,"popping element from priority queue\n");
    for(int i=0;i<8;i++){
           pop_heap(maxi_nums,pq_size,comparePairs,swapPairs);
           for(int i=0;i<=pq_size;i++){
                printf("(%d,%d)",maxi_nums[i].data,maxi_nums[i].pos);
           }
           printf("\n");
        pq_size-=1;
    }
}

//  https://leetcode.com/problems/sliding-window-maximum/


// pushing elements into priority queue (without considering smallest index with less priority)
// (1,0)
// (3,1)(1,0)
// (3,1)(1,0)(-1,2)
// (3,1)(1,0)(-1,2)(-3,3)
// (5,4)(3,1)(-1,2)(-3,3)(1,0)
// (5,4)(3,1)(3,5)(-3,3)(1,0)(-1,2)
// (6,6)(3,1)(5,4)(-3,3)(1,0)(-1,2)(3,5)
// (7,7)(6,6)(5,4)(3,1)(1,0)(-1,2)(3,5)(-3,3)
// popping elements into priority queue (without considering smallest index with less priority)
// (6,6)(3,1)(5,4)(-3,3)(1,0)(-1,2)(3,5)(7,7)
// (5,4)(3,1)(3,5)(-3,3)(1,0)(-1,2)(6,6)
// (3,5)(3,1)(-1,2)(-3,3)(1,0)(5,4)
// (3,1)(1,0)(-1,2)(-3,3)(3,5)
// (1,0)(-3,3)(-1,2)(3,1)
// (-1,2)(-3,3)(1,0)
// (-3,3)(-1,2)
// (-3,3)

// pushing elements into priority queue (with considering smallest index with less priority)
// (1,0)
// (3,1)(1,0)
// (3,1)(1,0)(-1,2)
// (3,1)(1,0)(-1,2)(-3,3)
// (5,4)(3,1)(-1,2)(-3,3)(1,0)
// (5,4)(3,1)(3,5)(-3,3)(1,0)(-1,2)
// (6,6)(3,1)(5,4)(-3,3)(1,0)(-1,2)(3,5)
// (7,7)(6,6)(5,4)(3,1)(1,0)(-1,2)(3,5)(-3,3)
// popping elements into priority queue (with considering smallest index with less priority)
// (6,6)(3,1)(5,4)(-3,3)(1,0)(-1,2)(3,5)(7,7)
// (5,4)(3,1)(3,5)(-3,3)(1,0)(-1,2)(6,6)
// (3,1)(1,0)(3,5)(-3,3)(-1,2)(5,4)
// (3,5)(1,0)(-1,2)(-3,3)(3,1)
// (1,0)(-3,3)(-1,2)(3,5)
// (-1,2)(-3,3)(1,0)
// (-3,3)(-1,2)
// (-3,3)
