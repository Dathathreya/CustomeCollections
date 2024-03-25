/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

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

int* maxSlidingWindow(int* ar, int numsSize, int k, int* returnSize) {
   // maintain sliding window of size k and  heap of size K 
   // n = 8, 5+3
   // 3+5 
   // 5 -> (0,5),(1,4),(2,3),(3,2),(4,1),(5,0)
   // 6 -> (0,6),(1,5),(2,4),(3,3),(4,2),(5,1),(6,0)
   // 7 -> (0,7),(1,6),(2,5),(3,4),(3,4),(5,2),(5,2),(7,0)
   int n=numsSize;*returnSize=2*((n-k+1)/2)+((n-k)%2==0);int low=0,high=k-1;
   int* arr=(int*)malloc((*returnSize)*sizeof(int)); 
   memset(arr,0,(*returnSize)*sizeof(int));
   pq_size=-1; // reset values correctly for global variables
   for(int i=0;i<k;i++){
       pq_size+=1;
       maxi_nums[pq_size].data = ar[i];maxi_nums[pq_size].pos = i;
       push_heap(maxi_nums,pq_size,comparePairs,swapPairs);
   }
   int i=0;low=1,high=k;
   arr[0]=maxi_nums[0].data;
   while(high<n){
        i+=1;
        pq_size+=1; 
        maxi_nums[pq_size].data = ar[high];  maxi_nums[pq_size].pos = high;
        push_heap(maxi_nums,pq_size,comparePairs,swapPairs);
        while(!(maxi_nums[0].pos>=low)){
            pop_heap(maxi_nums,pq_size,comparePairs,swapPairs);
            pq_size-=1;
        }
        arr[i]=maxi_nums[0].data;
        low+=1;high+=1;
   }
   return arr; 
}
