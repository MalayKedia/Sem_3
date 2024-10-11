#include<string>
using std::string;

// RLE compression
class rle
{
private:
    // the number of bits to read at a time
    int gamma;
public:
    rle(int gamma=4);
    string compress(string input);
    string decompress(string input);
    // function converting int to gamma-bit binary 
    string f(int i);
    // function converting gamma-bit binary to int
    int g(string i);
};