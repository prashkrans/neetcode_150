// LC#226. NCBT1. Invert Binary Tree

// 1. Recursion
// O(n) where n = no. of nodes of the binary tree. Note:  Its not O(2^n) but O(2^height) = O(2^logbase2n) = O(n)
// O(height) = O(logbase2n) due to the recursion stack and height = logn

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

 class Solution {
    public:
        TreeNode* invertTree(TreeNode* root) {
            if(root==nullptr) return root;
            TreeNode* temp = root->right;
            root->right = invertTree(root->left);
            root->left = invertTree(temp);
            return root;
        }
    };