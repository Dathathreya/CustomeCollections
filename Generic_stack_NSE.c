// 2 5 1 4 8 3 2 5
//Illustration 
// Pass # 1: Stack(Empty ) Console: 0
        // Update # 1:// Stack ({2,1})
// Pass # 2: Stack({2,1}) 
        // Update # 1:// Stack ({2,1}) Console:1
// Pass # 3: Stack ({2,1},{5,2})         
        // Update # 1:// Stack ({2,1},{1,3}) Console:1
 // Pass #4: Stack ({2,1},{1,3})         
        // Update # 1:// Stack ({2,1},{1,3},{4,4}) Console:3
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)
typedef char* str;


#define pair_struct(type1,type2)\
typedef struct{\
type1 first;\
type2 second;\
}pair_##type1##_##type2;

#define stack_struct(item_type)\
typedef struct stack_##item_type{\
item_type val;\
struct stack_##item_type* prev;\
}stack_##item_type;

#define stack_init(stack,stack_type,element)\
stack=(stack_type*)malloc(1*sizeof(stack_type));stack->val=element;stack->prev=stack;

#define stack_push(stack,stack_type,element)\
do{\
stack_type* new_node=NULL;stack_init(new_node,stack_type,element);if(stack!=NULL) {new_node->prev=stack;}\
stack=new_node;\
}while(0);

#define stack_pop(stack,stack_type)\
do{\
if(stack==stack->prev){stack=NULL;}\
else{stack_type* deleteNode=stack;stack=stack->prev;free(deleteNode);}\
}while(0);

#define stack_top(stack) stack->val
#define stack_isEmpty(stack) (stack==NULL)?(1):(0)

void solve(){
        int n;
        assert(fscanf(stdin,"%d",&n)>0);
        pair_struct(int,int);
        int ans[n],x,i;
        memset(ans,0,sizeof(ans));
        stack_struct(pair_int_int);
        stack_pair_int_int* stk = NULL;
        FOR(i,0,n){
             assert(fscanf(stdin,"%d",&x)>0);           
             int curr=0;
             pair_int_int pii={x,(i+1)};
             while(!stack_isEmpty(stk)){
                  pair_int_int top=stack_top(stk);
                  // Keep Removing Elements until you find smaller element on nearest left
                  if(top.first>=x){
                        stack_pop(stk,stack_pair_int_int);
                  }
                  else{
                       curr=top.second; // take current element index and break
                       break;         
                  }      
             }
             ans[i]=curr;
             stack_push(stk,stack_pair_int_int,pii);   
        }
        FOR(i,0,n){
                printf("%d ",ans[i]);
        }
        printf("\n");
}

int main(int argc,char* argv[]){
        int tt=1;
        //assert(fscanf(stdin,"%d",&tt)>0);
        while((tt--)){
             solve();   
        }
}

// void solve(){
//         pair_struct(int,int);
//         stack_struct(pair_int_int);
//         //stack_pair_int_int* head=(stack_pair_int_int*)malloc(sizeof(stack_pair_int_int));
//         stack_pair_int_int* head=NULL;
//         pair_int_int pii = {.first=23,.second=2272};
//         stack_push(head,stack_pair_int_int,pii);
//         pair_int_int topMost=stack_top(head);
//         printf("%d %d\n",topMost.first,topMost.second);
//         pair_int_int pii1 = {.first=181871,.second=1272};
//         stack_push(head,stack_pair_int_int,pii1);
//         topMost=stack_top(head);
//         printf("%d %d\n",topMost.first,topMost.second);
//         pair_int_int pii2 = {.first=781871,.second=61272};
//         stack_push(head,stack_pair_int_int,pii2);
//         topMost=stack_top(head);
//         printf("%d %d\n",topMost.first,topMost.second);
//         pair_int_int pii3 = {.first=441871,.second=972};
//         stack_push(head,stack_pair_int_int,pii3);
//         topMost=stack_top(head);
//         printf("%d %d\n",topMost.first,topMost.second);
//         stack_pop(head,stack_pair_int_int);//stack_pop(head,stack_pair_int_int);//stack_pop(head,stack_pair_int_int);//stack_pop(head,stack_pair_int_int);
//         printf("%d %d",stack_top(head).first,stack_top(head).second);
//         //printf("%d",stack_isEmpty(head));
// }