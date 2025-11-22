// LC#1448. Count Good Nodes in Binary Tree
// 1. DFS 2. BFS | Both of a pair of {root, maxVal in the path}
// O(n)
// O(n)

//  1. DFS traverse
//  O(n)
//  O(n)

class Solution {
    int traverse(TreeNode* root, int maxVal) {       // Helper function to traverse the tree
        if(root == nullptr) return 0;                // Base case: empty node contributes 0 good nodes
        maxVal = max(maxVal, root->val);             // Update max value seen in this path
        int left = traverse(root->left, maxVal);     // Recursively count good nodes in left subtree
        int right = traverse(root->right, maxVal);   // Recursively count good nodes in right subtree
        if(root->val < maxVal) return left + right;  // If not a good node, just return sum of subtrees
        return 1 + left + right;                     // If good node, count it (1) plus subtree results
    }
public:
    int goodNodes(TreeNode* root) {                  // Public interface function
        return traverse(root, root->val);            // Start traversal with root's value as initial max
    }
};

// or, same as above but compact
class Solution {
    int rec(TreeNode* root, int maxVal) {
        if(!root) return 0;
        int count = 0;
        if(root->val >= maxVal) count = 1;
        maxVal = max(maxVal, root->val);
        return count + rec(root->left, maxVal) + rec(root->right, maxVal);
    }
public:
    int goodNodes(TreeNode* root) {
        return rec(root, INT_MIN);
    }
};