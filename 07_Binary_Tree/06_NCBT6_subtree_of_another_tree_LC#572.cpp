/* LC#572. NCBT6. Subtree of Another Tree

Two approaches:
1. Recursion + isSameTree as a helper function (Prefer this)
2. Binary Tree Serialization And Pattern Matching (TODO)

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


// 1a. Recursion but compact
// O(n * m) where n = no. of nodes in the main tree and m = no. of nodes in the subtree
// O(n + m)

class Solution {
    bool isSameTree(TreeNode* p, TreeNode* q) {
         if(p == nullptr && q == nullptr) return true;
         if(p == nullptr || q == nullptr) return false;
         if(p->val != q->val) return false;
         return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
     }
 
 public:
     bool isSubtree(TreeNode* root, TreeNode* subRoot) {
         if(root == nullptr) return false;
         return (isSameTree(root, subRoot)
             || isSubtree(root->left, subRoot) 
             || isSubtree(root->right, subRoot));
     }
 };
 

// 1b. Recursion
// O(n * m) where n = no. of nodes in the main tree and m = no. of nodes in the subtree
// O(n + m)

class Solution {
bool isSameTree(TreeNode* p, TreeNode* q) {
        if(p == nullptr && q == nullptr) return true;
        if(p == nullptr || q == nullptr) return false;
        if(p->val != q->val) return false;
        return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
    }

    void traverse(TreeNode* root, TreeNode* subRoot, bool &ans) {
        if(root == nullptr) return;
        ans = ans || isSameTree(root, subRoot);
        traverse(root->left, subRoot, ans);
        traverse(root->right, subRoot, ans);
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        bool ans = false;
        traverse(root, subRoot, ans);
        return ans;   
    }
};
 