/* LC#297. NCBT15. Serialize and Deserialize Binary Tree

Took me three hours to solve this


*/


// 1. BFS Serialize then BFS Deserialize
// O(n)
// O(n)

class Codec {
    // This function could be replaced with the inbuilt function to_string(num)
    string intToString(int n) {                         // Converts integer to string
        bool isNegative = false;                        // Flag for negative number
        if(n<0) {
            n *= -1;                                    // Make number positive
            isNegative = true;                          // Mark as originally negative
        }
        string s;
        while(n) {
            int rem = n%10;                             // Get last digit
            char ch = rem + '0';                        // Convert digit to char
            s = ch + s;                                 // Append to result string
            n /= 10;                                    // Remove last digit
        }
        return (isNegative) ? '-' + s : s;              // Add minus sign if needed
    }

    // This function could be replaced with the inbuilt function stoi(str)
    int stringToInt(string s) {                         // Converts string to integer
            if(s == "#") return INT_MAX;                // Special marker for null node
            int n = s.size();
            int i = (s[0] == '-') ? 1 : 0;               // Start after '-' if negative
            int ans = 0;
            while(i<n) ans = ans*10 + (s[i++] - '0');   // Build number from digits
            return (s[0] == '-') ? -1*ans : ans;         // Add sign back if needed
        }

    vector<string> splitByComma(string s) {             // Splits string by commas
        vector<string> ans;
        int startIndex = 0;
        for(int i=0; i<s.size(); i++) {
            if(s[i] == ',') {
                ans.push_back(s.substr(startIndex, i-startIndex)); // Extract token
                startIndex = i+1;                    // Move to next token start
            }
        }
        ans.push_back(s.substr(startIndex));            // Add last token
        return ans;
    }

public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {                  // BFS-based tree serialization
        string s;
        if(root == nullptr) return s;                   // Empty tree case
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()) {
            TreeNode* u = q.front();
            q.pop();
            if(u != nullptr) {
                s += intToString(u->val);               // Convert node value to string
                s += ',';                               // Add comma separator
                q.push(u->left);                        // Add left child to queue
                q.push(u->right);                       // Add right child to queue
            }
            else s += "#,";                             // Marker for null node
        }
        // cout<<"Serialized string: "<<s.substr(0, s.size()-1)<<endl;
        return s.substr(0, s.size()-1);                 // Remove last comma
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {                // BFS-based tree reconstruction
        if(data.empty()) return nullptr;                // Handle empty input
        vector<string> stringNodes = splitByComma(data); // Tokenize string
        // for(auto i : stringNodes) cout<<i<<" "; cout<<endl;
        vector<int> nodes;
        for(auto node: stringNodes) nodes.push_back(stringToInt(node)); // Convert to int
        // for(auto i : nodes) cout<<i<<" "; cout<<endl;
        
        int i = 0;
        TreeNode* root = new TreeNode(nodes[i++]);      // Create root node
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty() && i<nodes.size()) {
            TreeNode* u = q.front();
            q.pop();
            int leftChildVal = nodes[i++];              // Get left child value
            int rightChildVal = nodes[i++];             // Get right child value
            if(leftChildVal != INT_MAX) {               // Check if left is not null
                TreeNode* leftChild = new TreeNode(leftChildVal); // Create left child
                q.push(leftChild);                      // Add to queue
                u->left = leftChild;                    // Link to parent
            }
            if(rightChildVal != INT_MAX) {              // Check if right is not null
                TreeNode* rightChild = new TreeNode(rightChildVal); // Create right child
                q.push(rightChild);                     // Add to queue
                u->right = rightChild;                  // Link to parent
            }
        }
        return root;                                    // Return reconstructed tree
    }
};



// 2. DFS Serialize then DFS Deserialize
// O(n)
// O(n)

class Codec {
public:
    int strToInt(string s) {            //  Converts a string to integer
        if(s=="X") return 10000;        //  it also takes care of negative integers stored in the string
        string str;
        if(s[0]=='-') str = s.substr(1);
        else str = s;
        int n = str.size(); 
        int ans = 0;
        for(int i=0; i<n; i++) ans = ans*10 + (str[i] - '0');
        if(s[0]=='-') return -ans;
        return ans;
    }
    
    // Encodes a tree to a single string. Preorder traversal
    string serialize(TreeNode* root) {
        if(root==NULL) return "X";              //  NULL is represented by X
        string LST = serialize(root->left);
        string RST = serialize(root->right);
        string currST = to_string(root->val) + "," + LST + "," + RST;   //  Values are separated by ','
        return currST;
    }
    
    TreeNode* deserializeHelper(queue<int> &intQ) { //  Trickier than serialize() as we dont know where the left subtree ends
        if(intQ.size()==0) return NULL;
        if(intQ.front()==10000) {                   //  Since the values in nodes <1000 using 10000 to represent NULL
            intQ.pop();
            return NULL;
        }
        TreeNode* root = new TreeNode(intQ.front());        
        intQ.pop();
        root->left = deserializeHelper(intQ);
        root->right = deserializeHelper(intQ);
        return root;       
    }
    
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string s) {               //  We need to convert the string to a queue as it helps keep the info where the left subtree ends 
        cout<<"Serialized string:"<<s<<endl;
        queue<string> Q;                            //  The string is split at the ',' using a queue of strings
        queue<int> intQ;                            //  The resulting queue of string is then converted back to a queue of integers (+ or -)
        int prev = 0;
        for(int i=0; i<s.size(); i++){
            if(s[i]==',') {
                Q.push(s.substr(prev, i-prev));     //  As integers with 2 or more digits are stored as strings of size = no. of digits
                prev = i+1;
            }
        }
        Q.push(s.substr(prev));                     //  Adding the last substring to the queue of strings
        while(!Q.empty()) {
            int val = strToInt(Q.front());          //  Converting the string to its integer counterpart
            intQ.push(val);          
            Q.pop();
        }        
        return deserializeHelper(intQ);             //  It is the main deserializer function
    }        
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));