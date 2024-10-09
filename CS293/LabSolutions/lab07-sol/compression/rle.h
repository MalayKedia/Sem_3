#include<iostream>
#include<string>
#include<fstream>
using namespace std;

// RLE compression
class rle
{
private:
    // tell no of bits to read at a time
    int gamma;

public:
    rle(int gamma);
    string compress(string input);
    string decompress(string input);
    // function converting int to gamma-bit binary 
    string f(int i);
    // function converting gamma-bit binary to int
    int g(string i);
};


