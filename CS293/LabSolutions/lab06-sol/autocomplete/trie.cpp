#include "trie.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

// Converts key current character into index
// use only 'a' through 'z' and lower case
int CHAR_TO_INDEX(char c){
    int index = ((int)c - (int)'a');
    if (index < 0) index = 26;
    else if (index > 25) index = 27;
    return index;
}

Trie::Trie()
{
	root = NULL;
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	struct TrieNode* pNode = new TrieNode;
	pNode->frequency = 0;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;
	
	if (root == NULL) root = pNode; // set root to first node created

	return pNode;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	struct TrieNode* pCrawl = root;

	for (int level = 0; level < key.length(); level++) {
		int index = CHAR_TO_INDEX(key[level]);
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	pCrawl->frequency++;
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			return false;

		pCrawl = pCrawl->children[index];
	}

	return (pCrawl->frequency);
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i])
			return 0;
	return 1;
}

// Recursive function to print auto-suggestions for given
// node.
std::pair<int,std::vector<std::string>> Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	std::pair<int,std::vector<std::string>> suggestions = {0,{}}, temp = {};
	
	// found a std::string in Trie with the given prefix
	if (root->frequency){
		suggestions.first = root->frequency;
		suggestions.second.push_back(currPrefix);
	}

	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (root->children[i]) {
			// child node character value
			char child = 'a' + i;
			temp = suggestionsRec(root->children[i], currPrefix + child);
			if (temp.first > suggestions.first)
				suggestions = temp;
			else if (temp.first == suggestions.first)
				suggestions.second.insert(suggestions.second.end(), temp.second.begin(), temp.second.end());
		}
	
	return suggestions;
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	// find last word and it's previous word
	std::istringstream iss(query);
	// get last two words in query
	std::string word, prev_word, last_word;
	while(iss >> word){
		prev_word = last_word;
		last_word = word;
	}
	last_word = last_word.substr(0, last_word.length()-1); // remove # at the end
	std::string prefix = prev_word + " " + last_word;
	struct TrieNode* pCrawl = root;
	for (char c : prefix) {
		int ind = CHAR_TO_INDEX(c);

		// no std::string in the Trie has this prefix
		if (!pCrawl->children[ind])
			return 0;

		pCrawl = pCrawl->children[ind];
	}
	// If prefix is present as a word, but
	// there is no subtree below the last
	// matching node.
	if (isLastNode(pCrawl)) {
		std::cout << last_word << std::endl;
		return -1;
	}
	std::pair<int,std::vector<std::string>> suggestions = suggestionsRec(pCrawl, prefix);
	std::sort(suggestions.second.begin(), suggestions.second.end());
	for (std::string s : suggestions.second){
		std::istringstream iss(s);
		std::string prev_word,word;
		iss>>prev_word>>word;
		std::cout << word << std::endl;
	}
	return 1;
}

void Trie::processContext()
{
	// read words from lorem.txt
	std::ifstream file("lorem.txt");
	std::string str;
	std::getline(file, str, '\0');
	std::istringstream iss(str);
	std::string word, prev_word = "$";
	while (iss >> word) {
		insert(root, prev_word+" "+word); // insert context into trie
		prev_word = word;
	}
}
