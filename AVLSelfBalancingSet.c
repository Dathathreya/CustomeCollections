#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>


int max(int a,int b){
    return (a<=b)?(b):(a);
}

typedef struct KeyValuePair{int _Key; int _value; }kvp_ii;

typedef struct AVLNode{kvp_ii _data; int ht; struct AVLNode* left; struct AVLNode* right; }aNode;

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
	new_node->left = new_node->right = NULL;   
	return new_node;
}

aNode* rotateRight(aNode* root){
    aNode* new_root = root->left;
    root->left=new_root->right;
    new_root->right = root;

    root->ht = 1 + max(getHeight(root->left) , getHeight(root->right) );
    new_root->ht = 1 + max(getHeight(new_root->left) , getHeight(new_root->right) );
  
    return new_root;
} 

aNode* rotateLeft(aNode* root){
    aNode* new_root = root->right;
    root->right=new_root->left;
    new_root->left = root;

    root->ht = 1 + max(getHeight(root->left) , getHeight(root->right) );
    new_root->ht = 1 + max(getHeight(new_root->left) , getHeight(new_root->right) );
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
	while(root!=NULL){
		if(compare_kvp_ii(&root->_data,data,eq)){
            return true;
		}
		else if(compare_kvp_ii(&root->_data,data,lt)){
            return Search(root->right,data); 
		}
        else if(compare_kvp_ii(&root->_data,data,gt)){
            return Search(root->left,data); 
        }
	}
    return false;
}

// 5 more functions are pending 1)Select 2)Rank 3)Delete 4)*Begin 5)*End
// select and rank needs size as structure data member in node_type 

void printNode(aNode* curr){
	
	return;
}

void solve(){
	aNode* root = newNode(&(struct KeyValuePair){10,199});
	root->left  = newNode(&(struct KeyValuePair){11,299});
	root->right = newNode(&(struct KeyValuePair){12,299});
    // anonymous struct and array 
	printf("verdict:%d\n",compare_kvp_ii(&root->left->_data,&root->right->_data,neq));

	return;
}

int main(int argc,char* argv[]){
	int tt=1;
	// assert(fscanf(stdin,"%d",&tt)>0);
	while(tt--){
		solve();
	}
}
