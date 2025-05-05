/* LC#230. Kth Smallest Element in a BST

Since its a BST, the elements are already sorted. Simple do an inorder traversal and insert the elements in
a vector. The kth smallest element is the (k-1)th element of that vector.
O(n) time and O(n) space

This should be marked as an easy but is marked as a medium.

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

// 1. Better and easier recursion i.e. simple inorder traveral i.e. left, root, right
// O(n)
// O(n)

class Solution {
    void inorderTraversal(TreeNode* root, vector<int> &sortedNodes) {
        if(root == nullptr) return;
        inorderTraversal(root->left, sortedNodes);
        sortedNodes.push_back(root->val);
        inorderTraversal(root->right, sortedNodes);
    }
public:
    int kthSmallest(TreeNode* root, int k) {
        vector<int> sortedNodes;
        inorderTraversal(root, sortedNodes);
        return sortedNodes[k-1];
    }
};



// 2. Recursion but worse:
// Time Complexity: O(n²) in worst case
// - For each node visited in traverseDFS, we call numOfNodes which takes O(n) time
// - In worst case, we might need to visit O(n) nodes
// - This leads to O(n²) overall time complexity

// Space Complexity: O(h) where h is the height of the tree
// - The recursion stack can go as deep as the height of the tree
// - In worst case (skewed tree), this becomes O(n)
// - No additional data structures are used
// */

class Solution {
    int numOfNodes(TreeNode* root) {
        if(!root) return 0;                                  // Base case: empty tree has 0 nodes
        return 1 + numOfNodes(root->left) + numOfNodes(root->right); // Count current node + nodes in left and right subtrees
    }

    int traverseDFS(TreeNode* root, int k) {
        if(!root) return -1;                                 // Base case: empty tree
        int numOfNodesInLST = numOfNodes(root->left);        // Count nodes in left subtree
        if(numOfNodesInLST >= k) return traverseDFS(root->left, k); // If kth smallest is in left subtree, search there
        else {                            					// If kth smallest is not in left subtree i.e if(numOfNodesInLST < k) 
            if(numOfNodesInLST == k-1) return root->val;      // If current node is the kth smallest, return its value
            return traverseDFS(root->right, k - (numOfNodesInLST + 1)); // Otherwise, search in right subtree with adjusted k
        }
    }

public:
    int kthSmallest(TreeNode* root, int k) {
        return traverseDFS(root, k);                         // Start DFS traversal to find kth smallest
    }
};

