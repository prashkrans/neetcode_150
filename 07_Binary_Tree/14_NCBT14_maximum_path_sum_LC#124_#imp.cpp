/* LC#124. NCBT14. Binary Tree Maximum Path Sum

Two ways: 

This problem got me a job at Amazon in 2022

Total 6 cases for maxPathSum and 3 cases for return
[#IMP] But using:
  int left = max(0, traverse(root->left, maxPathSum));
  int right = max(0, traverse(root->right, maxPathSum));
reduces the cases to 1 for maxPathSum and 1 for return

[#IMP] - When not using left/right = max(0, rec(left/right))
- The value returned from a node must represent the maximum gain that can be passed upward to its parent.
- Hence, it can include at most one child path (left or right), not both.
- That's why we return: max(root->val, root->val + max(left, right)).
- The 6 cases of root->val + left + right is a complete path and is only used for updating maxPathSum.

All methods take 0ms and beat 100%

* Definition for a binary tree node.
* struct TreeNode {
*     int val;
*     TreeNode *left;
*     TreeNode *right;
*     TreeNode() : val(0), left(nullptr), right(nullptr) {}
*     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
*     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
* };

### Approach 1a: Postorder DFS with Subtree Max Path Sum
1. Use DFS (postorder traversal) to compute the maximum path sum rooted at each node, considering left and right subtrees.
2. [#IMP] For each node, compute the max gain from the left and right child. If the gain is negative, discard it using max(0, ...).
3. The candidate maximum path through a node is: node's value + left gain + right gain. This considers the node as the peak.
4. Maintain a global variable `maxPathSum` to track the best such sum seen while traversing the tree recursively.
5. At each return, only pass along the best *one-sided* path (node + max(left, right)) to the parent to avoid bifurcations.
6. This ensures each path counted is valid (non-splitting), and all node contributions are added exactly once in a valid path.
7. Time complexity is O(n) because we visit each node once. Space complexity is O(h), the height of the tree, due to recursion.
*/

// Method 1a: Using left = max(0, rec(left)) and right = max(0, rec(right)) and returning INT_MIN
// Time Complexity:  O(n)                                       // Each node is visited once, n = no. of nodes
// Space Complexity: O(h)                                       // Call stack space, h = height of tree

class Solution {
  int traverse(TreeNode* root, int &maxPathSum) {
      if(!root) return INT_MIN;                                 // Base case: null node returns minimum integer
      int left = max(0, traverse(root->left, maxPathSum));      // Recursively get max gain from left subtree
      int right = max(0, traverse(root->right, maxPathSum));    // Recursively get max gain from right subtree
      maxPathSum = max(maxPathSum, root->val + left + right);   // Update global max if current path is better
      return root->val + max(left, right);                      // Return max path sum from root downward
  }
public:
  int maxPathSum(TreeNode* root) {
      int maxPathSum = INT_MIN;                                 // Initialize result with smallest integer
      traverse(root, maxPathSum);                               // Begin DFS traversal and update maxPathSum
      return maxPathSum;                                        // Return the highest path sum found
  }
};

// or, same as above but without comments

class Solution {
    int traverse(TreeNode* root, int &maxPathSum) {
        if(!root) return INT_MIN;
        int left = max(0, traverse(root->left, maxPathSum));
        int right = max(0, traverse(root->right, maxPathSum));
        maxPathSum = max(maxPathSum, root->val + left + right);
        return root->val + max(left, right);
    }
public:
    int maxPathSum(TreeNode* root) {
        int maxPathSum = INT_MIN;
        traverse(root, maxPathSum);
        return maxPathSum;
    }
};


/*
### Six Cases when both left and right children are non-null:
1. v                                      -> Node value alone, if both children add no benefit
2. v + L                                  -> Node + left child path only
3. v + R                                  -> Node + right child path only
4. L                                      -> Left child path only (skip node and right child)
5. R                                      -> Right child path only (skip node and left child)
6. v + L + R                              -> Full path through node connecting both left and right subtrees

All these are compared to update the global maximum path sum.
The return from the function, however, should only include one of the three cases: [#IMP]
v, v + L, or v + R — the best one-sided path to continue upward.

### Approach 1b: Postorder DFS with Explicit Null Child Handling
1. Use a recursive postorder traversal to compute the best path sum from both left and right
children at every node, updating a global maximum path sum in the process.
2. At each node, calculate six candidate values: the node itself, node + left, node + right,
left alone, right alone, and node + left + right to consider all path types.
3. Only return the best one-sided path from the node (either node alone or node + max of
left/right), because the complete path (including both children) can't be extended upward.
4. Base cases include handling null children by returning INT_MIN, ensuring that
nonexistent paths don't accidentally influence valid computations.
5. The algorithm runs in O(N) time and O(H) space, where N is number of nodes, and H is
tree height due to recursion.
*/


// Method 1b: Postorder DFS with Explicit Null Child Handling (My custom method)
// Time Complexity:  O(n)                                               // Each node is visited once, n = no. of nodes
// Space Complexity: O(h)                                               // Call stack space, h = height of tree

class Solution {
  int traverse(TreeNode* root, int &maxPathSum) {
      if(!root) return INT_MIN;                                                                 // base case: null node returns minimal value
      int left = traverse(root->left, maxPathSum);                                              // compute max path sum for left subtree
      int right = traverse(root->right, maxPathSum);                                            // compute max path sum for right subtree
      if(left == INT_MIN && right == INT_MIN) {                                                 // if both children are null
          maxPathSum = max(maxPathSum, root->val);                                              // update with just node value
          return root->val;                                                                     // return node value
      }
      if(left == INT_MIN) {                                                                     // only right child exists
          maxPathSum = max(maxPathSum, root->val);                                              // consider just node
          maxPathSum = max(maxPathSum, root->val + right);                                      // node + right
          maxPathSum = max(maxPathSum, right);                                                  // only right
          return max(root->val, root->val + right);                                             // return best one-sided path
      }
      if(right == INT_MIN) {                                                                    // only left child exists
          maxPathSum = max(maxPathSum, root->val);                                              // consider just node
          maxPathSum = max(maxPathSum, root->val + left);                                       // node + left
          maxPathSum = max(maxPathSum, left);                                                   // only left
          return max(root->val, root->val + left);                                              // return best one-sided path
      }
      maxPathSum = max(maxPathSum, root->val);                                                  // just node
      maxPathSum = max(maxPathSum, root->val + max(left, right));                               // node + one child
      maxPathSum = max(maxPathSum, root->val + left + right);                                   // full path through node
      maxPathSum = max(maxPathSum, max(left, right));                                           // just a child (rare but possible)
      return max(root->val, root->val + max(left, right));                                      // return best one-sided path
  }

public:
  int maxPathSum(TreeNode* root) {
      int maxPathSum = INT_MIN;                                                                 // initialize to negative infinity
      traverse(root, maxPathSum);                                                               // start postorder traversal
      return maxPathSum;                                                                        // return the final maximum path sum
  }
};


// or, same as above but without comments

class Solution {
  int traverse(TreeNode* root, int &maxPathSum) {
      if(!root) return INT_MIN;
      int left = traverse(root->left, maxPathSum);
      int right = traverse(root->right, maxPathSum);
      if(left == INT_MIN && right == INT_MIN) {
          maxPathSum = max(maxPathSum, root->val);
          return root->val;
      }
      if(left == INT_MIN) {
          maxPathSum = max(maxPathSum, root->val);
          maxPathSum = max(maxPathSum, root->val + right);
          maxPathSum = max(maxPathSum, right);
          return max(root->val, root->val + right);
      }
      if(right == INT_MIN) {
          maxPathSum = max(maxPathSum, root->val);
          maxPathSum = max(maxPathSum, root->val + left);
          maxPathSum = max(maxPathSum, left);
          return max(root->val, root->val + left);
      }
      maxPathSum = max(maxPathSum, root->val);
      maxPathSum = max(maxPathSum, root->val + max(left, right));
      maxPathSum = max(maxPathSum, root->val + left + right);
      maxPathSum = max(maxPathSum, max(left, right));        
      return max(root->val, root->val + max(left, right));
  }

public:
  int maxPathSum(TreeNode* root) {
      int maxPathSum = INT_MIN;
      traverse(root, maxPathSum);
      return maxPathSum;
  }
};

// Method 1c: Postorder DFS with Implicit Null Child Handling (My custom method)
// Time Complexity:  O(n)                                       // Each node is visited once, n = no. of nodes
// Space Complexity: O(h)                                       // Call stack space, h = height of tree

/*
    Time Complexity:  O(N)      -- Each node is visited once
    Space Complexity: O(H)      -- Call stack space (height of tree)

    At each node (when both left and right children exist), we consider these 6 cases:
      1. root->val                        // Take only the current node
      2. root->val + left                 // Include left subtree path
      3. root->val + right                // Include right subtree path
      4. root->val + left + right         // Combine both subtrees with current node as connector
      5. left                             // Skip current node, use left subtree only
      6. right                            // Skip current node, use right subtree only

    We don't clamp left/right with max(0, ...) before using them — so all six cases are relevant.
    
    The value returned from a node must represent the maximum gain that can be passed upward to its parent.
    Hence, it can include at most one child path (left or right), not both.
    That's why we return: max(root->val, root->val + max(left, right)).
    The case of root->val + left + right is a complete path and is only used for updating maxPathSum.
*/

class Solution {
  int traverse(TreeNode* root, int &maxPathSum) {
      if (!root) return INT_MIN;

      int left = traverse(root->left, maxPathSum);
      int right = traverse(root->right, maxPathSum);

      // Convert INT_MIN to 0 when considering in path (no contribution if no subtree)
      if (left == INT_MIN) left = 0;
      if (right == INT_MIN) right = 0;

      // Update the global maximum path sum with all possible combinations
      maxPathSum = max(maxPathSum, root->val);
      maxPathSum = max(maxPathSum, root->val + max(left, right));
      maxPathSum = max(maxPathSum, root->val + left + right);
      maxPathSum = max(maxPathSum, max(left, right));

      // Return the best one-sided path to propagate upward
      return max(root->val, root->val + max(left, right));
  }

public:
  int maxPathSum(TreeNode* root) {
      int maxPathSum = INT_MIN;
      traverse(root, maxPathSum);
      return maxPathSum;
  }
};

// or, same as above but without commments

class Solution {
  int traverse(TreeNode* root, int &maxPathSum) {
      if(!root) return INT_MIN;
      int left = traverse(root->left, maxPathSum);
      int right = traverse(root->right, maxPathSum);
      // Note: Not using max(0, rec(left/right)), so we need all 6 cases 
      if(left == INT_MIN) left = 0;           
      if(right == INT_MIN) right = 0; 
      maxPathSum = max(maxPathSum, root->val);
      maxPathSum = max(maxPathSum, root->val + max(left, right));
      maxPathSum = max(maxPathSum, root->val + left + right);
      maxPathSum = max(maxPathSum, max(left, right));        
      return max(root->val, root->val + max(left, right));
  }
public:
  int maxPathSum(TreeNode* root) {
      int maxPathSum = INT_MIN;
      traverse(root, maxPathSum);
      return maxPathSum;
  }
};