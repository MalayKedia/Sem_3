#ifndef TREE_H
#define TREE_H

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE

// Default Node struct

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_TREE 3
#define LOAD_LEFT_SUBTREE 4

#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct TreeNode{
  int key;		// Key
  TreeNode *left;	// Left Child of this Node (NULL, if None)
  TreeNode *right;	// Right Child of this Node (NULL, if None)
  TreeNode *parent;	// The Parent Node, NULL in case of Root

  // Constructor
  TreeNode(int key, TreeNode *leftChild, TreeNode *rightChild, TreeNode *parent) : key(key), left(leftChild), right(rightChild), parent(parent) {}
  void storeTree(ofstream &f );
};



class TREE{

public:

  TreeNode *root;

  // result variable is for testing purposes, Do not tamper with it!
  vector<string> result;


  // Constructors!
  TREE();
  TREE(TreeNode *root);

  // This function prints the TREE using ASCII characters using the
  // format:
  //
  //   root
  //       |-- left subtree
  //       |__ right subtree
  //
  // where the left and right subtrees are printed recursively in
  // the same format.
  //
  // We have done this for you! Please see tree.cpp for details
  // You may use this for debugging purposes.
  //
  void printTREE(const string& prefix, bool isLeft=false);

  // The three functions below are for evaluation purposes,
  // Do not tamper with them!
  void getTREE(const string& prefix, bool isLeft=false);
  void clearResult();
  vector<string> getResult();
  
  // Functions that traverse the TREE in various ways!
  // type can be PRE_ORDER, POST_ORDER or IN_ORDER, which
  // #defined numeric constants defined in tree.cpp
  // This function prints on cout the key of nodes
  // encountered on traversing the TREE in the given traversal order
  void traverse(int typeOfTraversal);


  // ****************************************************************
  // File load and store

  void customStore(string filename);
  void load(int flag, string filename, unordered_map<int, TreeNode*> &key_to_pointer);

  // ****************************************************************
  // Lab exam problems

  TreeNode* findlca(TreeNode* a, TreeNode* b);

};

#endif