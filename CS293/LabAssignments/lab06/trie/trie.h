/*
In this part of the lab, you will be implementing the prefix trie as discussed in class
We will also be using trie to implement an autocomplete feature.

Autocomplete is used to complete the prefix of a word into a complete word.
For instance, suppose our prefix is `ca'. One possible autocomplete is `cat'.
There can be multiple possible autocompletions possible, in which case, you must print all of them.
For instance, autocomplete for a null string is the entire dictionary.
In this part of the lab, you will insert some words into a trie, 
which will be our set of possible words and will implement autocomplete on it.

Note that we will be using ONLY LOWERCASE characters in this part of the lab.

Your goal is to implement all the functions provided below. Write the code in trie.cpp. 
Do NOT modify the header file (trie.h)

Begin by completing the insert, search, isLastNode and getNode functions. 
These will form a basic implementation of a Trie.
Next, implement the autocompletion functions.

Running Instructions
Run make to compile your code
Run make testBasic to test the basic trie properties such as insert and find
Run make testComplete to test the autocomplete features (which will not work without insert and find)

Input Format
First line contains 0 or 1 (0 - basic test, 1 - autocomplete test)
Second line contains integer n
Next n lines contain n words to be inserted
If basic test, next line contains an integer n2, followed by n2 words to be searched
If autocomplete test, next line contains a string to be autocompleted.

Output Format
See outputs folder for the same.

Please test the code on your own.
*/

#include <string>

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (26)

// Converts key current character into index
// use only 'a' through 'z' and lower case
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')

// trie node
struct TrieNode {
	struct TrieNode* children[ALPHABET_SIZE];

	// isWordEnd is true if the node represents
	// end of a word
	bool isWordEnd;
};

class Trie
{
    public:
    TrieNode* root;

    Trie();
    struct TrieNode* getNode(void);
    void insert(struct TrieNode* root, const std::string key);
    bool search(struct TrieNode *root, std::string key);
    bool isLastNode(struct TrieNode* root);
    void suggestionsRec(struct TrieNode* root,
					std::string currPrefix);
    int printAutoSuggestions(TrieNode* root, const std::string query);
};