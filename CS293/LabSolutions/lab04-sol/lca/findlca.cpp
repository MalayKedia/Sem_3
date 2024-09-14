#include "tree.h"

// Function which returns lca node of given nodes 'a' and 'b'
TreeNode* TREE::findlca(TreeNode* a, TreeNode* b) {

  // make a stack for storing ancestors of 'a'
  stack<TreeNode*> a_ancestors;
  // make a stack for storing ancestors of 'b'
  stack<TreeNode*> b_ancestors;

  // push ancestors of 'a'
  while(a!=nullptr){
    a_ancestors.push(a);
    a = a->parent;
  }
  // push ancestors of 'b'
  while(b!=nullptr){
    b_ancestors.push(b);
    b = b->parent;
  }

  // find lca by popping from both stacks
  TreeNode* lca = nullptr;
  while(!a_ancestors.empty() && !b_ancestors.empty()){
    if(a_ancestors.top() == b_ancestors.top()){
      lca = a_ancestors.top();
      a_ancestors.pop();
      b_ancestors.pop();
    }else{
      break;
    }
  }

  return lca;
}