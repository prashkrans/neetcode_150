/* LC#105. Construct Binary Tree from Preorder and Inorder Traversal


Approach Explanation:

Both solutions use the key properties of tree traversals:

1. Core Concept: 
  - The first element in preorder traversal is always the root node
  - In inorder traversal, all elements to the left of the root belong to the left subtree, and all elements to the right belong to the right subtree

2. Recursive Construction Process:
  - Take the next element from preorder array as the current root
  - Find this element's position in the inorder array
  - This position divides the inorder array into left and right subtree elements
  - Recursively build the left subtree using the corresponding portions of both arrays
  - Recursively build the right subtree using the corresponding portions of both arrays

3. Key Difference Between Solutions:
  - Solution 1 uses linear search (O(n)) to find each element in the inorder array
  - Solution 2 pre-computes all positions in a hashmap for O(1) lookups, making it more efficient

Note: pre_idx is a global variable hence passed by reference. [#IMP]

*/

// 1. Recursion without a hashmap
// O(n^2) Since O(n) for lookup in inorder array and O(n) for recursion from 0 to n-1 for preorder array
// O(n) due to the recursion stack
// Note: pre_idx is a global variable hence passed by reference. [#IMP]

class Solution {
    TreeNode* buildTreeRec(int &pre_idx, vector<int> &preorder, int l, int r, vector<int> &inorder) {
        if(l > r) return nullptr;
        int rootVal = preorder[pre_idx++];
        TreeNode* root = new TreeNode(rootVal);
        int j = 0;
        while(j<inorder.size() && inorder[j] != rootVal) j++;
        root->left = buildTreeRec(pre_idx, preorder, l, j-1, inorder);
        root->right = buildTreeRec(pre_idx, preorder, j+1, r, inorder);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        int pre_idx = 0;
        return buildTreeRec(pre_idx, preorder, 0, n-1, inorder);    
    }
};

// or, same as above

class Solution {
    TreeNode* rec(int l, int r, int &pre_idx, vector<int>& preorder, vector<int>& inorder) {
        if(l > r) return nullptr;
        int val = preorder[pre_idx++];
        int mid = 0;
        while(mid<inorder.size()) {
            if(inorder[mid] == val) break;
            mid++;
        }
        TreeNode* root = new TreeNode(val);
        root->left = rec(l, mid-1, pre_idx, preorder, inorder);
        root->right = rec(mid+1, r, pre_idx, preorder, inorder);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int pre_idx = 0;
        return rec(0, preorder.size()-1, pre_idx, preorder, inorder);
    }
};


// 2. Recursion with a hashmap
// Simply replaces the while loop with a hashmap
// O(n) Since O(1) for lookup in inorder array and O(n) for recursion from 0 to n-1 for preorder array
// O(n) due to the recursion stack

class Solution {
    TreeNode* buildTreeRec(int &pre_idx, vector<int> &preorder, int l, int r, unordered_map<int, int> &inorderIndices) {
        if(l > r) return nullptr;
        int rootVal = preorder[pre_idx++];
        TreeNode* root = new TreeNode(rootVal);
        int mid = inorderIndices[rootVal];
        root->left = buildTreeRec(pre_idx, preorder, l, mid-1, inorderIndices);
        root->right = buildTreeRec(pre_idx, preorder, mid+1, r, inorderIndices);
        return root;
    }
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();
        int pre_idx = 0;
        unordered_map<int, int> inorderIndices;
        for(int i=0; i<n; i++) inorderIndices[inorder[i]] = i;
        return buildTreeRec(pre_idx, preorder, 0, n-1, inorderIndices);    
    }
};