#include <bits/stdc++.h>
#include "bst.h"

using namespace std;

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

  if( argc < 2 ||
      (argv[1][0] != '0' && argv[1][0] != '1' && argv[1][0] != '2') ) {
    cout<<"Give mode of operation:\n 0 for interactive testing \n"
      " 1 for testing isBST \n"
      " 2 for testing rotate \n"
        <<endl;
    return 1;
  }
  char which = argv[1][0];

  // int i,k,N;
  // if( which == '3') {
  //   for(int j = 0; j < 5; j++ ) {
  //     N = rand() % 100;
  //     BST *b1 = new BST();
  //     set<int> ks;
  //     for(i = 0;i<N;i++){
  //       do{
  //         k = rand() % 1000;
  //       }while(!( ks.find(k)==ks.end()));
  //       b1->insert(k);
  //       ks.insert(k);
  //     }
  //     string fname = "testCorrectBST/test"+ to_string(j) +".ser";
  //     b1->customStore( fname );

  //     BST *b2 = new BST();
  //     b2->load(LOAD_FULL_BST, fname);
  //     b1->getBST("");
  //     b2->getBST("");
  //     if(b1->getResult()==b2->getResult()) {
  //       cout<<"Storing-Loading Works For FULL BST :)"<<endl;
  //     }else{
  //       cout<<"Storing-Loading Doesn't Work :("<<endl;
  //     }
  //   }
  // }else
    if( which == '1') {
    for(int j = 0; j < 10; j++ ) {
      string fname = "testCorrectBST/test"+ to_string(j) +".ser";
      BST *b = new BST();
      b->load(LOAD_FULL_BST, fname);
      if( b->isBST() ) {
        cout << fname << " is a BST!" << endl;
      }else{
        cout << fname << " is not a BST!" << endl;
      }
    }
    for( int j = 0; j < 5; j++ ) {
      string fname = "testWrongBST/test"+ to_string(j) +".ser";
      BST *b = new BST();
      b->load(LOAD_FULL_BST, fname);
      if( b->isBST() ) {
        cout << fname << " is a BST!" << endl;
      }else{
        cout << fname << " is not a BST!" << endl;
      }
    }
  }else if( which == '2') {
      for(unsigned j = 0; j < 10; j++ ) {
        string fname = "testCorrectBST/test"+ to_string(j) +".ser";
        BST *b = new BST();
        b->load(LOAD_FULL_BST, fname);
        auto curr = b->root;
        for( unsigned i = 0; i < j%3; i++ ) {
          if( i%2 ) {
            if(curr->left) curr = curr->left;
          }else{
            if(curr->right) curr = curr->right;
          }
        }
        auto key = curr->key;
        if( b->rotate(key) ) {
          cout << fname << " "<<key << " ROTATION WAS PERFORMED!" << endl;
        }else{
          cout << fname << " "<<key << " NO ROTATION WAS PERFORMED!" << endl;
        }
      }
  }else if( which == '0') {
    BST *b = new BST();
    string s;
    while(true){
      cout<<">>>";
      getline(cin,s);
      split(s,' ');

      if(parse[0]=="FIND"){
        if(b->find(stoi(parse[1]))){
          cout<<"KEY FOUND!"<<endl;
        }else{
          cout<<"KEY NOT FOUND!"<<endl;
        }
      }else if(parse[0]=="LOAD"){
        auto fname = parse[1];
        b = new BST();
        cout <<"Loading: "<< fname << endl;
        b->load(LOAD_FULL_BST, fname);
      }else if(parse[0]=="ISBST"){
        if( b->isBST() ) {
          cout << "YES" << endl;
        }else{
          cout << "NO" << endl;
        }
      }else if(parse[0]=="ROTATE"){
        if( !b->rotate(stoi(parse[1])) ) {
          cout << "NO ROTATION WAS PERFORMED!" << endl;
        }
      }else if(parse[0]=="PRINT"){
        b->printBST("");
      }else if(parse[0]=="QUIT"){
        break;
      }else{
        cout<<parse[0] << "INVALID REQUEST"<<endl;
      }

    }
  }else {
    cout << "INVALID MODE!";
  }
  return 0;
}
