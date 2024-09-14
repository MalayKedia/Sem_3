#include<iostream>

extern void KMPSearch(char* pat, char* txt);

// Driver code
int main()
{
    const int maxSize = 1000; // Maximum size for character arrays
    
    char pat[maxSize];
    char txt[maxSize];
    std::cin.getline(pat, maxSize); // Read the first character array
    std::cin.getline(txt, maxSize); // Read the second character array

	KMPSearch(pat, txt);
	return 0;
}