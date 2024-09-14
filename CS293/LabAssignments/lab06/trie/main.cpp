#include<iostream>
#include "trie.h"

int main()
{
	// Input keys (use only 'a' through 'z'
	// and lower case)
    int choice;
    std::cin >> choice;

	std::string keys[100];
    std::string searches;
	int n;

    std::cin >> n;

    for (int i = 0;i < n;i++) std::cin >> keys[i];

    Trie* tr = new Trie();
	struct TrieNode *root = tr->getNode();

	// Construct trie
	for (int i = 0; i < n; i++)
		tr->insert(root, keys[i]);

    if(choice)
    {
        std::cin >> searches;
        int comp = tr->printAutoSuggestions(root, searches);

        if (comp == -1)
            std::cout << "No other strings found with this prefix\n";

        else if (comp == 0)
            std::cout << "No string found with this prefix\n";
    }
    else
    {
        // Search for different keys
	    char output[][32] = {"Not present in trie", "Present in trie"};

        int nums;
        std::cin >> nums;
        
        for (int i = 0;i < nums;i++) 
        {
            std::cin >> searches;
            std::cout<<searches<<" --- "<<output[tr->search(root, searches)]<<std::endl;
        }
    }
    
	return 0;
}
