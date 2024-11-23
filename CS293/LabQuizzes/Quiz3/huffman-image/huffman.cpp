#include "huffman.h"

// Build Huffman Tree and generate codes
Node* buildHuffmanTree(const unordered_map<string, int>& freq, unordered_map<string, string>& huffmanCodes) {
    vector<Node*> minHeap;

    // Create leaf nodes for each pixel value with a frequency

    // Build the Huffman Tree

    // DO NOT EDIT LINES BELOW

    // Generate Huffman codes from the tree and prints them
    printCodes(minHeap[0], "", huffmanCodes);

    // Return the root of the tree
    return minHeap[0];
}

// Compress the image using the Huffman codes
string compressImage(const vector<vector<string>>& image, unordered_map<string, string>& huffmanCodes) {
}

// Decompress the data using the Huffman Tree
vector<vector<string>> decompressImage(const string& compressedData, Node* root, int rows, int cols, unordered_map<string, string> huffmanCodes) {
}
