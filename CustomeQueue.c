#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

typedef struct Queue{
    const void* data;
    struct Queue* next;
}m_queue; // monotonic queue - circular queue

int q_pop(m_queue** tail){
    int removeable=(q_empty(tail)==0);
    if(removeable){
        if((*tail)==((*tail)->next)){
            m_queue* deleteNode = (*tail);
            (*tail)=NULL;
        }
        else{
            m_queue* deleteNode = (*tail)->next;
            (*tail)->next = deleteNode->next;
            free(deleteNode);
        }
    }
    return removeable;
}

void q_push(m_queue** tail,const void* value){
    // add check for memory limit for pushing
    if(q_empty(tail))
    {
        (*tail) = (m_queue*)malloc(sizeof(m_queue));
        (*tail)->data = value;
        (*tail)->next = (*tail);
    }
    else{
        m_queue* newnode = (m_queue*)malloc(sizeof(m_queue));
        newnode->data    = value;
        newnode->next    = (*tail)->next;
        (*tail)->next    = newnode; 
        (*tail) = newnode;
    }
}

int q_empty(m_queue** tail){
    return ((*tail)==NULL);
}

int main()
{
    int* value = 45;
    m_queue* sliding_window=NULL;
    q_push(&sliding_window,value);  
    value = 27;
    q_push(&sliding_window,value);  
    value = 90;
    q_push(&sliding_window,value);  
    value = 13;
    q_push(&sliding_window,value);  
    value = 51;
    q_push(&sliding_window,value);  

    while(!q_empty(&sliding_window)){
        printf("%d,",(int*)(sliding_window->next)->data);
        q_pop(&sliding_window);
    }
    printf("%d\n",q_empty(&sliding_window));
}
