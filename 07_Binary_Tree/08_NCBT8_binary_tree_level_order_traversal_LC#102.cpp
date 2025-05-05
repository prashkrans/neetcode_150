/* LC#102. Binary Tree Level Order Traversal

Two ways: 
1. DFS (2 types: O(n) and O(n^2))
2. BFS (Best method) - no need of visited array as there are no back edges or cycles in a tree

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

//  1. BFS (Prefer this method)
//  O(n)
//  O(n) due to the queue
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root) return ans; // Base case of root == nullptr
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int qSize = q.size();
            vector<int> nodeValInCurrLevel;
            for(int i=0; i<qSize; i++) {
                TreeNode* u = q.front();
                q.pop();
                nodeValInCurrLevel.push_back(u->val); // [#IMP] insert u->val not u itself
                if(u->left) q.push(u->left);
                if(u->right) q.push(u->right);
            }
            ans.push_back(nodeValInCurrLevel);
        }
        return ans;
    }
};

// or, using curr instead of u

class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root) return ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            vector<int> nodesValAtCurrLevel;
            int qSize = q.size();
            for(int i=0; i<qSize; i++) {
                TreeNode* curr = q.front();
                q.pop();
                nodesValAtCurrLevel.push_back(curr->val);
                if(curr->left) q.push(curr->left);
                if(curr->right) q.push(curr->right);
            }
            ans.push_back(nodesValAtCurrLevel);
        }
        return ans;
    }
};

//  2. Better DFS
//  O(n)
//  O(n)

class Solution {
    void traverse(TreeNode* root, int depth, vector<vector<int>> &ans) {
        if(root == nullptr) return;
        if(ans.size() == depth) ans.push_back(vector<int>());
        ans[depth].push_back(root->val);
        traverse(root->left, depth + 1, ans);
        traverse(root->right, depth + 1, ans);
    }

public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        traverse(root, 0, ans);
        return ans;
    }
};

// or 

class Solution {
    int maxDepth(TreeNode* root) {
        if(root == nullptr) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }

    void traverse(TreeNode* root, int depth, vector<vector<int>> &ans) {
        if(root == nullptr) return;
        ans[depth].push_back(root->val);
        traverse(root->left, depth + 1, ans);
        traverse(root->right, depth + 1, ans);
    }
    
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans(maxDepth(root), vector<int>());
        traverse(root, 0, ans);
        return ans;
    }
};


//  3. DFS but worse (ignore this)
//  O(n^2)
//  O(h) (best case) or O(n) (worst case) due to the recursion stack

class Solution {
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }

    void currLevel(TreeNode* root, int level, vector<int> &currNodes) {
        if(!root) return;
        if(level==0) currNodes.push_back(root->val);
        currLevel(root->left, level-1, currNodes);
        currLevel(root->right, level-1, currNodes);
    }

public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(!root) return ans;
        int height = maxDepth(root) - 1;
        for(int i=0; i<=height; i++) {
            vector<int> currNodes;
            currLevel(root, i, currNodes);
            ans.push_back(currNodes);
        }
        return ans;
    }
};