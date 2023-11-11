#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <math.h>
#include <limits.h>

#define SZ 1001
#define MX (int)1e8+1
char z[SZ][SZ],t[SZ];
int XX[]={0,0,1,-1};
int YY[]={1,-1,0,0};
char mov[]={'R','L','D','U'};
// up,down,right,Left
typedef struct PairIntInt{int f,s;}pii;
//typedef struct Node{pii p;}nd;
int vis[SZ][SZ],previousStep[SZ][SZ],steps[MX];

//typedef struct QueueNode{pii val;struct QueueNode* next;}qNode;
typedef struct Queue{pii value;struct Queue* next;}queue;

queue* createNode(pii value){
    queue* newnode=(queue*)malloc(sizeof(queue));
    newnode->value=value;
    newnode->next=newnode;
    return newnode;
}

bool isEmpty(queue** head){return ((*head)==NULL);}
queue* front(queue** head){ return (*head)->next;}

void push(queue** head,pii value){
   queue* newnode=NULL;
   newnode=createNode(value);
   if((*head)!=NULL){
       queue* front=(*head)->next;
       (*head)->next = newnode;
       newnode->next = front;
   }
        *head=newnode;
}

void pop(queue** head){
    if(!isEmpty(head)){
        if((*head)==(*head)->next){
            (*head)=NULL;
        }
        else{
            queue* front=(*head)->next;
            queue* new_front= front->next;
            (*head)->next=new_front;
            free(front);
        }
    }
}

// vis array -> tracking visited nodes
// previousSteps -> knowing which step i took to reach current node(des) to commpute src node
// above needs add, subtract to reach or get back to source

void bfs(int n,int m,pii src,pii des){
    int i=0;
    queue* qe=NULL;
    push(&qe,src);
    memset(vis,0,sizeof(vis));
    memset(steps,0,sizeof(steps));
    while(!isEmpty(&qe)){
        pii top=front(&qe)->value;
        vis[top.f][top.s]=true;
        for(i=0;i<4;i++){
            int A=top.f+XX[i];
            int B=top.s+YY[i];
            pii ele;
            ele=top;
            if(A>=0 && B>=0 && A<n && B<m && z[A][B]!='#' && !vis[A][B]){
                ele.f=A;ele.s=B;
                vis[A][B]=true;
                previousStep[A][B]=i;
                push(&qe,ele);
            }
        }
        pop(&qe);
    }
    if(vis[des.f][des.s]){
        int sz=0;
        while(!((des.f==src.f)&&(des.s==src.s))){
            int p=previousStep[des.f][des.s];
            steps[sz++]=p;
            int fr=des.f-XX[p];
            int sc=des.s-YY[p];
            des={.f=fr,.s=sc};
        }
        puts("YES");
        printf("%d\n",sz);
        for(int z=sz-1;z>=0;z--){
            printf("%c",mov[steps[z]]);
        }
    }
    else
        fputs("NO",stdout);
    return;
}

void solve(){
    int n,m,i;assert(fscanf(stdin,"%d %d",&n,&m)>0);
    //cin>>n>>m;
    pii src,des;
    for(i=0;i<n;i++){
        assert(fscanf(stdin,"%s",&z[i])>0);
        for(int j=0;j<m;j++){
            if(z[i][j]=='A'){
                src={.f=i,.s=j};
            }
            if(z[i][j]=='B'){
                des={.f=i,.s=j};
            }
            
        }
    }
    bfs(n,m,src,des);
}

int main(int argc,char* argv[]){
    int tt=1;
    //assert(fscanf(stdin,"%d",&tt)>0);
    while((tt--)>0){
        solve();
    }
}
