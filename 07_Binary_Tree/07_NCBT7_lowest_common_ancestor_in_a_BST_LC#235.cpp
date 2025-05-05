/* LC#235. NCBT7. Lowest Common Ancestor of a Binary Search Tree
Note: This is a BST not a simple binary tree. 

Approach:
Four cases to consider:
1. if the root is null, return null
2. if the root is #strictly greater than both p and q, then the LCA lies in the left subtree
3. if the root is #strictly less than both p and q, then the LCA lies in the right subtree
4. if the root is between p and q, then the root is guaranteed to be the LCA

1. Recursive
2. Iterative

All methods: R.T. = O(h) not O(n) and A.S = O(h) due to the recursion stack
O(h) is even in the worst case as its a BST which cannot be a degenerate or linear binary tree


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

// 1. Recursive (Prefer this method)
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root) return nullptr;
        if(root->val > p->val && root->val > q->val) return lowestCommonAncestor(root->left, p, q);
        if(root->val < p->val && root->val < q->val) return lowestCommonAncestor(root->right, p, q);
        return root;
    }
};
    


// or,

class Solution {
    public:
        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
            if(p->val < root->val && q->val < root->val) 
                return lowestCommonAncestor(root->left, p, q);
            if(p->val > root->val && q->val > root->val) 
                return lowestCommonAncestor(root->right, p, q);
            return root;
        }
    };

// or,

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int maxVal = max(p->val, q->val);
        int minVal = min(p->val, q->val);
        if(maxVal < root->val) return lowestCommonAncestor(root->left, p, q);
        if(minVal > root->val) return lowestCommonAncestor(root->right, p, q);
        if(minVal < root->val && maxVal > root->val) return root;
        if(minVal == root->val || maxVal == root->val) return root;
    }
};

// or 

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int maxVal = max(p->val, q->val);
        int minVal = min(p->val, q->val);
        if(maxVal < root->val) return lowestCommonAncestor(root->left, p, q);
        if(minVal > root->val) return lowestCommonAncestor(root->right, p, q);
        return root;
    }
};

// 2. Iterative

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* curr = root;
        while(curr) {
            if(p->val < curr->val && q->val < curr->val) curr = curr->left;
            else if(p->val > curr->val && q->val > curr->val) curr = curr->right;
            else return curr;            
        }
        return nullptr;
    }
};

// Note: use curr-val, not root->val in the iterative method