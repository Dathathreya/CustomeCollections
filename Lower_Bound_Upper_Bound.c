// https://codeforces.com/contest/1920/problem/D
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

#define N (int)400010
#define INF (long long )(-1e18)
typedef int compare_bs_t(const void* arr,const void * key,int m,int lesserOrEqualto);

typedef long long unsigned llu;
llu pos[100005]={},arr[100005]={},answer[100005]={};

// arr - maintaining value of number  at last position 
// pos - maintaining last position of number

int compare_by_llu(const void* arr,const void* key,int m,int lesserOrEqualto){
    llu* temp = (llu*)arr;
    llu* Key = (llu*)key; 
    int ret = 0;

    if(lesserOrEqualto){
        ret = (temp[m]<=(*Key)); 
    }
    else{
        ret=(temp[m]<(*Key));
    }
    return ret;
}

int lower_bound(const void* arr,int low,int high,const void* key,compare_bs_t compfn){
    int found=high;
    if(compfn(pos,key,found,1)){
        
    }
    else{
        while(low<=high){
            int mid = (low+high)/2;
            if(compfn(pos,key,mid,0)){
                low = mid+1;
            }
            else{
                found = mid;
                high = mid-1; 
            }
        }
    }
    return found;
}

int upper_bound(const void* arr,int low,int high,const void* key,compare_bs_t compfn){
    int found=high;
    if(compfn(pos,key,found,1)){
        
    }
    else{
        while(low<=high){
            int mid = (low+high)/2;
            if(compfn(pos,key,mid,1)){
                low = mid+1;
            }
            else{
                found = mid;
                high = mid-1; 
            }
        }
    }
    return found;
}

void solve(){
   llu last=0,qi=0;
   int n,q,ch,x;
   assert(fscanf(stdin,"%d %d",&n,&q)>0);
   
   for(int i=1;i<=n;i++){
        assert(fscanf(stdin,"%d %d",&ch,&x)>0);
        if(ch==2){
            arr[i] = arr[i-1]; // propagate last number
            
            // finalProduct = num*cnt 
            // finalProduct/num < cnt 

            if(((2e18)/pos[i-1])<(x+1)){
                pos[i] = 2e18;
            }
            else{
                pos[i] = pos[i-1]+ pos[i-1]*x;
            }
        }
        else{
            arr[i] = x;
            pos[i] = pos[i-1]+1; // increase position of last number
        }

    }
    
    for(int i=1;i<=q;i++){
        assert(fscanf(stdin,"%llu",&qi)>0);  
        // lower bound 
        while(1){
            // leastNumber >= kth_number
            int found = lower_bound(pos,1,n,&qi,compare_by_llu);
            
            // ex. 
            // 1 2 2 3 4 4 
            // 1 2 4 5 6 12

            // case-1: qi=12,5 or anything -> it matches with current number 
            if(pos[found]==qi){
                answer[i] = arr[found];break;
            }
            // case-2: qi=36 -> qi is multiple of previous number (36%6==0) 
            // it ends with this number
            else if((qi%(pos[found-1]))==0){
                // remove previous repeation using modulo
                answer[i] = arr[found-1];break;
            }
            // case-3 : qi=11,
            // transformation : 11%6==5 , do search and find 5
            qi %= pos[found-1];
        }  
    }
    
    for(int i=1;i<=q;i++){
        printf("%llu ",answer[i]);
    }
    printf("\n");

}

int main(){
    int tt;
    assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--)
       solve();
}

// int upperBound(vector<int> &arr, int x, int n){
//     int low=0,high=n-1,ans=n-1;
//     // base case 
//     if(arr[ans]<=x){
//         ans+=1;
//     }
//     else{
//         while(low<=high){
//                     int mid = low + (high-low)/2;
//                     if(arr[mid]<=x){
//                         low = mid+1 ;
//                     } 
//                     else {
//                             ans = mid;
//                             high = mid - 1;
//                     }
//             }
//         }
//         return ans;
// }
