#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Queue{int value;struct Queue* next;}queue;

queue* createNode(int value){
    queue* newnode=(queue*)malloc(sizeof(queue));
    newnode->value=value;
    newnode->next=newnode;
    return newnode;
}

bool isEmpty(queue** head){return ((*head)==NULL);}
queue* peek(queue** head){ return (*head)->next;}

void push(queue** head,int value){
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

void test_queue(queue** head){
    char op='h';
    int x;
    while(true){
        //fflush(stdin);
        if(op>='a' && op<='z')        
            printf("1)For Quit type q/Q\n2)For push type y/Y\n3)For front type t/T\n4)For pop type r/R\n5)For check isempty type e/E\n");
        //fflush(stdin);
        op=getchar();
        op=tolower(op);
        fflush(stdin);
        if(op>='a' && op<='z')
        {
            switch(op){
                case 'y':
                    {
                        fflush(stdin);
                        printf("Enter number you want to add:");
                        scanf("%d",&x);
                        push(head,x);
                        break;
                    }
                case 'q':
                    {return;}
                case 't':
                    {
                        if(isEmpty(head)){
                            printf("Queue is Empty!!\n");       
                        }   
                        else{
                            queue* Top=peek(head);
                            printf("Top number:%d front:%p current:%p\n",Top->next->value,Top->next,Top);
                        }
                        break;
                    }
                case 'r':
                    {
                        if(isEmpty(head)){ printf("Queue is Empty!!\n"); }
                        else 
                            {pop(head);}
                        break;
                    }
                case 'e':{
                        printf("Queue is%s Empty!!\n",((!isEmpty(head))?(" not"):("")));
                        break;
                    }
                default:
                    printf("Invalid Option!! Try again!!\n");    
                    break;
                }
            }
    }
}

int main(){
    queue* head=NULL;
    test_queue(&head);
}
