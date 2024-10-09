#include "huffman-tree.cpp"
#include "huffman-zip.cpp"
#include "lz77.cpp"
#include "rle.cpp"
#include "constants.cpp"
#include <sstream>
#include <vector>
typedef std::stringstream sst;
using std::cout;

string next_block(fstream &f){
    string block; char c;
    for (int i = 0; i < BLOCK_SIZE; i++){
        if (f.eof()) break;
        f>>c;
        block += c;
    } return block;
}

int main(){
    string infile = "random.txt";
    fstream inf(infile);
    sst ss;

    string block, comp, recon;
    ulg insz = 0, outsz = 0;

    // utilities for compression
    tree *huffman_tree;
    rle rle_(4);

    bool use_huffman=true, use_lz77=true, use_rle=true;
    while (!inf.eof()) {
        block = next_block(inf);
        insz += block.size();

        // compression
        comp = block;

        if (use_lz77) {
            comp = deflate_lz77(comp);
            fstream out("c1.txt", ios::app); out << comp;
        } 
        
        if (use_huffman) {
            comp = deflate(comp, huffman_tree);
            fstream out("c2.txt", ios::app); out << comp;
        }

        if (use_rle) {
            comp = rle_.compress(comp);
            fstream out("c3.txt", ios::app); out << comp;
        }

        outsz += comp.size();

        // decompression
        recon = comp;

        if (use_rle) {
            recon = rle_.decompress(recon);
            fstream out("d1.txt", ios::app); out << recon;
        }

        if (use_huffman) {
            recon = inflate(recon, huffman_tree);
            fstream out("d2.txt", ios::app); out << recon;
        }

        if (use_lz77) {
            recon = inflate_lz77(recon);
            fstream out("d3.txt", ios::app); out << recon;
        }

        cout << (block == recon ? "Success!" : "Failure!") << endl;
    }
    // print gain in bits
    cout << "Compression: " << outsz << "/" << 8*insz << " = " << 100.0 * ((double)outsz / (8*(double)insz)) << "\%\n";
}