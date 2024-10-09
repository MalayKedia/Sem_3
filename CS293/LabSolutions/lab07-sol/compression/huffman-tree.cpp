#ifndef HUFFMAN
#define HUFFMAN
#include <iostream>
#include <map>
#include <set>
using namespace std;

// node
class tree{
public:
    string value = "┐"; // ┐/0/1/character. for now we just use just ┐.
    tree *left = nullptr, *right = nullptr;

    tree(){}
    tree(char value): value(1, value){}
    tree(tree *left): left(left){}
    tree(tree *left, tree *right): left(left), right(right){}
    
    static tree *merge_trees(tree *left, tree *right){
        return new tree(left, right);
    }
    void print(const string &prefix="", bool isLeftChild=false){
        cout << prefix << (prefix==""?"└──":(isLeftChild? "├─0":"└─1"));
        // cout << "value:" << value << "|" << endl;
        if (isLeaf()) cout << "─[" << value << "]" << endl; else cout << value << endl;
        if (left) left->print(prefix + (isLeftChild?"│  ":"   "), true);
        if (right) right->print(prefix + (isLeftChild?"│  ":"   "), false);
    }
    bool isLeaf() const{ return !(left && right); }
    void get_codes(map<char, string> &map_in_progress, const string &prefix="") const{
        if (left){
            if (left->isLeaf()) map_in_progress[left->value[0]] = prefix + "0";
            else left->get_codes(map_in_progress, prefix + "0");
        }
        if (right){ 
            if (right->isLeaf()) map_in_progress[right->value[0]] = prefix + "1";
            else right->get_codes(map_in_progress, prefix + "1");
        }
    }
    ~tree() {
        delete left; delete right;
    }
};

tree *huffman(set<pair<double, tree*> > &subtrees){
    tree *new_subtree = nullptr;
    if (subtrees.size() == 1){
        return subtrees.begin()->second;
    }
    while (subtrees.size() > 1){ // iterative implementation
        // cout << subtrees.size() << endl;
        auto t1 = *subtrees.begin(); subtrees.erase(t1);
        auto t2 = *subtrees.begin(); subtrees.erase(t2);
        new_subtree = tree::merge_trees(t1.second, t2.second);
        subtrees.insert(make_pair(t1.first + t2.first, new_subtree));
    }
    return new_subtree;
}

tree *huffman_wrapper(const map<char, double> &freq_map){
    set<pair<double, tree*> > subtrees; // could instead use a priority queue as well for faster (constant) implementation
    for (const auto &[c, freq]: freq_map){
        subtrees.insert(make_pair(freq, new tree(c)));
    }
    return huffman(subtrees);
}
#endif