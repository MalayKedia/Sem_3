// DO NOT MODIFY THIS FILE
#ifndef HUFFMAN_H
#define HUFFMAN_H

// ************************************************************
// DO NOT CHANGE ANYTHING IN THIS FILE

#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

struct Node {
    std::string hexValue;  // Hexadecimal pixel value (empty for internal nodes)
    int freq;              // Frequency of the pixel value
    Node* left;            // Pointer to left child
    Node* right;           // Pointer to right child
    Node(const std::string& hexValue, int freq) : hexValue(hexValue), freq(freq), left(nullptr), right(nullptr) {} // Constructor for leaf nodes
    Node(int freq) : hexValue(""), freq(freq), left(nullptr), right(nullptr) {} // Constructor for internal nodes
};

// Comparison object for priority queue
struct compare {
    bool operator()(Node* left, Node* right);
};

// Function to print Huffman codes
void printCodes(Node* root, std::string str, std::unordered_map<std::string, std::string>& huffmanCodes);

// Build Huffman Tree and generate codes
Node* buildHuffmanTree(const std::unordered_map<std::string, int>& freq, std::unordered_map<std::string, std::string>& huffmanCodes);

// Compress the image using the Huffman codes
std::string compressImage(const std::vector<std::vector<std::string>>& image, std::unordered_map<std::string, std::string>& huffmanCodes);

// Decompress the data using the Huffman Tree
std::vector<std::vector<std::string>> decompressImage(const std::string& compressedData, Node* root, int rows, int cols,unordered_map<string, string> huffmanCodes);

// Function to write compressed binary data to a file (as text)
void writeCompressedDataToFile(const std::string& filename, const std::string& compressedData);

// Function to read matrix from input
std::vector<std::vector<std::string>> readMatrixFromFile(const std::string& filename, int& rows, int& cols);

// Function to write the reconstructed image to output
void writeMatrixToFile(const std::string& filename, const std::vector<std::vector<std::string>>& matrix);

Node* extractMin(vector<Node*>& heap);
void insertNode(vector<Node*>& heap, Node* node);

#endif // HUFFMAN_H
