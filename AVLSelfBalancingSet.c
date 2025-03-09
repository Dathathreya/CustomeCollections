// https://www.spoj.com/problems/ORDERSET/
// Tested 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <limits.h>

int max(int a,int b){return (a>=b)?(a):(b); }
 
typedef struct KeyValuePair{int _Key; int _value; }kvp_ii;
  
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


typedef struct node
{
    kvp_ii _data;
    int height;
    struct node *left;
    struct node *right;
    int subtree_size;
}node;

node* create_node(kvp_ii* k)
{
    node *child = (node*)malloc(sizeof(node));

    child->_data._Key = k->_Key;
    child->_data._value = k->_value;
    child->height = 1;
    child->left = NULL;
    child->right = NULL;
    child->subtree_size = 1;

    return child;
}

int get_height(node *current_node)
{
    if(current_node == NULL)
        return 0;
    return current_node->height;
}

int get_balance(node *current_node)
{
    if(current_node == NULL)
        return 0;
    return get_height(current_node->left) - get_height(current_node->right);
}

int get_subtree_size(node *current_node)
{
    if(current_node == NULL)
        return 0;
    return current_node->subtree_size;
}

node* left_rotate(node *x)
{
    node *y = x->right;
    node *t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;

    x->subtree_size = get_subtree_size(x->left) + get_subtree_size(x->right) + 1;
    y->subtree_size = get_subtree_size(y->left) + get_subtree_size(y->right) + 1;

    return y;
}

node* right_rotate(node *x)
{
    node *y = x->left;
    node *t2 = y->right;

    y->right = x;
    x->left = t2;

    x->height = max(get_height(x->left), get_height(x->right)) + 1;
    y->height = max(get_height(y->left), get_height(y->right)) + 1;

    x->subtree_size = get_subtree_size(x->left) + get_subtree_size(x->right) + 1;
    y->subtree_size = get_subtree_size(y->left) + get_subtree_size(y->right) + 1;

    return y;
}

node* left_left_case(node *current_node)
{
    return right_rotate(current_node);
}

node* right_right_case(node *current_node)
{
    return left_rotate(current_node);
}

node* left_right_case(node *current_node)
{
    current_node->left = left_rotate(current_node->left);
    return right_rotate(current_node);
}

node* right_left_case(node *current_node)
{
    current_node->right = right_rotate(current_node->right);
    return left_rotate(current_node);
}

node* find_min(node *current_node)
{
    while(current_node->left != NULL)
        current_node = current_node->left;

    return current_node;
}

node* insert_node(node *current_node,kvp_ii* key_)
{
    if(current_node == NULL)
        return create_node(key_);

    if(compare_kvp_ii(key_ , &current_node->_data,lt))
        current_node->left = insert_node(current_node->left, key_);
    else if(compare_kvp_ii(key_ , &current_node->_data,gt))
        current_node->right = insert_node(current_node->right, key_);
    else
        return current_node;

    current_node->height = max(get_height(current_node->left), get_height(current_node->right)) + 1;
    current_node->subtree_size = get_subtree_size(current_node->left) + get_subtree_size(current_node->right) + 1;

    int balance = get_balance(current_node);

    
    if(balance > 1 && get_balance(current_node->left) >= 0)
        return left_left_case(current_node);

    if(balance < -1 && get_balance(current_node->right) <= 0)
        return right_right_case(current_node);

    if(balance > 1 && get_balance(current_node->left) < 0)
        return left_right_case(current_node);

    if(balance < -1 && get_balance(current_node->right) > 0)
        return right_left_case(current_node);

    return current_node;
}

node* delete_node(node *current_node,kvp_ii*  key_)
{
    if(current_node == NULL)
        return current_node;

    if(compare_kvp_ii(key_ , &current_node->_data,lt))
        current_node->left = delete_node(current_node->left, key_);
    else if(compare_kvp_ii(key_ , &current_node->_data,gt))
        current_node->right = delete_node(current_node->right, key_);
    else
    {
        if(current_node->left == NULL || current_node->right == NULL)
        {
            node *temp = NULL;

            if(current_node->left != NULL)
                temp = current_node->left;
            else
                temp = current_node->right;

            if(temp == NULL)
            {
                temp = current_node;
                current_node = NULL;
            }
            else
            {
                current_node->_data = temp->_data;
                current_node->left = temp->left;
                current_node->right = temp->right;
                current_node->height = temp->height;
                current_node->subtree_size = temp->subtree_size;
            }

             free(temp);
        }
        else
        {
            node *temp = find_min(current_node->right);

            current_node->_data = temp->_data;
            current_node->right = delete_node(current_node->right, &temp->_data);
        }
    }

    if(current_node == NULL)
        return current_node;

    current_node->height = max(get_height(current_node->left), get_height(current_node->right)) + 1;
    current_node->subtree_size = get_subtree_size(current_node->left) + get_subtree_size(current_node->right) + 1;

    int balance = get_balance(current_node);

    if(balance > 1 && get_balance(current_node->left) >= 0)
        return left_left_case(current_node);

    if(balance < -1 && get_balance(current_node->right) <= 0)
        return right_right_case(current_node);

    if(balance > 1 && get_balance(current_node->left) < 0)
        return left_right_case(current_node);

    if(balance < -1 && get_balance(current_node->right) > 0)
        return right_left_case(current_node);

    return current_node;
}

int count_smaller(node *current_node, kvp_ii* key_)
{
    if(current_node == NULL)
        return 0;

    int total = 0;

    if(compare_kvp_ii(key_ , &current_node->_data,lt))
    {
        total = count_smaller(current_node->left, key_);
    }
    else if(compare_kvp_ii(key_ , &current_node->_data,gt))
    {
        total = get_subtree_size(current_node->left) + 1;
        total = total + count_smaller(current_node->right, key_);
    }
    else
    {
        total = get_subtree_size(current_node->left);
    }

    return total;
}

node* find_k_smallest(node *current_node, int k)
{
    node* ret = NULL;
    while(current_node != NULL)
    {
        int left_subtree_size = get_subtree_size(current_node->left);

        if(left_subtree_size + 1 == k)
        {
            ret = current_node;
            break;
        }
        else if(left_subtree_size < k)
        {
            k -= left_subtree_size + 1;
            current_node = current_node->right;
        }
        else
        {
            current_node = current_node->left;
        }
    }
    return ret;
}

void delete_tree(node *current_node)
{
    if(current_node == NULL)
    {
        free(current_node);
        return;
    }
    delete_tree(current_node->left);
    delete_tree(current_node->right);
    return;
}

int main()
{
    int q,a;
    char ch[5];
    node *root = NULL;

    scanf("%d",&q);
    while(q--)
    {
        scanf("%s %d",ch,&a);

        if(ch[0] == 'I')
        {
            root = insert_node(root, &(kvp_ii){._Key=a,._value=a});
        }
        else if(ch[0] == 'D')
        {
            root = delete_node(root, &(kvp_ii){._Key=a,._value=a});
        }
        else if(ch[0] == 'K')
        {
            if((root==NULL)||(a > root->subtree_size))
            {
                printf("invalid\n");
            }
            else
            {
                node* nde = find_k_smallest(root, a);
                printf("%d\n",nde->_data._Key);
            }
        }
        else if(ch[0] == 'C')
        {
            a = count_smaller(root, &(kvp_ii){._Key=a,._value=a});
            printf("%d\n",a);
        }
    }

    delete_tree(root);
    return 0;
}
