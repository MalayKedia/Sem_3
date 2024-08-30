#include <bits/stdc++.h>
#include "tree.h"

using namespace std;

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE

vector<string> parse;

void split (string str, char seperator) {
    parse.clear();
    unsigned i = 0;
    int startIndex = 0, endIndex = 0;
    while ( i <= str.length() ) {
      if (str[i] == seperator || i == str.length()) {
        endIndex = i;
        parse.push_back(str.substr(startIndex,endIndex-startIndex));
        startIndex = endIndex + 1;
      }
      i++;
    }
}

int main(int argc, char **argv) {
  // a map from keys to pointer of their nodes
  unordered_map<int, TreeNode*> key_to_pointer; 

  if( argc < 2 ||
      (argv[1][0] != '0' && argv[1][0] != '1') ) {
    cout<<"Give mode of operation:\n 0 for interactive testing \n"
      " 1 for testing findlca \n"
      <<endl;
    return 1;
  }

  char which = argv[1][0];
  if( which == '1') {
    for(int j = 0; j < 10; j++ ) {
      string fname = "testLCA/tree"+ to_string(j) +".txt";
      TREE *b = new TREE();
      key_to_pointer.clear();
      b->load(LOAD_FULL_TREE, fname, key_to_pointer);
      fname = "testLCA/keys"+ to_string(j) +".txt";
      ifstream f(fname);
      int k1, k2;
      f >> k1 >> k2;
      TreeNode* x = nullptr;
        if(key_to_pointer.find(k1) != key_to_pointer.end()){
          x = key_to_pointer.at(k1);
        }
      TreeNode* y = nullptr;
      if(key_to_pointer.find(k2) != key_to_pointer.end()){
        y = key_to_pointer.at(k2);
      }
      if(TreeNode* ret = b->findlca(x, y)){
        cout << "LCA is: " << ret->key << endl;
      }else{
        cout << "LCA doesn't exist" << endl;
      }
    }
  }else if( which == '0') {
    TREE *b = new TREE();
    string s;
    while(true){
      cout<<">>>";
      getline(cin,s);
      split(s,' ');

      if(parse[0]=="LOAD"){
        auto fname = parse[1];
        b = new TREE();
        cout <<"Loading: "<< fname << endl;
        key_to_pointer.clear();
        b->load(LOAD_FULL_TREE, fname, key_to_pointer);
        cout << key_to_pointer.size() << " nodes loaded" << endl;
      }else if(parse[0]=="FINDLCA"){
        int k1 = stoi(parse[1]);
        int k2 = stoi(parse[2]);
        TreeNode* x = nullptr;
        if(key_to_pointer.find(k1) != key_to_pointer.end()){
          x = key_to_pointer.at(k1);
        }
        TreeNode* y = nullptr;
        if(key_to_pointer.find(k2) != key_to_pointer.end()){
          y = key_to_pointer.at(k2);
        }
        if(TreeNode* ret = b->findlca(x, y)){
          cout << "LCA is: " << ret->key << endl;
        }else{
          cout << "LCA doesn't exist" << endl;
        }
      }else if(parse[0]=="PRINT"){
        b->printTREE("");
      }else if(parse[0]=="QUIT"){
        break;
      }else{
        cout<<parse[0] << " is an INVALID REQUEST"<<endl;
      }
    }
  }else {
    cout << "INVALID MODE!";
  }
  return 0;
}