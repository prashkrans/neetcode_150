// LC#125. Valid Palindrome
// We need only alpha numeric characters in the processed string

// 1. Using iterative preprocess and two pointers for isPalindrome
// O(n + n) ~ O(n)
// O(n) due to a new string t

class Solution {
    // string preprocess(string s) { // recursive preprocess gets memory limit exceeded
    //     if(s.empty()) return "";
    //     char curr;
    //     if(s[0]>='A' && s[0]<='Z')
    //         curr = (s[0] - 'A') + 'a';
    //     else if(s[0]>='a' && s[0]<='z')
    //         curr = s[0];
    //      else if(s[0]>='0' && s[0]<='9')
    //         curr = s[0];
    //     else return preprocess(s.substr(1));
    //     return curr + preprocess(s.substr(1));
    // }
    string preprocess(string s) {
        string t;
        for(int i=0; i<s.size(); i++) {
            if(s[i]>='A' && s[i]<='Z')
                t += (s[i] - 'A') + 'a';
            else if(s[i]>='a' && s[i]<='z')
                t += s[i];
            else if(s[i]>='0' && s[i]<='9')
                t += s[i];
        }
        return t;
    }
public:
    bool isPalindrome(string s) {
        s = preprocess(s);
        cout<<s;
        int l = 0, r = s.size()-1;
        while(l < r) {
            if(s[l++] != s[r--]) return false;
        }
        return true;
    }
};
