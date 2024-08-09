#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>


int max(int a,int b){
    return (a<=b)?(b):(a);
}

typedef struct KeyValuePair{int _Key; int _value; }kvp_ii;

typedef struct AVLNode{kvp_ii _data; int ht; int sz; struct AVLNode* left; struct AVLNode* right; }aNode;

typedef enum Sign{eq,neq,gt,lt,lte,gte} sign_t;

bool compare_kvp_ii(kvp_ii* f,kvp_ii *s,sign_t sgn){
      bool match = false;
      switch(sgn){
          case eq:{
              match = (f->_Key == s->_Key);  
              break;
          }
          case neq:{
              match = (f->_Key != s->_Key);  
              break;
          }
          case gt:{
              match = (f->_Key > s->_Key);  
              break;
          }
          case lt:{
              match = (f->_Key < s->_Key);  
              break;
          }
          case gte:{
              match = (f->_Key >= s->_Key);  
              break;
          }
          case lte:{
              match = (f->_Key <= s->_Key);  
              break;
          }
      }
      return match;     
}

int getHeight(aNode* curr){if(!curr) return -1; return curr->ht; }
int getSize(aNode* curr){if(!curr) return 0; return curr->sz; }

int getBalance(aNode* curr){if(!curr) return 0; return getHeight(curr->left)-getHeight(curr->right); }

void updateHeight(aNode* curr){
    if(!curr) return;
    curr->ht = 1 + max(getHeight(curr->left),getHeight(curr->right));
    return;
}

aNode* newNode(kvp_ii* data){
    aNode* new_node = (aNode*)malloc(sizeof(aNode));
    new_node->_data = *data;
    new_node->ht = 0;
    new_node->sz = 1;
    new_node->left = new_node->right = NULL;   
    return new_node;
}

aNode* rotateRight(aNode* root){
    aNode* new_root = root->left;
    root->left=new_root->right;
    new_root->right = root;

    root->ht = 1 + max(getHeight(root->left) , getHeight(root->right) );
    root->sz = 1 + getSize(root->left) + getSize(root->right) ; 
    new_root->ht = 1 + max(getHeight(new_root->left) , getHeight(new_root->right) );
    new_root->sz = 1 + getSize(new_root->left) + getSize(new_root->right) ; 
    return new_root;
} 

aNode* rotateLeft(aNode* root){
    aNode* new_root = root->right;
    root->right=new_root->left;
    new_root->left = root;

    root->ht = 1 + max(getHeight(root->left) , getHeight(root->right) );
    root->sz = 1 + getSize(root->left) + getSize(root->right) ; 
    new_root->ht = 1 + max(getHeight(new_root->left) , getHeight(new_root->right) );
    new_root->sz = 1 + getSize(new_root->left) + getSize(new_root->right) ; 
    return new_root;
} 

aNode* insert(aNode* root,kvp_ii* new_val){
    if(root==NULL){
        return newNode(new_val);
    }
    if(compare_kvp_ii(&root->_data,new_val,eq)){
        return root;
    }
    else if(compare_kvp_ii(&root->_data,new_val,lt)){
        root->right = insert(root->right,new_val);
    }
    else if(compare_kvp_ii(&root->_data,new_val,gt)){
        root->left = insert(root->left,new_val);
    }
    
    root->ht = 1 + max(getHeight(root->left) , getHeight(root->right) );
    root->sz = 1 + getSize(root->left) + getSize(root->right) ; 

    int balance_factor = getBalance(root);

    if(balance_factor>1 && getBalance(root->left)>=0){ // taller on left subtree (Left should be atleast  Right or more)
        return rotateRight(root);
    }
    if(balance_factor>1 && getBalance(root->left)<0){ // taller on left subtree but rightSide is taller on left subtree strictly
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if(balance_factor<-1 && getBalance(root->right)>0){// taller on right subtree but leftSide is taller on right subtree strictly
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    if(balance_factor<-1 && getBalance(root->right)<=0){// taller on right subtree (Left should be atmost  Right or less)
        return rotateLeft(root);
    }
    return root;
}

bool Search(aNode* root,kvp_ii* data){
        if(compare_kvp_ii(&root->_data,data,eq)){
            return true;
        }
        else if(compare_kvp_ii(&root->_data,data,lt)){
            return Search(root->right,data); 
        }
        else if(compare_kvp_ii(&root->_data,data,gt)){
            return Search(root->left,data); 
        }
    return false;
}

aNode* successor(aNode* curr){
    aNode* answer = curr;
    while(curr!=NULL){
        answer = curr;
        curr = curr->left;
    }
    return answer;
}

aNode* delete(aNode* root,kvp_ii* del_val){
    if(!root){
        return root;
    }
    if(compare_kvp_ii(&root->_data,del_val,lt)){
        root->right = delete(root->right,del_val);
    }
    else if(compare_kvp_ii(&root->_data,del_val,gt)){
        root->left = delete(root->left,del_val);
    }
    else{
        // root-> sz = (root-> sz>=2)?(root-> sz-1):(root->sz); 
        if((root->left==NULL)||(root->right==NULL))
        {
            aNode* NodeToBeSwappedWithRoot = root->left ? root->left : root->right;
            if(!NodeToBeSwappedWithRoot){ // root takes role of null node and becomes null
                NodeToBeSwappedWithRoot = root; // root to be deleted so copied to temp
                root = NULL;
            }   
            else{
                *root = *NodeToBeSwappedWithRoot;
            }
            free(NodeToBeSwappedWithRoot);
        }
        else{
            aNode* succ = successor(root->right);
            root->_data = succ->_data;
            root->right = delete(root->right,&succ->_data);
        }
    }
    
    if(!root){
        return root;
    }

    root->ht = 1 + max(getHeight(root->left) , getHeight(root->right) );
    root->sz = 1 + getSize(root->left) + getSize(root->right) ; 

    int balance_factor = getBalance(root);

    if(balance_factor>1 && getBalance(root->left)>=0){ // taller on left subtree (Left should be atleast  Right or more)
        return rotateRight(root);
    }
    if(balance_factor>1 && getBalance(root->left)<0){ // taller on left subtree but rightSide is taller on left subtree strictly
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if(balance_factor<-1 && getBalance(root->right)>0){// taller on right subtree but leftSide is taller on right subtree strictly
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    if(balance_factor<-1 && getBalance(root->right)<=0){// taller on right subtree (Left should be atmost  Right or less)
        return rotateLeft(root);
    }
    return root;
}

// 5 more functions are pending 1)Select 2)Rank 3)Delete 4)*Begin 5)*End
// select and rank needs size as structure data member in node_type 

void in_order(aNode* curr){
    if(!curr) return;
    
    in_order(curr->left);
    printf("%d ",curr->_data._Key);
    in_order(curr->right);
    return;
}

aNode* select(aNode* curr,int k){
    if(!curr) return 0;
    int StandingPos = 1 + getSize(curr->left) ;
    if(k == StandingPos){
        return curr;
    }
    else if (k < StandingPos){
        return select(curr->left,k);
    }
    else 
        return select(curr->right,k-1-StandingPos);
}

aNode* rank(aNode* curr,kvp_ii cmp_itm){
    if(!curr) return 0;
    int StandingPos = 1 + getSize(curr->left) ;
    if(compare_kvp_ii(&curr->_data,&cmp_itm,gte)){ // have >= want
        return rank(curr->left,cmp_itm);
    }
    else  // have < want
        return StandingPos + rank(curr->right,cmp_itm);
}

aNode* rbegin(aNode* root){if(!root) return NULL; aNode* curr = root; while(curr->right!=NULL){curr = curr->right; } return curr; }

aNode* begin(aNode* root){if(!root) return NULL; aNode* curr = root; while(curr->left!=NULL){curr = curr->left; } return curr; }

int hasNextInt(int* choice){return (scanf("%d",&(*choice))>0); }

void solve(){
    int x,choice;
    aNode* root=NULL;
    kvp_ii item;
    while(hasNextInt(&choice)){
        //printf("inside %d\n",choice);
        switch(choice){
            case 1: {
                scanf("%d",&x);
                item._Key = x;
                item._value = x;
                root=insert(root,&item);
                break;
            }
            case 2: {
                scanf("%d",&x);
                item._Key = x;
                item._value = x;
                root=delete(root,&item);
                break;
            }
            case 3: {
                in_order(root);
                putchar('\n');
                break;
            }
            case 4: {
                break;
            }
            case 7: {
                printf("continue without break goto start\n");
                break;
            }
        }
    
        if(choice==4){
            break;
        }
    }
    return;
}

int main(int argc,char* argv[]){
    int tt=1;
    // assert(fscanf(stdin,"%d",&tt)>0);
    while(tt--){
        solve();
    }
}
