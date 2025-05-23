void down_heapify(const void* arr,int root,int size){    // go down 
    int leftChild  = 2*root+1;
    int rightChild = 2*root+2;
    int greatest   = root;
    if((leftChild<size)&&(compfn(arr,greatest,leftChild))){
            //swap_int(&leftChild,&greatest);
            int t = leftChild;leftChild = greatest; greatest = t; 
    }
    if((rightChild<size)&&(compfn(arr,greatest,rightChild))){
            int t = rightChild;rightChild = greatest; greatest = t; 
    }
    if(greatest!=root){
        swapfn(arr,greatest,root);
        down_heapify(arr,greatest,size);
    }
    return;
}
int getParent(int c){ return ((c>0)?((c-1)/2):(0)); }

void up_heapify(const void* arr,int root,int child){  // go up - used  in push a node 
    if((child==0)||(root==child)||(compfn(arr,child,getParent(child)))){
        return;
    }
    else{
        swapfn(arr,child,getParent(child));
        up_heapify(arr,root,(child-1)/2);
    } 
}


#include <stdio.h>
#define N 500004
int _a[N],_b[N];
// question is summation of square of difference between latency of array A and latency of array B at index i with array A and array B having n items total count 
// latA , latB means we can bring down the value of a specific item by 1 (not allowed if its 0) or up by value of 1 for each respective array
// NOTE: latA only allowed on array A , latB only allowed on array B
// later calculate summation of difference between latency of array A and latency of array B at index i with array A and array B having n items total count  after 
// above operations

// n = 3 
// latencyA = [4,6,1]// latencyB = [2,6,2] adjustmentA=4,adjustmentA=3 
// answer: 0 reason: (3-3)^2 + (6-6)^2 + (2-2)^2 

// n = 2
// latencyA = [2,5]// latencyB = [7,8] adjustmentA=1,adjustmentA=2
// answer: 13 reason: (2-5)^2 + (6-8)^2

// n = 3
// latencyA = [15,1,26]// latencyB = [11,4,20] adjustmentA=3,adjustmentA=2
// answer: 22 reason: (14-11)^2 + (1-3)^2 + (24-21)^2 

void getminimumleastlatency(int n,int lata,int latb,int* a,int* b){
    // heapify up and down 
    // print ans 
}

void solve(){
    int lata,latb,n,i;
    scanf("%d %d",&n,&lata,&latb);
    for(i=0;i<n;i++){
        scanf("%d",&_a[i]);    
    }
    for(i=0;i<n;i++){
        scanf("%d",&_b[i]);    
    }
    getminimumleastlatency(n,lata,latb,_a,_b);
    return;
}

int main()
{
    solve();
    return 0;
}
