/* LC#199. Binary Tree Right Side View

2 Approaches:
1. BFS
2. DFS with a vector passed as reference whose size == current depth

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

//  1. BFS
//  O(n)
//  O(n) 

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if(!root) return ans; // Important base, don't forget this
        
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            int qSize = q.size();
            vector<int> currLevelNodes;
            for(int i=0; i<qSize; i++) {
                TreeNode* u = q.front();
                q.pop();
                currLevelNodes.push_back(u->val);
                if(u->right) q.push(u->right);  // [#IMP] right above left => currLevelNodes[0]
                if(u->left) q.push(u->left);
            }
            ans.push_back(currLevelNodes[0]);   // [#IMP] insert currLevelNodes[0] not entire currLevelNodes like in level order traversal
        }
        return ans;
    }
};


//  2. DFS with a vector passed as reference and when size == current depth insert root->val
//  O(n)
//  O(n)

class Solution {
    void traverse(TreeNode* root, int depth, vector<int> &ans) {
        if(root == nullptr) return;
        if(ans.size() == depth) ans.push_back(root->val);
        traverse(root->right, depth + 1, ans);
        traverse(root->left, depth + 1, ans);
    }

public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        traverse(root, 0, ans);
        return ans;        
    }
};