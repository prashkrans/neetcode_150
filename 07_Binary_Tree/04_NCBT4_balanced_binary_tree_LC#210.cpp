/* LC#110. NCBT4. Balanced Binary Tree

A height-balanced binary tree is a binary tree in which the depth of the two subtrees of every node 
never differs by more than one. 
=> maxDepth(left) - maxDepth(right) <= 1 or height of the left and right subtrees differ by at most 1.
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// 1. Recursion (Only use this approach to understand the problem but solve using 2. Better Recursion)
// O(n*n) = O(n^2)
// O(height) not O(h^2) where h = height = logn

class Solution {
    int maxDepth(TreeNode* root) {
        if(root==nullptr) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
public:
    bool isBalanced(TreeNode* root) {
        if(root == nullptr) return true;
        int heightOfLST = maxDepth(root->left) - 1;
        int heightOfRST = maxDepth(root->right) - 1;
        if(abs(heightOfLST - heightOfRST) > 1) return false;
        return isBalanced(root->left) && isBalanced(root->right);
    }
};

/*
### Approach: Optimized Depth-First Search (DFS)
1. Use a recursive function `maxDepth` to calculate the depth of the tree while checking for balance.
2. For each node:
   - Recursively calculate the depth of the left and right subtrees.
   - If either subtree is unbalanced (returns `INT_MIN`), propagate `INT_MIN` up the recursion stack.
   - If the difference in depths of the left and right subtrees is greater than 1, mark the current node 
     as unbalanced by returning `INT_MIN`.
   - Otherwise, return the depth of the current node as `1 + max(left, right)`.
3. In the `isBalanced` function, check if the result of `maxDepth` is `INT_MIN`:
   - If yes, the tree is unbalanced.
   - Otherwise, the tree is balanced.

### Complexity:
- **Time Complexity**: O(n)
  - Each node is visited once during the depth calculation.
- **Space Complexity**: O(h)
  - The recursion stack can go as deep as the height of the tree.

### Alternative:
- Instead of using `INT_MIN`, you can use `-1` to indicate an unbalanced subtree for simplicity.
*/

// 2. Better Recursion: DFS using maxDepth
// Time Complexity: O(n)
// - Each node is visited once during the depth calculation, making the complexity O(n), where n is the number of nodes in the tree.

// Space Complexity: O(h)
// - The recursion stack can go as deep as the height of the tree, which is O(h), where h is the height of the tree.

class Solution {
    int maxDepth(TreeNode* root) {
        if(!root) return 0;                              // Base case: null node has depth 0
        int left = maxDepth(root->left);                 // Recursively calculate the depth of the left subtree
        int right = maxDepth(root->right);               // Recursively calculate the depth of the right subtree
        if(left == INT_MIN || right == INT_MIN) return INT_MIN; // If any subtree is unbalanced, propagate INT_MIN
        if(abs(right - left) > 1) return INT_MIN;        // If the current node is unbalanced, return INT_MIN
        return 1 + max(left, right);                     // Return the depth of the current node
    }
public:
    bool isBalanced(TreeNode* root) {
        return (maxDepth(root) == INT_MIN) ? false : true; // Check if the tree is balanced
    }
};


// or, using -1 instead of INT_MIN
// O(n) time and O(h) space

class Solution {
    int maxDepth(TreeNode* root) {
        if(!root) return 0;                              // Base case: null node has depth 0
        int left = maxDepth(root->left);                 // Recursively calculate the depth of the left subtree
        int right = maxDepth(root->right);               // Recursively calculate the depth of the right subtree
        if(left == -1 || right == -1) return -1;         // If any subtree is unbalanced, propagate -1
        if(abs(right - left) > 1) return -1;             // If the current node is unbalanced, return -1
        return 1 + max(left, right);                     // Return the depth of the current node
    }
public:
    bool isBalanced(TreeNode* root) {
        return (maxDepth(root) == -1) ? false : true;    // Check if the tree is balanced
    }
};