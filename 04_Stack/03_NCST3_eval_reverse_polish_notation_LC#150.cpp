/* LC#150. Evaluate Reverse Polish Notation

Approaches:
1. Stack
2. Since stack can be used to solve this we can also use a recursion.

*/

// 1. Using a stack
// O(n*m) where n = size of tokens and m = avg length of string but m = 4(const)  = O(4n) ~ O(n)
// O(n)

class Solution {
    int stringToInt(string s) {
        bool isNegative = (s[0] == '-') ? true : false;
        if(isNegative) s = s.substr(1);
        int ans = 0;
        for(int i=0; i<s.size(); i++) ans = ans*10 + (s[i] - '0');
        return (isNegative) ? -1*ans : ans;
    }

public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st;
        for(int i=0; i<tokens.size(); i++) {
            string s = tokens[i];
            if(s != "+" && s != "-" && s != "*" && s != "/") 
                st.push(stringToInt(s));
            else {
                int right = st.top(); st.pop();
                int left = st.top(); st.pop();
                int res;
                if(s == "+") res = left + right;
                else if(s == "-") res = left - right;
                else if(s == "*") res = left * right;
                else res = left / right; // else if(s == "/") res = left / right;
                st.push(res);
            }
        }
        return st.top();
    }
};


// 2a. Recursion (from right to left)
// O(n)
// O(n)

class Solution {
public:
    int rec(vector<string>& tokens) {
        string token = tokens.back();
        tokens.pop_back();  // opposite of push_back()
        
        if (token != "+" && token != "-" && token != "*" && token != "/") 
            return stoi(token);

        int right = rec(tokens);
        int left = rec(tokens);
        
        if (token == "+") return left + right;
        else if (token == "-") return left - right;
        else if (token == "*") return left * right;
        else return left / right;
    }

    int evalRPN(vector<string>& tokens) {
        return rec(tokens);
    }
};


// 2b. Recursion (from right to left)
// O(n)
// O(n)

class Solution {
public:
    int rec(int &i, vector<string>& tokens) { // Using i as a global index 
        if(i == -1) return 0;
        string token = tokens[i--];

        
        if (token != "+" && token != "-" && token != "*" && token != "/") 
            return stoi(token);

        int right = rec(i, tokens);
        int left = rec(i, tokens);
        
        if (token == "+") return left + right;
        else if (token == "-") return left - right;
        else if (token == "*") return left * right;
        else return left / right;
    }

    int evalRPN(vector<string>& tokens) {
        int i = tokens.size()-1;
        return rec(i, tokens);
    }
};
    