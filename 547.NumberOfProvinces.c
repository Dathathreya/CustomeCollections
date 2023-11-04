int visited[201];

typedef struct QueueNode{
    int item;
    struct QueueNode* next;
}qNode;
bool isEmpty(qNode** queue){ return ((*queue)==NULL);}
void assignValue(qNode** queue,int itm){
    (*queue)=(qNode*)malloc(sizeof(qNode));
    (*queue)->next=(*queue);
    (*queue)->item=itm;
    return; //break,continue;
}
 
void push(qNode** queue,int itm){
    if(isEmpty(queue)){ // empty
        assignValue(queue,itm);
    }
    else{
        qNode* newnode=NULL;
        assignValue(&newnode,itm);
        (newnode)->next=(*queue)->next;
        (*queue)->next=(newnode);
        (*queue)=newnode;
    }
}
 
void pop(qNode** queue){
     if(!isEmpty(queue)){
        if((*queue)==(*queue)->next){
            (*queue)=NULL;
        }
        else{
            qNode* deleteNode=(*queue)->next;
            (*queue)->next=(deleteNode)->next;
            (deleteNode)->next=NULL;
            free(deleteNode);
        }   
     } 
     return;   
}
 
qNode* front(qNode** queue){ return (*queue)->next;}
 

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) 
{
    memset(visited,0,sizeof(visited));
    int i=0,j=0,count=0;
    qNode* queue=NULL;
    //printf("connected size: %d\n",isConnectedSize);
    for(i=0;i<isConnectedSize;i++){
        if(!visited[i])
        {
            push(&queue,i);
            while(!isEmpty(&queue))
            {
                qNode* top=front(&queue);
                int src=top->item;
                visited[src]=true;
                for(j=0;j<isConnectedSize;j++){
                    if(isConnected[src][j] && src!=j && !visited[j])
                    {
                          push(&queue,j);
                    }
                }
                pop(&queue);
            }
            count+=1;
        }   
    }
    return count;
}
