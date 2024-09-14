/*
Problem 3: If at first you don't succeed, trie, trie again. :)

NOTE: WE WILL BE USING ONLY LOWERCASE CHARACTERS (a-z).

Now, let us extend the above to a more non-trivial use case.
Suppose I have a particular prefix for which I desire an autocomplete.
It makes little sense to print all possible autocompletions as the number can be quite large.
Let us setup the basic framework for a smarter algorithm, one that analyses `context'.
Now, the context encapsulates information that can allow us to sort autocompletions according to their relevance.
Hence, we will seek to report only the most relevant autocompletions.

In this problem, let us track the context of every word as the word that precedes the current word.
Hence, we are given a text which tracks the pre-processed text history of the user, found in lorem.txt
Insert each word into the trie, along with its context (which is the word that precedes it).
The user will insert a number n (n > 1) number of words as a query.
You will have to print the recommended autocomplete(s) for the last word in the query.
The last word ends in a #. Hence "ca#"" is the prefix "ca" (obviously a prefix for cats).
The recommended autocomplete(s) for the word are defined as follows:

We define the "score" of an autocomplete to be
the number of times the proposed autocomplete word and the preceding word in the query
appears in the user text history (as governed by lorem.txt).
A proposed autocomplete word is one that has the last word in the query as a prefix.
A recommended autocomplete is one that has the maximum "score".

For instance, suppose we have the query as "I love ca#". The context of the last word is "love".
Analysing lorem.txt, we can see "love cats" and "love anime". But anime is not a valid completion for "ca".
Hence, the recommended autocomplete is "cats".

For sake of completeness, let us represent the null word by "$". 
Hence, the first word is preceded by "$".

Feel free to import your implementations from the other parts and change any file (EXCEPT main.cpp) ONLY for this part.
How you implement this is ENTIRELY upto you.
THE ONLY THING YOU MUST NOT DO IS STORE A COPY OF THE ENTIRE lorem.txt AS A STRING (trying to render the trie useless)
The input file will contain a user query, you will have to print the most recommended autocomplete(s),
each on a new line, in lexicographic order.

RUNNING INSTRUCTIONS
Run make to compile your code
Run make test to test your code

Input format
A query containing the string with the word to be autocompleted at the end.

Output format
Return the recommended autocomplete(s) in lexicographic order
Read main.cpp for the error messages in case no string is recommended.

Some additional points to ponder:
The contextual data allows us to make more accurate suggestions based on user preferences.
This model we build is based on fixed data. 
You can even make the model update itself with each subsequent query if you wish.
Such a model will be able to provide more relevant searches as the user preferences change with time.
Addtionally, you can also try to incorporate different things into context to target a better autocomplete model. 
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
    void processContext();
};