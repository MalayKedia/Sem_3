#include "huffman-tree.cpp"
#include "huffman-zip.cpp"
#include "lz77.cpp"
#include <sstream>
using std::stringstream;

int main(){
    string infile = "random.txt";
    stringstream ss; ss << ifstream(infile).rdbuf();
    string instr = ss.str(); // the whole file with whitespace as well
    // instr = "aaaabbbb";
    cout << "instr:" << instr.size() << endl;
    tree *huffman_tree;
    string comp1 = deflate_lz77(instr);
    cout << "comp1:" << comp1.size() << endl;
    string comp = deflate(comp1, huffman_tree);
    cout << "comp :" << comp.size() << endl;
    map<char, string> codes; huffman_tree->get_codes(codes);
    for (const auto &[k, v]: codes) {
        cout << '[' << k << ']' << " " << v << endl;
    }
    // cout << "tree:" << endl;
    // huffman_tree->print();
    string reconstruct = inflate(comp, huffman_tree);
    cout << "stag1:" << (reconstruct==comp1) << endl;
    cout << "rec1 :" << reconstruct.size() << endl;
    reconstruct = inflate_lz77(reconstruct);
    cout << "rec  :" << reconstruct.size() << endl;
    ofstream outfile("out.txt");
    outfile << reconstruct;
    cout << (instr == reconstruct ? "Success!" : "Failure!") << endl;

    // add run-length encoding

    // print gain in bits
    cout << "Compression:" << comp.size() << "/" << 8*instr.size() << endl;
    cout << 100.0 * (1 - (double)comp.size() / (8*(double)instr.size())) << "\%\n";
    // cout << "The coding scheme:\n";
    // map<char, string> codes; huffman_tree->get_codes(codes);
    // for (const auto &[k, v]: codes) {
    //     cout << '[' << k << ']' << " " << v << endl;
    // }

    // print gain in bits using just huffman
    string comp2 = deflate(instr, huffman_tree);
    cout << "Compression:" << comp2.size() << "/" << 8*instr.size() << endl;
    cout << 100.0 * (1 - (double)comp2.size() / (8*(double)instr.size())) << "\%\n";
}