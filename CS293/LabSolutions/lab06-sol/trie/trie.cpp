#include "trie.h"
#include <iostream>

Trie::Trie()
{
	this->root = new TrieNode();
}

// Returns new trie node (initialized to NULLs)
struct TrieNode* Trie::getNode(void)
{
	return this->root;
}

// If not present, inserts key into trie. If the
// key is prefix of trie node, just marks leaf node
void Trie::insert(struct TrieNode* root, const std::string key)
{
	struct TrieNode* ptr = this->root;
	for (char c : key) {
		if (ptr->children[c - 'a'] == NULL) {
			ptr->children[c - 'a'] = new TrieNode();
		}
		ptr = ptr->children[c - 'a'];
	}
	ptr->isWordEnd = true;
}

bool Trie::search(struct TrieNode *root, std::string key)
{
	struct TrieNode* ptr = this->root;
	for (char c : key) {
		if (ptr->children[c - 'a'] == NULL) {
			return false;
		}
		ptr = ptr->children[c - 'a'];
	}
	return ptr->isWordEnd;
}

// Returns 0 if current node has a child
// If all children are NULL, return 1.
bool Trie::isLastNode(struct TrieNode* root)
{
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] != NULL) {
			return false;
		}
	}
	return root->isWordEnd;
}

// Recursive function to print auto-suggestions for given
// node.
void Trie::suggestionsRec(struct TrieNode* root,
					std::string currPrefix)
{
	// found a std::string in Trie with the given prefix
	if (root->isWordEnd) {
		std::cout << currPrefix << std::endl;
	}
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (root->children[i] == NULL) {
			continue;
		}
		suggestionsRec(root->children[i], currPrefix + (char)(i + 'a'));
	}
}

// print suggestions for given query prefix.
int Trie::printAutoSuggestions(TrieNode* root, const std::string query)
{
	struct TrieNode* ptr = this->root;
	for (char c : query) {
		if (ptr->children[c - 'a'] == NULL) {
			return 0;
		}
		ptr = ptr->children[c - 'a'];
	}
	this->suggestionsRec(ptr, query);
	return 1;
}
