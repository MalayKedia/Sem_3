// write some c++ that inflates a compressed string using the huffman tree.
#include <string>
#include <iostream>
#include "huffman-tree.cpp"
#include "constants.cpp"
#include <map>
#include <set>
using namespace std;
typedef unsigned long ulg;

// one run of the automaton starting at index i. returns the word and the index of the next character.
class uncompressor {
    const std::string &compressed;
    const tree *huffman_tree;
    int i = 0;
    const tree *curr;
    std::string res;
public:
    uncompressor(const std::string &compressed, const tree *huffman_tree): compressed(compressed), huffman_tree(huffman_tree), curr(huffman_tree){}
    void inflate() {
        for (;i < compressed.size(); i++){ // read the word
            if (curr->isLeaf()){ // found a word
                res += curr->value;
                curr = huffman_tree;
                // check if it is the escape character
                if (res.back() == -1) {
                    // cout << "res:" << res << endl;
                    restore_backref();
                } i--;
            } else if (compressed[i] == '0') {
                curr = curr->left;
            } else if (compressed[i] == '1') {
                curr = curr->right;
            }
        }
        // get the last word
        if (curr->isLeaf()) res += curr->value;
    }
    std::string get_res() const{
        return res;
    }
    void restore_backref() {
        // res += string(1, -1);
        res += compressed.substr(i, OFFSET_BITS);
        i += OFFSET_BITS;
        res += string(1, -1);
        i++;
        res += compressed.substr(i, LENGTH_BITS);
        i += LENGTH_BITS;
        res += string(1, -1);
        i++;
    }
};

string inflate(const string &compressed, const tree *huffman_tree){
    uncompressor unc(compressed, huffman_tree);
    unc.inflate();
    return unc.get_res();
}

map<char, double> get_freqs(const string &buf) {
    // cout << "buf:" << buf << endl;
    map<char, double> res;
    for (int i = 0; i < buf.size();) {
        if (buf[i]!=-1) res[buf[i++]]++;
        else {
            i += OFFSET_BITS + LENGTH_BITS + 3;
        }
    }
    // add a high frequency to the escape character
    res[-1] = 1<<30;
    return res;
}

string bin(unsigned long n, bool is_offset=false) {
    return is_offset?bitset<15>(n).to_string():bitset<8>(n).to_string();
}

string deflate(const string &buf, tree* &huffman_tree) {
    string res;
    auto freq_map = get_freqs(buf);
    huffman_tree = huffman_wrapper(freq_map);
    auto codes = map<char, string>();
    huffman_tree->get_codes(codes);
    for (int i = 0; i < buf.size(); i++) {
        if (buf[i] != -1) {
            res += codes[buf[i]];
        } else {
            // leave the backreference as is
            res += codes[-1];
            i++;
            res += buf.substr(i, OFFSET_BITS);
            i += OFFSET_BITS;
            res += codes[-1];
            i++;
            res += buf.substr(i, LENGTH_BITS);
            i += 8;
            res += codes[-1];
        }
    }
    return res;
}