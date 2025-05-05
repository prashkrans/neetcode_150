/* LC#14. Longest Common Prefix

Approaches: 
1. Trie 
2. Hashmap that counts the frequency of each character in the prefix

Approach 1: Trie
1. Insert the first string into a prefix tree (Trie).
2. For each of the remaining strings, traverse the Trie and find the longest common prefix.
3. Return the longest common prefix found.
4. If no common prefix is found, return an empty string.


// Method 1: Using a prefix tree (Trie)
// Running time: O(S), where S is the sum of all characters in all strings
// Auxiliary space: O(m), where m is the length of the LCP

struct node {
    bool isWord;
    node* children[26];
    node () {
        isWord = false;
        for(int i=0; i<26; i++) children[i] = nullptr;
    }
};

class Solution {
    node* root;
public:
    Solution(): root(new node) {}

    void insert(string s) {
        node* curr = root;
        for(int i=0; i<s.size(); i++) {
            int index = s[i] - 'a';
            if(curr -> children[index] == nullptr) curr -> children[index] = new node;
            curr = curr -> children[index];
        }
        curr -> isWord = true;
    }

    int lcp(string s) {
        int count = 0;
        node* curr = root;
        for(int i=0; i<s.size(); i++) {
            int index = s[i] - 'a';
            if(curr->children[index] == nullptr) return count;
            else {
                count++;
                curr = curr -> children[index];
            }
        }
        return count;
    }
    
    string longestCommonPrefix(vector<string>& strs) {
        if(strs.size()==1) return strs[0];
        else {
            insert(strs[0]);
            int minLcpLength = INT_MAX;
            for(int i=1; i<strs.size(); i++) {
                minLcpLength = min(minLcpLength, lcp(strs[i]));
            }
            cout<<minLcpLength<<" ";
            return strs[0].substr(0, minLcpLength);
        }
    }
};

// Method 2: Iterative [This is not Knuth Morris Pratt]
// Running time: O(S), where S is the sum of all characters in all strings
// Auxiliary space: O(m), where m is the length of the LCP

// class Solution {
// public:
//     string longestCommonPrefix(vector<string>& strs) {
//         string curr = strs[0];
//         for(int i=1; i<strs.size(); ++i) {
//             int j=0;
//             int n = min(curr.length(), strs[i].length());
//             while(j<n && curr[j]==strs[i][j]) {
//                 ++j;
//             }
//             curr = strs[i].substr(0,j);
//         }
//         return curr;
//     }
// };