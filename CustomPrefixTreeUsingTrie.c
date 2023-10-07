#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct Trie{
    bool isEnding;
    struct Trie* chSet[26];
}Trie;

Trie* createNode(){
    Trie* newnode=(Trie*)malloc(sizeof(Trie));
    int i;
    for(i=0;i<26;i++){
        newnode->chSet[i]=NULL;
    }
    return newnode;
}

void trieInsert(Trie* obj,char* word){
    int i,n=strlen(word);
    Trie* head=obj;
    for(i=0;i<n;i++){
        // head=head->chSet[word[i]-'a'];
        if(head->chSet[word[i]-'a']==NULL)
            head->chSet[word[i]-'a']=createNode();
        if(i == n-1){
            Trie* nd = head->chSet[word[i]-'a'];
            nd->isEnding=true;
        }
        head = head->chSet[word[i]-'a'];
    }
    return;
}

bool isPrefix(Trie* obj,char* prefix){
    int i,n=strlen(prefix);
    Trie* curr=obj;
    for(i=0;i<n;i++){
        curr=curr->chSet[prefix[i]-'a'];
        if(curr==NULL){
            return false;
        }
    }
    return true;
}

bool searchWord(Trie* obj,char* word){
    int i,n=strlen(word);
    Trie* curr=obj;
    for(i=0;i<n;i++){
        curr=curr->chSet[word[i]-'a'];
        if(curr==NULL || (!curr->isEnding && i==n-1)){
            return false;
        }
    }
    return true;
}

void dispose(Trie* obj){
    free(obj);
}
void displayChoices(){
    printf("1)For insert to Trie type y/Y\n2)For checkPrefix type p/P\n3)For searchWord type w/W\n4)for quit q/Q\n");
}
void test_trie(Trie** obj){
    char ch='~';
    while(true){
                if(!isspace(ch))
                    displayChoices();
                ch=getchar();
                ch=tolower(ch);    
                switch(ch){
            case 'y':{
                //std::boolalpha
                char word[277187];
                printf("Enter word you want to insert:");
                scanf("%s",word);
                trieInsert(*obj,word);
                printf("%s\n","Word is inserted into Trie");
                break;    
            }
            case 'p':{
                //std::boolalpha
                char prefix[277187];
                printf("Enter word you want to check if its prefix:");
                scanf("%s",prefix);
                printf("Word is%s a prefix in Trie\n",isPrefix(*obj,prefix)?(""):(" not"));
                break;
            }
            case 'w':{
                char word[277187];
                printf("Enter word you want to check if its present:");
                scanf("%s",word);
                printf("Word is%s present in Trie\n",searchWord(*obj,word)?(""):(" not"));
                break;    
            }
            case 'q': {return;}
            default:{break;}
        }
    }
}

int main(int argc,char * argv[]){
    // read string 
    char input[1981];
    fgets(input,1981,stdin);
    printf("%s\n",input);
    Trie* obj = createNode();
    test_trie(&obj);
    dispose(obj);
}
// output
// [?2004l
// a
// a

// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// y
// Enter word you want to insert:assert
// Word is inserted into Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// w
// Enter word you want to check if its present:asse
// Word is not present in Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// p
// Enter word you want to check if its prefix:asse
// Word is a prefix in Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// y
// Enter word you want to insert:number
// Word is inserted into Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// p
// Enter word you want to check if its prefix:numb
// Word is a prefix in Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// w
// Enter word you want to check if its present:numb
// Word is not present in Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// y
// Enter word you want to insert:numb
// Word is inserted into Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// w
// Enter word you want to check if its present:nim  umb
// Word is present in Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// y
// Enter word you want to insert:nimb
// Word is inserted into Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// w
// Enter word you want to check if its present:nim
// Word is not present in Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
// p
// Enter word you want to check if its prefix:nim
// Word is a prefix in Trie
// 1)For insert to Trie type y/Y
// 2)For checkPrefix type p/P
// 3)For searchWord type w/W
// 4)for quit q/Q
