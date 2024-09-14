#include<iostream>
#include<string.h>

// Part 1 - Dictionary



// In the first part, you will implement the dictionary data structure as
//  you have studied in CS213.
//
// • Implement a dictionary of strings (consider each string is
//   null-terminated, of max length 32, including the null).
//   Use the dictionary to map a string to an integer.
// • The hash code map should use a polynomial accumulation scheme
//   (be careful of overflow)
// • The compression map should use the Fibonacci compression scheme.
// • Use a fixed-length array for the dictionary. Say 64 should be adequate.
// • To resolve hash collisions, use the simple linear probing scheme with
//   appropriate NULL and TOMBSTONE markers (as described in the lecture
//   slides)

// Polynomial Accumulation

// The polynomial rolling hash function is a hash function that uses only
//  multiplications and additions. The following is the function:
//
//         hash(s) = s[0] + s[1]p + s[2]p^2 . . . s[n − 1]p^{n−1}
//
// where p is some positive integer. Use p as 31 or 33.

// Fibonacci Compression

// Used to map a key to an index in the hash table. We use
//
//           h(k) = ⌊ m {kA} ⌋
//
// where k is the key, A is constant between 0 and 1, and
// m is the size of the hash table. In Fibonacci compression,
// we use A as the conjugate of the golden ratio, or (√5−1)/2.
//
// Please write all code for this code in a dictionary.cpp file using
// this header file dictionary.h. Do NOT change the header file.
// You can test your dictionary using dictionaryTest.cpp.



// Running Instructions

// Compile your code by running
//
//    $make exec
//
// Follow the following instructions for testing your dictionary manually.
//
// • Run dictionaryTest.cpp in manual mode.
//
//    $exec 0
//
//   The Interactive part of the Testing can take these instructions
//   – QUIT: end the interactive mode and exit the program
//   – INS <key> <value>: Insert the key-value pair into the Dictionary
//   – DEL <key>: Delete the key from the dictionary if found
//   – FIND <key>: Find and returns the key-value pair
//   Follow the following instructions for testing your dictionary
//   automatically. (These are optional to run)
//
// • Run our test cases on your dictionary
//    $make runtests
//
// • Check distribution of buckets on random inputs.
//    $make random
//
// • Check distribution of buckets on english words.
//    $make english
//
//   The wors from the following URL
//   https://github.com/dwyl/english-words/blob/master/words.txt
//
//   Please use other constants in your implmentation to see
//   the impact on the distribution.
//

#ifndef DICTIONARY_H
#define DICTIONARY_H

// Can change this value for debugging
int DICT_SIZE = 64;

struct Entry {
  // define suitable fields here
  std::string key;
  int value;
};

class Dictionary {
 private:
  int N; // size of array A
  struct Entry *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(std::string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(std::string key);
  
  // Default constructor
  Dictionary(); 

  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  struct Entry *get(std::string key);

  // Put the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(struct Entry e);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(std::string key);
};

#endif
