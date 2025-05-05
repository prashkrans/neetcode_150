/* LC#98. Validate Binary Search Tree

Sizes and ranges (typical on 64-bit Linux/macOS)
On Windows, 'long' is only 4 bytes

Typical values on 64-bit systems (Linux/macOS):
Note: On Windows, 'long' is 4 bytes like 'int'

int         // 4 bytes →  INT_MIN  = -2,147,483,648       | INT_MAX  = 2,147,483,647
* long is the same as int in Windows, while long is the same as long long in linux
long        // 8 bytes →  LONG_MIN = -9,223,372,036,854,775,808 | LONG_MAX = 9,223,372,036,854,775,807
long long   // 8 bytes →  LLONG_MIN = -9,223,372,036,854,775,808 | LLONG_MAX = 9,223,372,036,854,775,807

Approaches:
    1. Better DFS
    2. DFS but worse
    3. BFS

Note: 
1. Here we left < root->val < right not left <= root->val <= right
2. We use LLONG_MIN and LLONG_MAX to avoid overflow when comparing with INT_MIN and INT_MAX
3. When going left, we set right to root->val and when going right, we set left to root->val
4. We can compare root->val either before or after the recursive calls

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

//  1. Better DFS (Prefer this method)
//  O(n) | 0ms beats 100%
//  O(n)

typedef long long ll;
class Solution {
    bool traverseDFS(TreeNode* root, ll left, ll right) {
        if(root == nullptr) return true;                    // Empty tree is valid
        return traverseDFS(root->left, left, root->val)     // Left subtree: upper bound becomes current value         
            && traverseDFS(root->right, root->val, right)   // Right subtree: lower bound becomes current value
            && (left < root->val && root->val < right);     // Current node must also be valid
    }

public:
    bool isValidBST(TreeNode* root) {
        return traverseDFS(root, LLONG_MIN, LLONG_MAX);     // left is maxVal so its LLONG_MIN and right is minVal so its LLONG_MAX 
    }
};

// or, 
typedef long long ll;
class Solution {
    bool traverseDFS(TreeNode* root, ll left, ll right) {
        if(root == nullptr) return true;
        return (left < (ll)root->val && right > (ll)root->val)
            && traverseDFS(root->left, left, (ll)root->val)
            && traverseDFS(root->right, (ll)root->val, right);
    }

public:
    bool isValidBST(TreeNode* root) {
        return traverseDFS(root, LLONG_MIN, LLONG_MAX);        
    }
};

// or, 
typedef long long ll;
class Solution {
    bool rec(TreeNode* root, ll left, ll right) {
        if(!root) return true;
        return(left < root->val && root->val < right && rec(root->left, left, root->val) && rec(root->right, root->val, right));
    }
public:
    bool isValidBST(TreeNode* root) {
        return rec(root, LLONG_MIN, LLONG_MAX);
    }
};

//  2. DFS but worse
//  Time Complexity: O(n²)
//  - Each call to isValidBST() triggers O(n) operations via maxVal()/minVal()
//  - These functions traverse entire subtrees for every node
//  - Results in quadratic time for both balanced and skewed trees

//  Space Complexity: O(h) where h is tree height
//  - Recursion stack depth equals tree height
//  - Best case (balanced): O(log n)
//  - Worst case (skewed): O(n)

class Solution {
    long long minVal(TreeNode* root) {
        if(!root) return LLONG_MAX;  // Base case: return max possible value for empty node
        return min((long long)root->val, min(minVal(root->left), minVal(root->right)));  // Find minimum among current node and both subtrees
    }

    long long maxVal(TreeNode* root) {
        if(!root) return LLONG_MIN;  // Base case: return min possible value for empty node
        return max((long long)root->val, max(maxVal(root->left), maxVal(root->right)));  // Find maximum among current node and both subtrees
    }

public:
    bool isValidBST(TreeNode* root) {
        if(!root) return true;  // Empty tree is valid BST
        
        long long maxV = LLONG_MIN;  // Initialize with smallest possible value
        long long minV = LLONG_MAX;  // Initialize with largest possible value
        
        if (root->left) maxV = maxVal(root->left);  // Get max value from left subtree
        if (root->right) minV = minVal(root->right);  // Get min value from right subtree
        
        bool left = isValidBST(root->left);   // Recursively check if left subtree is valid BST
        bool right = isValidBST(root->right);  // Recursively check if right subtree is valid BST
        
        // BST is valid if: left subtree valid, right subtree valid, 
        // max of left < current node, min of right > current node
        return left && right && (maxV < root->val && minV > root->val);
    }
};


// class Solution { // INT_MIN and INT_MAX fails
//     int minVal(TreeNode* root) {
//         if(!root) return INT_MAX;
//         return min(root->val, min(minVal(root->left), minVal(root->right)));
//     }

//     int maxVal(TreeNode* root) {
//         if(!root) return INT_MIN;
//         return max(root->val, max(maxVal(root->left), maxVal(root->right)));
//     }

// public:
//     bool isValidBST(TreeNode* root) {
//         if(!root) return true;
//         int maxV = INT_MIN;
//         int minV = INT_MAX;
//         if (root->left) maxV = maxVal(root->left);
//         if (root->right) minV = minVal(root->right);
//         bool left = isValidBST(root->left);
//         bool right = isValidBST(root->right);
//         return left && right && (maxV < root->val && minV > root->val);
//     }
// };


//  3. BFS

typedef long long ll;  // Define a shorthand for 'long long' type for larger integer range

struct node{
	TreeNode* treeNode;  // Pointer to the actual tree node
	ll left;             // Left boundary for valid values at this node
	ll right;            // Right boundary for valid values at this node
	
	node(): treeNode(nullptr), left(LLONG_MIN), right(LLONG_MAX) {}  // Default constructor: no node, full range
	node(TreeNode* treeNode_): treeNode(treeNode_), left(LLONG_MIN), right(LLONG_MAX) {}  // Constructor with node, full range
	node(TreeNode* treeNode_, ll left_, ll right_): treeNode(treeNode_), left(left_), right(right_) {}  // Constructor with all parameters
};

class Solution {
public:
	bool isValidBST(TreeNode* root) {
		queue<node*> q;  // Queue for BFS traversal
		q.push(new node(root));  // Initialize with root node and default boundaries
		while(!q.empty()) {
			node *front = q.front();  // Get the front node from queue
			q.pop();  // Remove the front node from queue
			TreeNode* curr = front->treeNode;  // Current tree node
			ll left = front->left;  // Left boundary for current node
			ll right = front->right;  // Right boundary for current node
			
			if(left < curr->val && right > curr->val) {  // Check if current node's value is within valid range
			    if(curr->left) q.push(new node(curr->left, left, curr->val));  // For left child, update right boundary to current value
			    if(curr->right) q.push(new node(curr->right, curr->val, right));  // For right child, update left boundary to current value
            }
            else return false;  // #IMP to use else here. If value is outside the valid range, tree is not a valid BST
		}
		return true;  // If we've checked all nodes without returning false, the tree is a valid BST
	}
};





/* TODO: Incorrect for now
*/
typedef long long ll;
class Solution {
    ll maxll(ll a, ll b) {
        return (a > b) ? a : b;
    }
    ll minll(ll a, ll b) {
        return (a < b) ? a : b;
    }
    pair<ll, ll> rec(TreeNode* root) {
        if(!root) return {LLONG_MIN, LLONG_MAX};
        ll left = rec(root->left).first;
        ll right = rec(root->right).second;
        // if(left == INT_MAX || right == INT_MIN) return {INT_MAX, INT_MIN};
        int maxVal = maxll(root->val, maxll(left, right));
        int minVal = minll(root->val, minll(left, right));
        if((ll)root->val > left && (ll)root->val < right) return {maxVal, minVal};
        return {LLONG_MAX, LLONG_MIN};
    }
public:
    bool isValidBST(TreeNode* root) {
        pair<ll, ll> ans = rec(root);
        cout<<ans.first<<" "<<ans.second<<endl;
        if(ans.first == LLONG_MAX && ans.second == LLONG_MIN) return false;
        return true;        
    }
};