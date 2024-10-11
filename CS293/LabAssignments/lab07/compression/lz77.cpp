#include <string>
#include <iostream>
#include <fstream>
#include <bitset>
#include "constants.h"
using std::string, std::bitset;
typedef unsigned long ulg;

// a struct for the backreference. A casting operator to string that can used (it is not optimal) as encoding is provided for convenience.
struct backref{
    ulg offset, length;
    backref(const ulg &offset, const ulg &length): offset(offset), length(length){}
    operator string() const{
        return encode_backref();
    }
    string encode_backref() const{
        return string(1, -1) + bitset<15>(offset).to_string() + string(1, -1) + bitset<8>(length-3).to_string() + string(1, -1);
    }
};

// find the longest match for buf[i:i+lookahead_size] as a substring in the window buf[max(i-window_size,0):] and return appropriate backreference. Note that the longest match can exceed buf[i], that is, for buf=aaaa the longest match at i = 1 returns (0, 3).
backref find_longest_match(const string &buf, ulg i, ulg window_size, ulg lookahead_size)
{ return backref(0, 0); }

// compress the string using lz77 and return the compressed binary string containing characters and string encodings of backreferences.
string deflate_lz77(const string &infile_str)
{ return ""; }

// decompress the string (contains string encodings of backreferences, etc) using lz77 and return the original string.
string inflate_lz77(const string &compressed)
{ return ""; }