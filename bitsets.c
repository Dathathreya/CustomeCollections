#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define FOR(i,start,end) for(i=start;i<end;i++)
#define ROF(i,start,end) for(i=end-1;i>=start;i--)
#define max(a,b) (a>=b)?(a):(b)
#define min(a,b) (a<=b)?(a):(b)

#define M 1ll<<63
#define N (int)4e5+4
typedef unsigned long long  llu;

llu bitSets[N];
int size,a[N];char* bitStrings[N];

int get(llu bitPos){
    return ((bitSets[bitPos>>6] & (1llu<<(bitPos&63)))!=0);
}
void set(llu bitPos){
    bitSets[bitPos>>6] |=  (1llu<<(bitPos&63));
}

void toggle(llu bitPos){
    bitSets[bitPos>>6] ^=  (1llu<<(bitPos&63));
}

void clear(llu bitPos){
    bitSets[bitPos>>6] &= ~(1llu<<(bitPos&63));
}

int count(){
    int ret=0,i,no_of_blocks=N;
    no_of_blocks += 63;
    no_of_blocks >>= 6;

    for(i=0;bitSets[i]>0;i++){
        if(bitSets[i]){
            llu z=bitSets[i];
            for(;(z>0);z=((z)&(z-1))){
                ret += 1;
            }
        }
    }

    return ret;
}

void andEqual(llu Value){
    int i=0,j=0;
    for(;bitSets[i]>0;i++){
        bitSets[i] &= (Value&63);
        Value >>= 6;
    }

    return;
}

void OrEqual(llu Value){
    int i=0,j=0;
    for(;((bitSets[i]>0)||(Value>0));i++){
        bitSets[i] |= (Value&63);
        Value >>= 6;
    }
    return;     
}

void XorEqual(llu Value){
    int i=0,j=0;
    for(;((bitSets[i]>0)||(Value>0));i++){
        bitSets[i] ^= (Value&63);
        Value >>= 6;
    }
    return;
}

void OrLeftShift(int bitPos){
    int rem = bitPos&63,whole = bitPos>>6,i;
    int no_of_blocks=N;
    no_of_blocks += 63;
    no_of_blocks >>= 6;
    if(rem==0){
        for(i=no_of_blocks-1;i>=whole;i--){
                bitSets[i] |= (bitSets[i-whole]<<rem);
        }
    }
    else{
        for(i=no_of_blocks-1;i>=whole+1;i--){
                bitSets[i] |= (bitSets[i-whole]<<rem);/*take first rem bits of prev block*/
                bitSets[i] |= (bitSets[i-whole-1]>>(64-rem)); /*take last 64-rem bits of immediate prev block of prev*/
            
        }
        bitSets[whole] |= (bitSets[whole-whole]<<rem);
    }
    return;
}

void OrRightShift(int bitPos){
//     shift by 6 digits 

// 00011011110 100011000 
// 11110000000 

// 7 64-7

// 7 57 

// ((bitsets[curr+1]&((1<<rem+1)-1))<<(rem)
return;
}

void toString(){
    int i=0,j=0,z=0;
    int no_of_blocks = N;
    no_of_blocks += 63;
    no_of_blocks >>= 6;
    char bititem[64];
    memset(bititem,'0',sizeof(bititem));
    for(i=0;bitSets[i]>0;i++){
        memset(bititem,'0',sizeof(bititem));
        FOR(j,0,64){
            if(((bitSets[i]>>j)&1)!=0)
                {bititem[j]='1';}
        }
        bitStrings[i]=(char*)malloc(64*sizeof(char));
        memcpy(bitStrings[i],bititem,64*sizeof(char));
    }
    return;
}

void solve(){
    int n,i;
    llu ans=0,total=0;
    assert(fscanf(stdin,"%d",&n)>0);
    memset(a,0,sizeof(a));
    memset(bitSets,0,sizeof(bitSets));
    FOR(i,0,n){
        assert(fscanf(stdin,"%d",&a[i])>0);
    } 
    toString();
    // for(i=0;bitSets[i]>0;i++){
    //     printf("%s\n",bitStrings[i]);
    // }
    set(0); 
    FOR(i,0,(2*n)){
        if(i<n) total += a[i];
        if(get(i)) ans=max(ans,total-i);
        
        if(i<n) OrLeftShift(a[i]);
        clear(i);
    }
    
    printf("%llu\n",ans);
}

int main(int argc, char const *argv[])
{
    int tt=1;
    //assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--){
        solve();
    }
    return 0;
}
