/* LC#124. NCBT14. Binary Tree Maximum Path Sum

Approach for Maximum Path Sum in Binary Tree:

1. Problem Definition:
  - Find the maximum path sum in a binary tree
  - A path can start and end at any node
  - Path must follow tree edges without revisiting nodes

2. Key Insight:
  - For each node, we consider two types of paths:
    Case 1.) Path going through the node (connecting left and right subtrees)
    Case 2.) Path using the node as part of a bigger path up the tree i.e a node to its ancestors or parents

3. Core Algorithm:
  - Use post-order DFS traversal (left, right, node)
  - For each node, calculate:
    - Maximum path sum ending at current node (to be returned to parent): root->val + max(left, right)
    - Maximum path sum passing through current node (to update global max): root->val + left + right

4. Implementation Details:
  - Helper function `traverseDFS()` handles DFS traversal
  - Base case: return 0 for null nodes
  - For each node:
    - Recursively find max path sums from left and right subtrees
    - Ignore negative path sums by using max(0, path_sum) => Path pruning
    - Update global maximum when considering a path through current node
    - Return maximum possible path that can continue upward

5. Critical Optimizations:
  - Use max(0, pathSum) to ignore negative paths => Path pruning
  - Store global maximum in a reference parameter `ans`
  - Consider both connecting subtrees and extending paths upward

6. Edge Cases:
  - Handle single node trees (initialized ans with root value)
  - Handle negative node values (pruning negative paths)

7. Complexity Analysis:
  - Time Complexity: O(N) where N is the number of nodes in the tree
    - Each node is visited exactly once
  - Space Complexity: O(H) where H is the height of the tree
    - Recursion stack space in worst case (skewed tree): O(N)
    - Recursion stack space in best case (balanced tree): O(log N)

*/

class Solution {
    int traverseDFS(TreeNode* root, int &ans) { // Note: [#IMP] ans is a global variable
        if(root == nullptr) return 0;                                 // Base case: empty node returns 0
        
        int leftMax = max(0, traverseDFS(root->left, ans));          // Get max path sum from left subtree (ignore negative values)
        int rightMax = max(0, traverseDFS(root->right, ans));        // Get max path sum from right subtree (ignore negative values)
        
        ans = max(ans, root->val + leftMax + rightMax);              // Update global max with path through current node (Case 1)
        return root->val + max(leftMax, rightMax);                   // Return max one-way path up through this node (Case 2)    
    }
public:
    int maxPathSum(TreeNode* root) {                                 // Main function to find maximum path sum
        int ans = root->val;                                         // Initialize answer with the root value
        traverseDFS(root, ans);                                      // Start traversal from root
        return ans;                                                  // Return the maximum path sum found
    }
};