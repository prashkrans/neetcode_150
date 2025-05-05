/* LC#543. Diameter of Binary Tree

Diameter of a binary subtree at any node is given by (Remember this):
    int heightOfLST = maxDepth(root->left, diameter); 
    int heightOfRST = maxDepth(root->right, diameter);
    int currDiameter = heightOfLST + heightOfRST;


Approach:
O(n^2)
1. Diameter at any node = height of LST + height of RST. This includes the node. 
Here, height of LST/RST is maxDepth of LST/RST without the node

2. Diameter could either pass through the node or not pass through i.e. 
return max(diameter through node, diameter without the node)

O(n)
DFS i.e. Max Depth function only once and a global variable or a variable passed by reference


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

// 1. Recursion (Prefer this method)
// O(n^2) due to maxDepth inside diameterOfBinaryTree
// O(h) due to the recursion stack

class Solution {
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if(!root) return 0;
        int diameter = maxDepth(root->left) + maxDepth(root->right);
        int subTreeDiameter = max(diameterOfBinaryTree(root->left), diameterOfBinaryTree(root->right));
        return max(diameter, subTreeDiameter);
    }
};

// 2. Recursion (Better than 1 and 3). It uses the maxDepth function itself only once
// O(n) i.e. linear instead of O(n^2) | 0ms beats 100%
// O(h) in best case or O(n) in worst case (degenerate tree or linear tree like a linked list)

class Solution {
    int maxDepth(TreeNode* root, int &diameter) {           // [#IMP] diameter is passed by reference
        if(!root) return 0;
        int heightOfLST = maxDepth(root->left, diameter);
        int heightOfRST = maxDepth(root->right, diameter);
        int currDiameter = heightOfLST + heightOfRST;       // calucate diameter at this node
        diameter = max(diameter, currDiameter);             // update the diameter
        return 1 + max(heightOfLST, heightOfRST);           // we calc diameter but return maxDepth
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        maxDepth(root, diameter);
        return diameter;
    }
};

// 3. Recursion (Ignore)
// O(n^2) due to maxDepth inside traverse
// O(h) due to the recursion stack

class Solution {
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }

    void traverse(TreeNode* root, int &diameter) {
        if(!root) return;
        diameter = max(diameter, maxDepth(root->left) + maxDepth(root->right));
        traverse(root->left, diameter);
        traverse(root->right, diameter);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        traverse(root, diameter); 
        return diameter;
    }
};