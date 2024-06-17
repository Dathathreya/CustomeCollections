
typedef int  (*compare_t)(const void*,const void*); /*Pointer Based Heap or Collection*/
typedef void (*swap_t)   (const void*,const void*); /*Pointer Based Heap or Collection*/
typedef int  (*compare_self_t)(const void*,int left,int right); /*Array Based Heap or Collection*/
typedef void (*swap_self_t)   (const void*,int first,int second); /*Array Based Heap or Collection*/
            typedef long long unsigned llu;
            int maxi_block = 0,size=0;            
            llu bitset[100901];
            int isSet(llu* bs,int number){
                int block = number>>6;   // number / 6 
                int rem   = (number&63); // number % 64
                return ((bs[block] & (1llu<<rem))!=0);
            }
            void OrLeftShiftStrict(llu* bset,int shiftBy){
                  int whole = shiftBy>>6;   // number / 6 
                  int rem   = (shiftBy&63); // number % 64
                  if(rem==0){
                      for(int i=size;i>=whole;i--){
                          if(i-whole<whole){
                               bset[i] |= ((bset[i-whole])<<rem);    
                          }  
                          else if(i-whole==whole){
                              bset[i] |= ((((1llu<<rem)-1)&(bset[i-whole]))<<rem);    
                          }
                          if(bset[i]){
                            if(i>maxi_block) maxi_block=i;   
                          }
                      }
                  }
                  else{
                      if(whole==0){
                          bset[whole] |= ((((1llu<<rem)-1)&(bset[whole-whole]))<<rem);
                          bset[whole+1] |= ((((1llu<<rem)-1)&(bset[whole-whole]))>>(64-rem));
                          if(bset[(whole+1)]){
                            if((whole+1)>maxi_block) maxi_block=(whole+1);   
                          }
                      }   
                      else{
                           for(int i=size;i>=(whole+1);i--){
                              if(i-whole<whole){
                                    bset[i] |= ((bset[i-whole])<<rem);    
                                    bset[i] |= ((bset[i-(whole+1)])>>(64-rem));    
                              }
                              else if(i-whole==whole){
                                  bset[i] |= ((((1llu<<rem)-1)&(bset[i-whole]))<<rem);    
                                  bset[i] |= ((bset[i-(whole+1)])>>(64-rem)); 
                              }
                              else if(i-(whole+1)==whole){
                                  bset[i] |= ((((1llu<<rem)-1)&(bset[i-(whole+1)]))>>(64-rem)); 
                              }
                               if(bset[i]){if(i>maxi_block) maxi_block=i;}
                           }
                           bset[whole] |= ((bset[whole-whole])<<rem);
                      }
                      if(bset[whole]){if(whole>maxi_block) maxi_block=whole;}
                  }  
                 return ; 
            }
            int compare_self_int(const void* arr,int left,int right){
                int* arr1 = (int*)arr;
                return arr1[left] <= arr1[right];
            }

            void swap_self_int(const void* arr,int left,int right){
                int* arr1 = (int*)arr;
                int t = arr1[left];
                arr1[left] = arr1[right];
                arr1[right] = t;
                return ;
            }

            // heap Sort using heap Data Structure
            void heapify(const void* arr,int root,int size,compare_self_t compfn,swap_self_t swapfn){
                int left = (root*2)+1 , right = (root*2)+2,greatest=root;
                if((left<size)&&(compfn(arr,greatest,left))){
                    greatest = left;
                }
                if((right<size)&&(compfn(arr,greatest,right))){
                    greatest = right;
                }
                if(greatest!=root){
                    swapfn(arr,greatest,root);     /* Swap Values at those indices not indices itself */
                    heapify(arr,greatest,size,compfn,swapfn); /* pick larger element and go down and repeat heapify */
                }
            }

            void heapSort(const void* arr,int low,int high,compare_self_t compfn,swap_self_t swapfn){ /* fixed size heap */
                for(int node = low+((high-low)>>1);node>=low;node--){
                    heapify(arr,node,high+1,compfn,swapfn);
                }
                for(int node=high;node>low;node--){
                    swapfn(arr,low,node);
                    heapify(arr,low,node,compfn,swapfn);
                }
                return;
            }

        int maxTotalReward(int* rewardValues, int rewardValuesSize) {
                int n = rewardValuesSize;
                heapSort(rewardValues,0,n-1,compare_self_int,swap_self_int);
                memset(bitset,0,sizeof(bitset));
                int i=0,maxi=0,sum = 2*rewardValues[n-1]-1;
                bitset[0] = 1;
                maxi_block = 0;
                size = (sum+63)>>6;
                for(i=0;i<n;i++){
                   OrLeftShiftStrict(bitset,rewardValues[i]); 
                }
                for(int bit=63;bit>=0;bit--){
                      if(isSet(bitset,maxi_block*64 + bit))  
                        return maxi_block*64 + bit;
                }
                return 0;   
        }
