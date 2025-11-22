// 20. Valid Parentheses


// 1. Using a stack
// O(n) where n = size of string s
// O(n)

class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for(int i=0; i<s.size(); i++) {
            if(st.empty()) st.push(s[i]);
            else {
                if(st.top() == '{' && s[i] == '}') st.pop();
                else if(st.top() == '[' && s[i] == ']') st.pop();
                else if(st.top() == '(' && s[i] == ')') st.pop();
                else st.push(s[i]);
            }
        }
        return (st.empty()) ? true : false;
    }
};
    