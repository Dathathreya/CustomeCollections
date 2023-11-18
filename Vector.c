#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <string.h>
#include <float.h>
#include <stddef.h>

#define INITIAL_CAPACITY 4
#define FOR(i,a,b) for(i=a;i<=b-1;i++)
#define ROF(i,a,b) for(i=b-1;i>=a;i--)
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)

#define swap(type,a,b)\
        type* c = a;\
        a=b;\
        b=c;

// standard vector tag for initialization 
#define VECTOR_STRUCT(tag, item_type,vector_name) \
typedef struct tag { \
    size_t size, capacity; \
    item_type *items; \
}vector_name;

#define VECTOR_INIT(identifier,type,vector_name)\
do{\
identifier=(vector_name*)malloc(1*sizeof(vector_name));\
identifier->items=(type*)malloc(INITIAL_CAPACITY*sizeof(type));\
identifier->size=0;\
identifier->capacity=INITIAL_CAPACITY;\
}while(0);        

// #define push_back(identifier,type,element)\
// do{\
// if((identifier->size)>=(identifier->capacity))\
//  identifier->capacity*=2;identifier->items=(type*)realloc(identifier->items,identifier->capacity);\
// identifier->items[identifier->size++]=element;\
// }while(0); printf("%d %d %d\n",identifier->size,identifier->capacity,idx);\

#define empty(identifier) identifier->size==0

#define insert(identifier,type,index,element)\
do{\
int i,idx=index;\
identifier->size+=1;\
if((identifier->size)==(identifier->capacity))\
 identifier->capacity*=2;identifier->items=(type*)realloc((identifier->items),identifier->capacity*sizeof(type));\
ROF(i,(index+1),(identifier->size))\
        identifier->items[i]=identifier->items[i-1];\
identifier->items[idx]=element;}while(0);\

#define erase(identifier,index)\
do{\
int i;\
FOR(i,index,(identifier->size))\
        identifier->items[i]=identifier->items[i+1];\
identifier->size-=1;\
}while(0);

#define pop_back(identifier) erase(identifier,identifier->size-1);
#define push_back(identifier,type,element) insert(identifier,type,identifier->size,element);
#define emplace_back(identifier,type,element) insert(identifier,type,identifier->size,element);

int main(int argc,char* argv[]){
        int i,j;
        // VECTOR_STRUCT(tag,int,vector_int);
        // vector_int* arr=NULL;
        // VECTOR_INIT(arr,int,vector_int);
        // push_back(arr,int,12);
        // push_back(arr,int,23);
        // push_back(arr,int,34);
        // push_back(arr,int,45); //12 23 34 45 56
        // //12 23 34 56 45    
        // insert(arr,int,3,56);
        // push_back(arr,int,78);
        // printf("%d %d\n",arr->size,arr->capacity);
        // //erase(arr,0);
        // FOR(i,0,arr->size){
        //         printf("%d ",arr->items[i]);
        // }
        // printf("\n");
        // pop_back(arr);
        // //push_back(arr,int,56);
        // //push_back(arr,int,67);
        // printf("%d %d\n",arr->size,arr->capacity);
        // FOR(i,0,arr->size){
        //         printf("%d ",arr->items[i]);
        // } 
        //puts("");
        VECTOR_STRUCT(tag2,char*,vector_string);
        vector_string* chSet=NULL;
        VECTOR_INIT(chSet,char*,vector_string);
        push_back(chSet,char*,"first");
        push_back(chSet,char*,"second");
        push_back(chSet,char*,"third");
        push_back(chSet,char*,"fourth");
        push_back(chSet,char*,"fivth");
        push_back(chSet,char*,"sixth");
        push_back(chSet,char*,"hund");
        push_back(chSet,char*,"pink");
        push_back(chSet,char*,"orange");
        push_back(chSet,char*,"latern");
        push_back(chSet,char*,"yellow");
        push_back(chSet,char*,"unary");
        vector_string* chSet2=NULL;
        VECTOR_INIT(chSet2,char*,vector_string);
        push_back(chSet2,char*,"seventh");
        push_back(chSet2,char*,"eighth");
        push_back(chSet2,char*,"ninth");
        push_back(chSet2,char*,"tenth");
        push_back(chSet2,char*,"eleventh");
        push_back(chSet2,char*,"tweleth");
        VECTOR_STRUCT(tag4,vector_string,vector_2d_string);
        vector_2d_string* _2darr=NULL;
        VECTOR_INIT(_2darr,vector_string,vector_2d_string);       
        push_back(_2darr,vector_string,*chSet);
        push_back(_2darr,vector_string,*chSet2);
        printf("\n%d %d\n",_2darr->size,_2darr->capacity);
        FOR(i,0,(_2darr->size)){
                vector_string curr=_2darr->items[i];
                printf("%d %d\n",curr.size,curr.capacity);
                FOR(j,0,curr.size){
                        printf("%s ",curr.items[j]);
                }
                printf("\n");
        }
}
