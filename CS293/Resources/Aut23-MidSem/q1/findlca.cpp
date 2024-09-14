#include "tree.h"

// Function which returns lca node of given nodes 'a' and 'b'
TreeNode* TREE::findlca(TreeNode* a, TreeNode* b) {

  if( a == NULL || b == NULL) return NULL;

  TreeNode* pa = a->parent;
  TreeNode* pb = b->parent;

  if(a == b){return b;}
  if(pa == NULL){return a;}
  if(pb == NULL){return b;}
  if(pa == pb){return pa;}
  if(pa == b){return b;}
  if(pb == a){return a;}

  TreeNode* r1 = findlca(a,pb);
  TreeNode* r2 = findlca(pa,b);

  // if(r1 == pa && r2 == pb)
  // {
    // return findlca(pa,pb);
  // }

  if(r2 == pa){return r1;}
  if(r1 == pb){return r2;}
  if(r1 == r2){return r1;}
  if(r1 == a){return a;}
  if(r2 == b){return b;}
    
  // dummy return
  return nullptr;
}