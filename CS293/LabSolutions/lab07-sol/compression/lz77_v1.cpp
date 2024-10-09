// write the inflate function for lz77 compression.

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

typedef unsigned long ulg;
struct backref{
    ulg offset, length;
    backref(ulg offset, ulg length): offset(offset), length(length){}
    operator string() const{
        return string(1, char(-1)) + to_string(offset) + "," + to_string(length) + string(1, char(-1));
    }
    string encode_backref() const{
        // encode the length using characters -9 to -2
        ulg len = length-3; // 3 is the minimum length
        string res;
        while (len > 0){
            res += char(-9 + len % 8);
            len /= 8;
        }
        return string(1, char(-1)) + bitset<15>(offset).to_string() + bitset<8>(length).to_string() + string(1, char(-1));
    }
};

backref find_longest_match(const string &buf, ulg i, ulg window_size, ulg lookahead_size){
    // find the longest match in the window
    ulg max_length = 0, max_offset = 0;
    for (ulg j = (i>=window_size)?i-window_size:0; j < i; j++){
        ulg ll = i, k = j, length = 0;
        while (ll < buf.size() && ll < i + lookahead_size && buf[ll] == buf[k]){
            // skip backreferences todo
            ll++; k++; length++;
        }
        if (length > max_length){
            max_length = length;
            max_offset = i - j;
        } else if (length == max_length && i - j < max_offset){
            max_offset = i - j; // prefer the smaller offset, as per the spec.
        }
    }
    return backref(max_offset, max_length);
}

string deflate_lz77(const string &infile_str){
    // we assume the string is one-block long.
    string res;
    ulg window_size = 32768, lookahead_size = 258;
    for (ulg i{0}; i < infile_str.size();) {
        auto bref = find_longest_match(infile_str, i, window_size, lookahead_size);
        if (bref.length < 3) {
            res += infile_str[i++];
        } else {
            // convert both to binary and then to string
            // res += '[' + bitset<15>(bref.offset).to_string() + ',' + bitset<8>(bref.length).to_string() + ']';
            res += string(bref);
            i += bref.length;
        }
    }
    return res;
}

string inflate_lz77(const string &compressed){
    cout << "compressed:" << compressed << endl;
    string res;
    for (ulg i{0}; i < compressed.size();) {
        // print trace
        cout << i << " " << compressed[i] << " " << res << endl;
        if (compressed[i] == -1) {
            ulg j = i + 1;
            cout << "ye\n";
            while (compressed[j] != ',') j++, cout << "ye\n";
            ulg offset = stoul(compressed.substr(i+1, j-i-1));
            ulg k = j + 1;
            while (compressed[k] != -1) k++;
            ulg length = stoul(compressed.substr(j+1, k-j-1));
            for (ulg l = 0; l < length; l++) {
                cout << "idx:" << res.size() << ' ' << offset << endl;
                res += res[res.size() - offset]; // reconstruct from backreference
            }
            i = k + 1;
        } else {
            res += compressed[i++];
        }
    } return res;
}
// int main() {
//     // simple test
//     string infile = "random.txt";
//     stringstream ss; ss << ifstream(infile).rdbuf();
//     const string in_str = ss.str();
//     string comp = deflate_lz77(in_str);
//     cout << comp << endl;
//     string reconstruct = inflate_lz77(comp);
//     cout << (reconstruct==in_str) << endl;
//     cout << "Compression:" << comp.size() << "/" << in_str.size() << endl;
// }