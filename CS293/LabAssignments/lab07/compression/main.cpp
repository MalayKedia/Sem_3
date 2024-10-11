#include "huffman-tree.cpp"
#include "huffman-zip.cpp"
#include "lz77.cpp"
#include "rle.cpp"
#include "constants.h"
using std::cout, std::endl, std::fstream;
using std::string, std::ios;

string next_block(fstream &f){
    string block; char c;
    for (int i = 0; i < BLOCK_SIZE; i++){
        if (f.eof()) break;
        f.get(c);
        block += c;
    } return block;
}

int main(int argc, char **argv){
    if (argc != 3) {
        cout << "Usage: " << argv[0] << " <input-file> <part>" << endl;
        return 1;
    }
    string infile = argv[1];
    fstream inf(infile);

    string block, comp, recon;
    ulg insz = 0, outsz = 0;

    // utilities for compression
    tree *huffman_tree;
    rle rlenc(4);

    int part = atoi(argv[2]);
    bool use_huffman=false, use_lz77=false, use_rle=false;
    switch (part) {
        case 3: use_lz77 = true; // notice the missing break statement. Why is the fall-through useful here?
        case 2: use_huffman = true;
        case 1: use_rle = true;
    }

    while (!inf.eof()) {
        block = next_block(inf);
        insz += block.size();

        // compression
        comp = block;

        if (use_lz77) {
            comp = deflate_lz77(comp);
            fstream out("comps/c1.txt", ios::app); out << comp;
        } 
        
        if (use_huffman) {
            comp = deflate(comp, huffman_tree);
            fstream out("comps/c2.txt", ios::app); out << comp;
        }

        if (use_rle) {
            comp = rlenc.compress(comp);
            fstream out("comps/c3.txt", ios::app); out << comp;
        }

        outsz += comp.size();

        // decompression
        recon = comp;

        if (use_rle) {
            recon = rlenc.decompress(recon);
            fstream out("decomps/d1.txt", ios::app); out << recon;
        }

        if (use_huffman) {
            recon = inflate(recon, huffman_tree);
            fstream out("decomps/d2.txt", ios::app); out << recon;
        }

        if (use_lz77) {
            recon = inflate_lz77(recon);
            fstream out("decomps/d3.txt", ios::app); out << recon;
        }

        cout << (block == recon ? "Success!" : "Failure!") << endl;
    }
    // print gain in bits
    if (part != 1) cout << "Ratio of final/original: " << outsz << "/" << 8*insz << " = " << 100.0 * ((double)outsz / (8*(double)insz)) << "\%\n";
    else cout << "Ratio of final/original: " << outsz << "/" << insz << " = " << 100.0 * ((double)outsz / ((double)insz)) << "\%\n";
}