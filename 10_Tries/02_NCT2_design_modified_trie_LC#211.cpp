/**
LC#211. NCT2. Design Add and Search Words Data Structure


Approach:
a. Standard trie insert (0 to 25 characters)
b. Modified trie search (iterative if word[i] != '.' else recursive)

// Running time: O(n)
// Auxiliary space: O(n+t)
// where where n is the length of the string and t is the total number of nodes created in the Trie.
**/

struct node {
    bool isCompleteWord;
    node* children[26];
    node() {
        isCompleteWord = false;
        for(int i=0; i<26; i++) children[i] = nullptr;
    }
};

class WordDictionary {
    node *root;

    bool isWordPresent(string word, int j, node* root) {
        node* curr = root;
        for(int i=j; i<word.size(); i++) {
            char ch = word[i];
            if(ch=='.') {
                for(auto &child: curr->children) {
                    if(child!=nullptr && isWordPresent(word, i+1, child)) return true;
                }
                return false;
            }
            else {
                if(curr->children[ch-'a'] == nullptr) return false;
                curr = curr -> children[ch-'a'];
            }
        }
        return curr->isCompleteWord;
    }

public:
    WordDictionary() {
        root = new node;
    }
    
    void addWord(string word) {             // same insert as a standard trie
        node* curr = root;
        for(int i=0; i<word.size(); i++) {
            int index = word[i] - 'a';
            if(curr -> children[index] == nullptr) curr->children[index] = new node;
            curr = curr -> children[index];
        }
        curr -> isCompleteWord = true;
    }
    
    bool search(string word) {
       return isWordPresent(word, 0, root);
    }
};


// 2. Using a queue: [Verified] but yet to understand
struct node {
    bool isCompleteWord;
    node* children[26];
    node() {
        isCompleteWord = false;
        for(int i=0; i<26; i++) children[i] = nullptr;
    }
};

class WordDictionary {
    node *root;
    
public:
    WordDictionary() {
        root = new node;
    }
    
    void addWord(string word) {             // same insert as a standard trie
        node* curr = root;
        for(int i=0; i<word.size(); i++) {
            int index = word[i] - 'a';
            if(curr->children[index] == nullptr) curr->children[index] = new node;
            curr = curr->children[index];
        }
        curr->isCompleteWord = true;
    }
    
    bool search(string word) {
        // Using a queue to keep track of all possible states
        // Each state is a pair of (node pointer, position in word)
        queue<pair<node*, int>> q;
        q.push({root, 0});
        
        while(!q.empty()) {
            auto [curr, pos] = q.front();
            q.pop();
            
            // If we've processed the entire word
            if(pos == word.size()) {
                if(curr->isCompleteWord) return true;
                continue;
            }
            
            char ch = word[pos];
            
            if(ch == '.') {
                // For wildcard, try all possible children
                for(int i = 0; i < 26; i++) {
                    if(curr->children[i] != nullptr) {
                        q.push({curr->children[i], pos + 1});
                    }
                }
            } else {
                // For regular character
                int index = ch - 'a';
                if(curr->children[index] != nullptr) {
                    q.push({curr->children[index], pos + 1});
                }
            }
        }
        
        return false;
    }
};