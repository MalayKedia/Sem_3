#include "tree.h"

/*
    Alternate recursive solution
*/

TreeNode* lca(TreeNode* a, TreeNode *b, TreeNode *r) {
    if (!r || !a || !b) { // empty tree or node not found
        return nullptr;
    }
    if (a == r || b == r) { // one node is root
        return r;
    }
    TreeNode *left = lca(a, b, r->left), *right = lca(a, b, r->right); // recursive call
    if (left && right) { // both common ancestors
        return r;
    }
    if (left) { // left ancestor exists
        return left;
    }
    return right; // right exists or null
}

// Function which returns lca node of given nodes 'a' and 'b'
TreeNode* TREE::findlca(TreeNode* a, TreeNode* b) {
  // dummy return
  return lca(a,b,root);
}
