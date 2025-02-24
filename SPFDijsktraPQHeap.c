#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#define N ((int)1e4)
typedef int  compfn_t(const void* arr,int fr,int sc); 
typedef void swapfn_t(const void* arr,int fr,int sc); 

typedef struct pair{ 
    int data;
    int pos;
}pair;

pair maxi_nums[N];bool pms[N];int vis[N]; static int pq_size=-1;

void swapPairs(const void* temp,int fr,int sc){ 
    pair* parrays = (pair*)temp;
    pair t        =  parrays[fr] ;
    parrays[fr]   =  parrays[sc] ;
    parrays[sc]   =  t;
}

int comparePairs(const void* temp,int fr,int sc){ 
    pair* parrays = (pair*)temp;
    if(parrays[fr].data==parrays[sc].data) return parrays[fr].pos>parrays[sc].pos;
    return (parrays[fr].data<parrays[sc].data);
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
void push_h(int sum,int value){
    pq_size+=1;
    maxi_nums[pq_size].data = sum;maxi_nums[pq_size].pos = value;
    push_heap(maxi_nums,pq_size,comparePairs,swapPairs);
    return;
}    
void pop_h(){
    pop_heap(maxi_nums,pq_size,comparePairs,swapPairs);
    pq_size-=1;
}
int top(bool which){
    if(pq_size>=0){
        return ((!which)?(maxi_nums[0].data):(maxi_nums[0].pos));
    }
    return -1;
}
void init(){
    pq_size=-1;
    return;
}
void sieve(int z){
        memset(pms,true,sizeof(pms));
        for(int i=1;i<N;i++){
            vis[i]=z;
        }
        pms[0] = false;pms[1] = false;
        int i=0,j=0;
        for(i=2;(i*i)<N;i++){
            if(pms[i])
            {
                for(j=i*i;j<N;j+=i){
                    pms[j] = false;
                }
            }
        }
    }
    int minOperations(int n, int m) {
        sieve(1e9);
        int i=0,j=0,ans=INT_MAX;
        init();
        //priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> qu;
        if((pms[n])||(pms[m])){
            return -1;
        }
        // starting point 
        // push things to my queue only if its improving(minimizing) my answer 
        push_h(n,n);
        while(pq_size>=0){
            int tp = top(1);
            int sc = top(0);
            if(tp==m){
                return sc;
            }
            int pow = 1,prev = 0;
            while(tp>=pow){
                int di=(((tp)%(pow*10))-(prev))/pow;
                prev = ((tp)%(pow*10));
                if(di<9){
                    if((!pms[tp+pow])&&(vis[tp+pow]>(sc+tp+pow)))
                    {
                        vis[tp+pow] = sc+tp+pow;
                        // qu.push({sc+tp+pow,tp+pow});
                        push_h(sc+tp+pow,tp+pow);
                    }
                }
                if(di>0)
                {
                    if((!pms[tp-pow])&&(vis[tp-pow]>(sc+tp-pow)))
                    {
                        vis[tp-pow] = sc+tp-pow;
                       // qu.push({sc+tp-pow,tp-pow});
                         push_h(sc+tp-pow,tp-pow);
                    }
                }
                pow =pow* 10;
            }
            pop_h();
        }
        return ((ans==INT_MAX)?(-1):(ans));
}

int main(){
    printf("%d\n",minOperations(1000,9999));
}
