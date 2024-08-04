#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <math.h>

#define M (int)2e5+9
#define REP(n) for(int i=0;i<n;i++)
int min(int a,int b){return (a<=b)?(a):(b);}
int max(int a,int b){return (a>=b)?(a):(b);}
typedef long long unsigned llu;
typedef long long int lli ;

// https://wcipeg.com/wiki/Size_Balanced_Tree
// https://www.scribd.com/document/3072015/10-%E9%99%88%E5%90%AF%E5%B3%B0-Size-Balanced-Tree

typedef struct KeyValuePair{
    int _key,_value;
}KVP;

typedef struct SizeBalancedTreeNode{
    KVP _data;
    struct SizeBalancedTreeNode* left;
    struct SizeBalancedTreeNode* right;
    int size;
}SBTNode;

typedef int compareSBTNodes_t(SBTNode* first,SBTNode* second);
typedef void swapSBTNodes_t(SBTNode* first,SBTNode* second);

enum Sign{Greater,Lesser,EqualTo,GreaterThanEqTo,LesserThanEqTo,NotEqualTo};

int compareSBTNodes_ii(SBTNode* first,SBTNode* second,Sign sn){
    KVP f1 = first->_data;
    KVP s1 = second->_data;
    bool compared = false;

    switch(sn){
        case 0:
        {
            compared = f1._key > s1.key;
            break;
        } 
        case 1:
        {
            compared = f1._key < s1.key;
            break;
        }
        case 2:
        {
            compared = f1._key == s1.key;
            break;
        } 
        case 3:
        {
            compared = f1._key >= s1.key;
            break;
        }
        case 4:
        {
            compared = f1._key <= s1.key;
            break;
        }
        case 5:
        {
            compared = f1._key != s1.key;
            break;
        }
    }
    return compared; 
} 
/*

    2 properties of size balanced binary tree 
    1)size(T->right) >= size(T->left->left),size(T->left->right)
    2)size(T->left) >= size(T->right->left),size(T->right->right)
    
    case '2:
     o              o(root)           B(new-root)
    / \  left      / \     right     / \ 
   L   R ---->    B   R    ---->    L   O 
  / \            /                 / \   \
 A   B          L                 A   C   R
    /          / \        
   C          A   C      

 case 2:
     o               o(root)              C(new-root)
    / \   right     / \     left         / \
   L   R  ---->    L   C    ---->       o   R  
      / \               \              /   / \
     C   E               R            L   D   E
      \                 / \ 
       D               D   E

*/

void right_rotate(SBTNode* root){
    SBTNode* new_root = root->left;
    root->left = new_root->right;
    new_root->right = root;
    new-root->size = root->size ;
    root->size = root->left->size + root->right->size + 1;
    root = new_root;
    return;
}

void left_rotate(SBTNode* root){
    SBTNode* new_root = root->right;
    root->right = new_root->left;
    new_root->left = root;
    new_root->size = root->size;
    root->size = root->left->size + root->right->size + 1;
    root = new_root;
    /*fixUp parent node  is missing and null handling is missing*/
    return;
}

void maintainT(SBTNode* root,bool flag){
    if(root==NULL){
        return;
    }
    if(flag){ 
        if((root->left!=NULL)&&(root->right!=NULL)){
            if((root->right->left!=NULL)&&((root->left->size)<(root->right->left->size))){
                right_rotate(root->right); // RL case , case 1:
                left_rotate(root);
                // adjust size here 
            }
            if((root->right->right!=NULL)&&((root->left->size)<(root->right->right->size))){
                left_rotate(root); // RR case , case 2:
            }
        }
    }
    else{
        if((root->left!=NULL)&&(root->right!=NULL)){
            if((root->left->left!=NULL)&&((root->right->size)<(root->left->left->size))){
                right_rotate(root); // LL case , case '1:
                // adjust size here 
            }
            if((root->left->right!=NULL)&&((root->right->size)<(root->left->right->size))){
                left_rotate(root->left);
                right_rotate(root); // LR case , case '2:
            }
        }
    }
    maintainT(root->left,FALSE);
    maintainT(root->right,TRUE);
    maintainT(root,TRUE);
    maintainT(root,FALSE);
}

SBTNode select(SBTNode* root,int k_th){
        if(root==NULL){
            return NULL;
        }
        int offset = (root->left!=NULL)?(root->left->size):(0); // 0-indexed for 1-ind , root->left->size+1
        if(k_th==offset){
            return root;
        }
        else if(k_th>offset){
            return select(root->right,k_th-(offset+1)); // 0-indexed, for 1-ind , k_th-offset
        }        
        return select(root->left,k_th);
}

SBTNode search(SBTNode* root,SBTNode* search_node,compareSBTNodes_t compfn){
    SBTNode* curr = root;
    while(curr!=NULL){
        if(comfn(curr,search_node,EqualTo)){
            return curr;
        }   
        else if(comfn(curr,search_node,Lesser)){
            return search(curr->right,search_node,compfn);
        }   
        else{
            return search(curr->left,search_node,compfn);
        }
    }
    return NULL;
}


void insert(SBTNode root,SBTNode insert_node,compareSBTNodes_t compfn){
    if(root==NULL){
        root=(SBTNode*)malloc(sizeof SBTNode);
        root->_data = insert_node->_data;
        root->size = 1;
        root->Left = root->right = NULL; 
        return;
    }
    root->size = root->size + 1;
    if(compfn(insert_node->_data,root->data,Lesser)){ // want < have
        insert(root->left,insert_node,compfn);
    }
    else {
        insert(root->right,insert_node,compfn);
    }
    maintainT(root,compfn(insert_node->_data,root->data,GreaterThanEqTo));
}

void delete(SBTNode* root,SBTNode delete_node,compareSBTNodes_t compfn){

}


void solve(void){

    return;
}


int main(int argc,char* argv[]){
    int tt=1;
    double f = 36252535142413.5736545;
    
    //fprintf(stderr,"%.13f %.13f\n",f,last);
    /*assert(fscanf(stdin,"%d",&tt)>0)*/
    while(tt--){
        solve();
    }
    return 0-0;
}

// https://codeforces.com/contest/264/submission/40542899
// treap,multiplicative inverse,red black tree,SplayTree
// SCC,DSU,Bipartite,EulerTour,HamiltonPath,SPF,MST,A*

// https://www.geeksforgeeks.org/problems/numbers-with-same-first-and-last-digit4228/1?itm_source=geeksforgeeks&itm_medium=article&itm_campaign=practice_card

