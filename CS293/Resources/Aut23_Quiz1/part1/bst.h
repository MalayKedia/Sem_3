#ifndef BST_H
#define BST_H

// DO NOT MODIFY THIS FILE

// Default Node struct

#define PRE_ORDER 0
#define POST_ORDER 1
#define IN_ORDER 2
#define LOAD_FULL_BST 3
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

  int field1 = -1; // Extra fields are available for needed book keeping
  int field2 = -1;
  int field3 = -1;
  int field4 = -1;

  // Constructor
  TreeNode( int key, TreeNode *leftChild, TreeNode *rightChild,
            TreeNode *parent) :
    key(key), left(leftChild), right(rightChild), parent(parent) {}
  void storeTree( ofstream &f );
};



class BST{

public:

  TreeNode *root;

  // result variable is for testing purposes, Do not tamper with it!
  vector<string> result;


  // Constructors!
  BST();
  BST(TreeNode *root);

  // This function prints the BST using ASCII characters using the
  // format:
  //
  //   root
  //       |-- left subtree
  //       |__ right subtree
  //
  // where the left and right subtrees are printed recursively in
  // the same format.
  //
  // We have done this for you! Please see BST.cpp for details
  // You may use this for debugging purposes.
  //
  void printBST(const string& prefix, bool isLeft=false);

  // The three functions below are for evaluation purposes,
  // Do not tamper with them!
  void getBST(const string& prefix, bool isLeft=false);
  void clearResult();
  vector<string> getResult();


  // Return true, if the ticket with given attributes is found, false otherwise
  bool find(int key);



  // ****************************************************************

  void load(int flag, string filename);

  // ****************************************************************
  // Lab problems

  // Problem 1
  bool isBST();

  // Problem 2
  bool rotate(int key);

};

#endif
