#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct Stack{
    int value;
    struct Stack* prev; 
}stack;

stack* createNode(int value,stack* prev,bool newly){
    stack* newnode=(stack*)malloc(sizeof(stack));
    newnode->value=value;
    newnode->prev=(newly)?(newnode):(prev);
    return newnode;
}

bool isEmpty(stack** tail){ return (*tail==NULL); }

stack* top(stack** tail) {return (*tail);}

void push(stack** tail,int value){
    stack* newnode=NULL;
    if(*tail==NULL){
        newnode=createNode(value,NULL,true);
    }
    else {
        newnode=createNode(value,*tail,false);
    }
    *tail=newnode;   
}

void pop(stack** tail){
    if(!isEmpty(tail)){
        if((*tail)==(*tail)->prev){
            *tail=NULL;
        }
        else{
            stack* deleted=*tail;
            *tail=deleted->prev;
            //printf("%p %d",*tail,(*tail)->value);
            free(deleted);
        }
    }
}
void test_stack(stack** tail){
    char op='h';
    int x;
    while(true){
        //fflush(stdin);
        if(op>='a' && op<='z')        
            printf("1)For Quit type q/Q\n2)For push type y/Y\n3)For top type t/T\n4)For pop type r/R\n5)For check isempty type e/E\n");
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
                        push(tail,x);
                        break;
                    }
                case 'q':
                    {return;}
                case 't':
                    {
                        if(isEmpty(tail)){
                            printf("Stack is Empty!!\n");       
                        }   
                        else{
                            stack* Top=top(tail);
                            printf("Top number:%d previous:%p current:%p\n",Top->value,Top->prev,Top);
                        }
                        break;
                    }
                case 'r':
                    {
                        if(isEmpty(tail)){ printf("Stack is Empty!!\n"); }
                        else 
                            {pop(tail);}
                        break;
                    }
                case 'e':{
                        printf("Stack is%s Empty!!\n",((!isEmpty(tail))?(" not"):("")));
                        break;
                    }
                default:
                    printf("Invalid Option!! Try again!!\n");    
                    break;
                }
            }
    }
}
int main() {
    // driver code
    stack* tail=NULL;
    //printf("%p\n",tail);    
    test_stack(&tail);
}