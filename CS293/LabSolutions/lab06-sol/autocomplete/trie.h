#include <string>
#include <map>
#include <vector>

// Alphabet size (# of symbols)
#define ALPHABET_SIZE (28)
// 0 to 25 for a-z
// 26 for space
// 27 for $

// trie node
struct TrieNode {
	struct TrieNode* children[ALPHABET_SIZE];

	int frequency; // to store the frequency of the string
    // 0 if there is no string ending at this node
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
    std::pair<int,std::vector<std::string>> suggestionsRec(struct TrieNode* root, std::string currPrefix);
    int printAutoSuggestions(TrieNode* root, const std::string query);
    void processContext();
};