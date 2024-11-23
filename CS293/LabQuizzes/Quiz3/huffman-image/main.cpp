// DO NOT MODIFY THIS FILE
#include "huffman.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>

using namespace std;

// Function to print Huffman codes
void printCodes(Node* root, string str, unordered_map<string, string>& huffmanCodes) {
    if (!root) return;

    // If it's a leaf node
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->hexValue] = str;
    }

    printCodes(root->left, str + "0", huffmanCodes);
    printCodes(root->right, str + "1", huffmanCodes);
}

// Custom function to insert a node into a list (to simulate min-heap behavior)
void insertNode(vector<Node*>& heap, Node* node) {
    heap.push_back(node);
    int i = heap.size() - 1;

    // Sort the vector based on the frequency of nodes (like a min-heap)
    while (i > 0 && heap[i]->freq < heap[i - 1]->freq) {
        swap(heap[i], heap[i - 1]);
        i--;
    }
}

// Custom function to extract the minimum node from the list
Node* extractMin(vector<Node*>& heap) {
    Node* minNode = heap.front();
    heap.erase(heap.begin());
    return minNode;
}


// Function to write compressed binary data to a file (as text)
void writeCompressedDataToFile(const string& filename, const string& compressedData) {
    ofstream file(filename);
    
    if (file.is_open()) {
        // Write the compressed data as a string of '0's and '1's
        file << compressedData.length() << "\n";
        file << compressedData;
        file.close();
        //cout << "Compressed data written to " << filename << endl;
    } else {
        cout << "Unable to open the file!" << std::endl;
    }
}

// Function to read matrix from input file in hexadecimal format
vector<vector<string>> readMatrixFromFile(const string& filename, int& rows, int& cols) {
    ifstream file(filename);
    vector<vector<string>> matrix;

    if (file.is_open()) {
        matrix.resize(rows, vector<string>(cols));

        string line;
        for (int i = 0; i < rows && getline(file, line); ++i) {
            istringstream iss(line);
            string hexValue;
            for (int j = 0; j < cols && iss >> hexValue; ++j) {
                matrix[i][j] = hexValue;  // Store the hex string directly
            }
        }

        file.close();
    } else {
        cout << "Unable to open the file!" << endl;
    }

    return matrix;
}

// Function to write the reconstructed image to output file in hexadecimal format
void writeMatrixToFile(const string& filename, const vector<vector<string>>& matrix) {
    ofstream file(filename);

    // Check if the file is open
    if (file.is_open()) {
        for (const auto& row : matrix) {
            for (const string& pixel : row) {
                file << pixel << " ";  // Write as hex string
            }
            file << endl;  // Newline at the end of each row
        }
        file.close();
        //cout << "Reconstructed image written to " << filename << endl;
    } else {
        cout << "Unable to open the file!" << endl;
    }
}

int main() {
    int rows = 28, cols = 28, num_of_testcases = 10;

    for (int ts = 0; ts < num_of_testcases ; ++ts) {
        // Step 1: Read the matrix from input file (hexadecimal format)
        vector<vector<string>> image = readMatrixFromFile("testcases/input/testcase_img"+to_string(ts)+".txt", rows, cols);

        // Step 2: Calculate frequency of each pixel value (hexadecimal)
        unordered_map<string, int> freq;
        for (auto row : image) {
            for (const string& pixel : row) {
                freq[pixel]++;
            }
        }

        // Step 3: Build Huffman Tree and generate Huffman codes
        unordered_map<string, string> huffmanCodes;
        Node* root = buildHuffmanTree(freq, huffmanCodes);

        // Step 4: Compress the image
        string compressedData = compressImage(image, huffmanCodes);
        //cout << "Compressed binary data: " << compressedData << endl;
        writeCompressedDataToFile("testcases/compressed_output/testcase_compressed_img"+to_string(ts)+".txt", compressedData);

        // Step 5: Output Huffman codes
        /*cout << "Huffman codes:" << endl;
        for (auto pair : huffmanCodes) {
            cout << pair.first << " -> " << pair.second << endl;
        }*/

        // Step 6: Decompress the image
        vector<vector<string>> reconstructedImage = decompressImage(compressedData, root, rows, cols, huffmanCodes);

        // Step 7: Output the reconstructed image to file (hexadecimal format)
        writeMatrixToFile("testcases/output/testcase_img"+to_string(ts)+".txt", reconstructedImage);
    }
    
    return 0;
}
