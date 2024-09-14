#include "tree.h"

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE

void TreeNode::storeTree(ofstream &f){
    //adds a -1 if the left branch is being added
    //adds a -2 if any branch is empty
    //if the root is a leaf, adds only the root

    f<< key <<endl;
    if(left==NULL && right==NULL) return;
    f<<"-1"<<endl;
    if(left!=NULL) left->storeTree(f);
    else f<<"-2"<<endl;
    if(right!=NULL) right->storeTree(f);
    else f<<"-2"<<endl;
}

TREE::TREE(){root = NULL;}
TREE::TREE(TreeNode *root){this->root = root;}


// Functions that traverse the TREE in various ways!
// type is one of PRE_ORDER, POST_ORDER or IN_ORDER
// Print on cout the journey codes at nodes of the TREE in the same order as
// they are encountered in the traversal order
// Print one journey code per line

void TREE::traverse(int typeOfTraversal){
    if(root==NULL)return;
    if(typeOfTraversal==0){
        TreeNode* curr = root;
        cout<<"("<<root->key<<")"<<endl;
        
        // traverse as if the left-subtree was the only structure
        root = curr->left;
        traverse(typeOfTraversal);

        // traverse as if the right-subtree was the only structure

        root = curr->right;
        traverse(typeOfTraversal);
        // leave no side-effects after you're done
        root = curr;
    }else if(typeOfTraversal==1){
        TreeNode * curr = root;

        // traverse as if the left-subtree was the only structure
        root = curr->left;
        traverse(typeOfTraversal);


        // traverse as if the right-subtree was the only structure
        root = curr->right;
        traverse(typeOfTraversal);
        
        cout<<"("<<curr->key<<")"<<endl;

        // leave no side-effects after you're done
        root = curr;
        
    }else{
        TreeNode * curr = root;
       
        // traverse as if the left-subtree was the only structure
        root = curr->left;
        traverse(typeOfTraversal);

        cout<<"("<<curr->key<<")"<<endl;
        
        
        // traverse as if the right-subtree was the only structure
        root = curr->right;
        traverse(typeOfTraversal);

        // leave no side-effects after you're done
        root = curr;
    }
}


template <typename T>
class StackNode{
//element of my_stack
public:
    T val;
    StackNode<T>* next;
    StackNode(T t, StackNode<T>* ptr):val{t},next{ptr}{}
};
template <typename T>
class my_stack{
//stack implemented as a linked list
    StackNode<T>* head = NULL;
public:
    bool empty(){ //returns if the stack is empty
        return (head!=NULL);
    }
    void push(T ptr){//adds an element to the top of the stack
        StackNode<T> *temp = head;
        head = new StackNode<T>{ptr, temp};
    }
    void pop(){ //removes the last added element from the stack
        StackNode<T>* temp = head;
        if(head==NULL) throw "Pop called on empty stack";
        head = head->next;
        delete temp;
    }
    T top(){//returns the value of the most recently added element of the stack
        if(head==NULL) throw "Pop called on empty stack";
        return head->val;
    }
};

void TREE::customStore(string filename) { 
    ofstream f(filename);
    root->storeTree(f);
    f.close();
    return;
}

void TREE::load(int flag, string filename, unordered_map<int, TreeNode*> &key_to_pointer) {
    ifstream f{filename};
    my_stack<TreeNode*> S;
    // stack holds pointers to the nodes in which only the left
    // ptr has been assigned to
    int data{0};
    TreeNode* prev{NULL};
    bool isFirstNode{1};
    if(flag==LOAD_LEFT_SUBTREE){
        //ignore the data of the root
        f>>data;
        if(data!=-2){
            f>>data;
            f>>data;
        }
        else return;
    }
    while(f>>data){
        if(data == -1){
            S.push(prev);
            int key;
            f>>key;
            if(key == -2){
                prev->left = NULL;
            }
            else{
                prev->left = new TreeNode{key, NULL, NULL, prev};
                prev = prev->left;
                key_to_pointer[key] = prev;
            }
            continue;
        }
        if(isFirstNode){
            if(data == -2){
                root = NULL;
                break;
            }
            isFirstNode = 0;
            root = new TreeNode{data, NULL, NULL, NULL};
            key_to_pointer[data] = root;
            prev = root;
            continue;
        }
        if(flag==LOAD_LEFT_SUBTREE && S.empty()) break;
        prev = S.top();
        S.pop();
        if(data == -2){
            prev->right = NULL;
            continue;
        }
        prev->right = new TreeNode{data, NULL, NULL, prev};
        prev = prev->right;
        key_to_pointer[data] = prev;
    }
}

// Adapted from Adrian Schneider's code on StackOverflow
void TREE::printTREE(const string& prefix, bool isLeft)
{
    if( root != nullptr )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "|__" );

        // print the value of the node
        cout << root->key << endl;
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        printTREE( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        printTREE( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void TREE::getTREE(const string& prefix,  bool isLeft)
{
    if( root != nullptr )
    {
        result.push_back(prefix);

        result.push_back(isLeft ? "├──" : "└──" );

        // print the value of the node
        result.push_back(to_string(root->key) + "\n");
        TreeNode *curr = root;
        root = root->left;
        // enter the next tree level - left and right branch
        getTREE( prefix + (isLeft ? "│   " : "    "), true);
        root = curr->right;
        getTREE( prefix + (isLeft ? "│   " : "    "), false);
        root = curr;
    }
}

void TREE::clearResult(){
    result.clear();
}

vector<string> TREE::getResult(){
    return result;
}
