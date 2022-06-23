#include <bits/stdc++.h>
using namespace std;

#define CHAR_SIZE 128

class TrieNode
{
private:
    /* data */
    vector<TrieNode*> arr;
    bool endOfWord;
public:
    TrieNode(/* args */);
    ~TrieNode();
    void insertWord(string);
    bool searchWord(string);
    bool deleteWord(TrieNode*&, string);
    bool haveChildren(TrieNode*);
};

TrieNode::TrieNode(/* args */)
{
    // If we consider only lowercase alphabets
    arr.resize(CHAR_SIZE, NULL);
    endOfWord = false;
}

TrieNode::~TrieNode()
{
}

void TrieNode::insertWord(string s){
    TrieNode* curr = this;
    for(int i = 0; i < s.length(); i++){
        char ch = s[i];
        if(!curr->arr[ch]){
            curr->arr[ch] = new TrieNode();
        }
        curr = curr->arr[ch];
    }

    curr->endOfWord = true;
    return;
}

bool TrieNode::searchWord(string s){
    TrieNode* curr = this;

    for(int i = 0; i < s.length(); i++){
        char ch = s[i];
        if(!curr->arr[ch]){
            return false;
        }
        curr = curr->arr[ch];
    }

    if(curr->endOfWord) return true;
    else return false;
}

bool TrieNode::haveChildren(TrieNode* curr){
    for(int i = 0; i < CHAR_SIZE; i++){
        if(curr->arr[i]){
            return true;
        }
    }
    return false;
}

bool TrieNode::deleteWord(TrieNode*& curr, string s){
    if(!curr){
        //if Trie is empty
        return false;
    }

    if(s.length() > 0){
        char ch = s[0];
        
        //recur for node of the next character. If deleting next char is possible, delete current node if it is non leaf.
        
        if(curr && curr->arr[ch] && deleteWord(curr->arr[ch], s.substr(1)) && curr->endOfWord == false){
            if(!haveChildren(curr)){
                delete curr;
                curr = nullptr;
                return true;
            } else {
                return false;
            }
        }
    }

    if(s.length() == 0 && curr->endOfWord == true){

        //if current node is a leaf node

        if(!haveChildren(curr)){
            //and it does not have any children, simply delete the node and propagate to its parent
            delete curr;
            curr = nullptr;
            return true;
        } else {

            //mark current node as non-leaf node. We do not delete this node as it contains information for other words also.
            curr->endOfWord = false;

            //Do not delete any of its parents as well.
            return false;
        }
    }

    return false;
}