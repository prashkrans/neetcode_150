/* LC#208. NCT1. Implement Trie (Prefix Tree)
*/

// Time Complexity:
// - `insert`: O(m), where m is the length of the word being inserted.
// - `search`: O(m), where m is the length of the word being searched.
// - `startsWith`: O(m), where m is the length of the prefix being checked.

// Space Complexity: O(n * 26), where n is the total number of characters inserted into the Trie.

class Trie {
    struct TrieNode {
        bool isCompleteWord;                             // Indicates if the node represents the end of a word
        vector<TrieNode*> children;                      // Pointers to child nodes for each character
        TrieNode(): isCompleteWord(false), children(vector<TrieNode*>(26, nullptr)) {}
    };
    TrieNode* root;                                      // Root of the Trie
public:
    Trie() {
        root = new TrieNode;                             // Initialize the root node
    }
    
    void insert(string word) {
        TrieNode* curr = root;                           // Start from the root
        for(int i = 0; i < word.size(); i++) {           // Iterate through each character in the word
            int index = word[i] - 'a';                   // Map character to index (0-25)
            if(!curr->children[index])                   // If the child node doesn't exist, create it
                curr->children[index] = new TrieNode;
            curr = curr->children[index];               // Move to the child node
        }
        curr->isCompleteWord = true;                    // Mark the end of the word
    }
    
    bool search(string word) {
        TrieNode* curr = root;                           // Start from the root
        for(int i = 0; i < word.size(); i++) {           // Iterate through each character in the word
            int index = word[i] - 'a';                   // Map character to index
            if(!curr->children[index]) return false;     // If the child node doesn't exist, the word is not in the Trie
            curr = curr->children[index];               // Move to the child node
        }
        return curr->isCompleteWord;                    // Return true if it's the end of a complete word
    }
    
    bool startsWith(string prefix) {
        TrieNode* curr = root;                           // Start from the root
        for(int i = 0; i < prefix.size(); i++) {         // Iterate through each character in the prefix
            int index = prefix[i] - 'a';                 // Map character to index
            if(!curr->children[index]) return false;     // If the child node doesn't exist, the prefix is not in the Trie
            curr = curr->children[index];               // Move to the child node
        }
        return true;                                     // Return true if the prefix exists in the Trie
    }
};

// or, same as above but without comments

class Trie {
    struct TrieNode {
        bool isCompleteWord;
        vector<TrieNode*> children;
        TrieNode(): isCompleteWord(false), children(vector<TrieNode*>(26, nullptr)) {}
    };
    TrieNode* root;
public:
    Trie() {
        root = new TrieNode;
    }
    
    void insert(string word) {
        TrieNode* curr = root;
	    for(int i=0; i<word.size(); i++) {
            int index = word[i] - 'a';
            if(!curr->children[index]) curr->children[index] = new TrieNode;
            curr = curr->children[index];
	    }
	    curr->isCompleteWord = true;
    }
    
    bool search(string word) {
        TrieNode* curr = root;
        for(int i=0; i<word.size(); i++) {
            int index = word[i] - 'a';
            if(!curr->children[index]) return false;
            curr = curr->children[index];
        }
        return curr->isCompleteWord;
    }
    
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for(int i=0; i<prefix.size(); i++) {
            int index = prefix[i] - 'a';
            if(!curr->children[index]) return false;
            curr = curr->children[index];
        }
        return true;
    }
};


// 2. If trie were not a class: [Verified by Claude]
// This is not a solution to LC#208 but a generic implementation of a trie for understanding the concept.

struct TrieNode {
	bool isCompleteWord;
	vector<TrieNode*> children;
	TrieNode(): isCompleteWord(false), children(vector<TrieNode*>(26, nullptr)) {}
};

void insert(TrieNode* root, string word) {
	if(!root) root = new TrieNode;
	TrieNode* curr = root;
	for(int i=0; i<word.size(); i++) {
		int index = word[i] - 'a';
		if(!curr->children[index]) curr->children[index] = new TrieNode;
		curr = curr->children[index];
	}
	curr->isCompleteWord = true;
}

bool search(TrieNode* root, string word) {
	if(!root) return false;
	TrieNode* curr = root;
	for(int i=0; i<word.size(); i++) {
		int index = word[i] - 'a';
		if(!curr->children[index]) return false;
		curr = curr->children[index];
	}
	return curr->isCompleteWord;
}

bool startsWith(TrieNode* root, string prefix) {
    if(!root) return false;
    TrieNode* curr = root;
    for(int i=0; i<prefix.size(); i++) {
        int index = prefix[i] - 'a';
        if(!curr->children[index]) return false;
        curr = curr->children[index];
    }
    return true;
}