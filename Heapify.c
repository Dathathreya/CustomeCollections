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
