#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

#define N ((int)5e5+300)
typedef struct ln{
    int value;
    struct ln* prev;
}ln;

int max_depth=0;
bool vis[N];int depth[N],prefix[N];
ln mem_store_adj_list[2*N];
ln* adj_list[N];
int count_adj_list = 0;
int _max(int a,int b){
    return ((a>=b)?(a):(b));
}
void add_adj_list(int from,int to){
    ln* new_node = &mem_store_adj_list[count_adj_list++]; 
    new_node->value = to;
    new_node->prev = adj_list[from];
    adj_list[from] = new_node;
}
void init_adj_list(int n){
    count_adj_list = max_depth = 0;
    for(int i=0;i<=n;i++){
        vis[i] = depth[i] = prefix[i] = 0;
        adj_list[i] = NULL;
    }
    return;
}
void dfs(int node,int _depth){
    vis[node] = true;
    depth[node] = _depth;
    max_depth  = _max(max_depth,_depth);
    ln* topNode = adj_list[node];
    while((topNode!=NULL)&&((topNode->value)>0)){
        int nei = topNode->value;
        if(!vis[nei]){
            dfs(nei,_depth+1);
            depth[node] = _max(depth[node],depth[nei]); 
        }
        topNode = topNode->prev;
    }
    if(_depth>1){
        prefix[1]--;
        prefix[_depth]++;
    }
    prefix[depth[node]+1]--;
}
void solve(){
    int n,u,v,i,ans=INT_MIN; // from , to 
    assert(scanf("%d",&n)>0);
    init_adj_list(n);
    for(i=0;i<(n-1);i++){
        assert(scanf("%d%d",&u,&v)>0);
        add_adj_list(u,v);add_adj_list(v,u);
    }
    dfs(1,0);
    int start = 0;
    for(int ip=1;ip<=max_depth;ip++){
        start += prefix[ip];
        ans = _max(start,ans);
    }
    printf("%d\n",-ans);
    return;
}
int main() {
    int tt;
    assert(scanf("%d",&tt)>0);
    while(tt--){
        solve();
    }
    return 0;    
}
