#include "swap-pairs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void printList(const Node* node) {
    while (node->link != nullptr) {
        cout << node->data << " ";
        node = node->link;
    }

    cout << node->data << endl;
}

void append(Node*& head, int new_data) {
    Node* new_node = new Node(new_data);

    if (head == nullptr) {
        head = new_node;
        return;
    }

    Node* last = head;
    while (last->link != nullptr) {
        last = last->link;
    }
    last->link = new_node;
}

int main() {
    Node* head = nullptr;

    // Open input and output files
    ifstream inputFile("testcases/input_file.txt");
    ofstream outputFile("output.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    streambuf* originalCoutBuffer = cout.rdbuf();
    cout.rdbuf(outputFile.rdbuf());

    // Process each line in the input file to populate the linked list
    string line;
    while (getline(inputFile, line)) {
        head = nullptr;

        stringstream ss(line);
        int value;
        while (ss >> value) {
            append(head, value);
        }

        // Perform the reverse operation
        reverseAdjacentNodes(head);

        // Print the reversed list to output file
        printList(head);
    }

    cout.rdbuf(originalCoutBuffer);

    // Close input and output files
    inputFile.close();
    outputFile.close();

    // Compare the output with the expected output
    ifstream expectedOutputFile("testcases/expected_output_file.txt");
    ifstream actualOutputFile("output.txt");

    if (!expectedOutputFile.is_open() || !actualOutputFile.is_open()) {
        cerr << "Error opening expected or actual output file." << endl;
        return 1;
    }

    string expectedLine, actualLine;
    bool differenceFound = false;

    while (getline(expectedOutputFile, expectedLine) && getline(actualOutputFile, actualLine)) {
        if (expectedLine != actualLine) {
            differenceFound = true;
            cout << "Difference found:" << endl;
            cout << "Expected: " << expectedLine << endl;
            cout << "Actual: " << actualLine << endl;
        }
    }

    if (!differenceFound) {
        cout << "No differences found. Output matches the expected output." << endl;
    }

    // Close expected and actual output files
    expectedOutputFile.close();
    actualOutputFile.close();

    return 0;
}
