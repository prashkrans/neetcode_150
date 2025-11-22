/**
LC91. NC1DP7. Decode Ways


**/
// Method 1a: Recursion with memoization
// Running time: O(n) due to the dp map, recursion is atmost n times
// Auxiliary space: O(n) due to the dp map and the recursion stack

class Solution {
    string intToString(int n) {
        string s;
        while(n) {
            int rem = n%10;
            s += '0' + rem;
            n = n/10;
        }
        reverse(s.begin(), s.end());
        // cout<<s<<" ";
        return s;
    }
    int rec(string s, unordered_set<string> &validCodes,  unordered_map<string, int> &dp) {
        if(s.empty()) return 1; // Correct base case
        else if(dp.count(s)) return dp[s];
        else {
            int left = 0, right = 0;
            string s1 = s.substr(0, 1);
            if(validCodes.count(s1)) left = rec(s.substr(1), validCodes, dp);
            if(s.size()>1) {
                string s2 = s.substr(0, 2);
                if(validCodes.count(s2)) right = rec(s.substr(2), validCodes, dp);
            }
            dp[s] = left + right;
            return dp[s];            
        }    
    }
public:
    int numDecodings(string s) {
        int count = 0;
        unordered_set<string> validCodes;
        unordered_map<string, int> dp;
        for(int i=1; i<=26; i++) {
            string validCode = intToString(i);
            validCodes.insert(validCode); // Don't insert dp[validCode] = 1
        }
        dp[s] = rec(s, validCodes, dp);
        return dp[s];
    }
};

// Method 2a: Bottom up approach with DP array
// Running time: O(n) due to the dp vector
// Auxiliary space: O(n) due to the dp vector
// TODO - yet to understand this

class Solution {
    public:
        int numDecodings(string s) {
            vector<int> dp(s.size() + 1);
            dp[s.size()] = 1;
            for (int i = s.size() - 1; i >= 0; i--) {
                if (s[i] == '0') {
                    dp[i] = 0;
                } else {
                    dp[i] = dp[i + 1];
                    if (i + 1 < s.size() && (s[i] == '1' || 
                        s[i] == '2' && s[i + 1] < '7')) {
                        dp[i] += dp[i + 2];
                    }
                }
            }
            return dp[0];
        }
    };

// Method 2b: Bottom up approach with DP array
class Solution {
    public:
        int numDecodings(string s) {
            // Handle empty string or leading zero
            if (s.empty() || s[0] == '0') return 0;
            
            unordered_set<string> validCodes;
            for(int i=1; i<=26; i++) validCodes.insert(to_string(i));
            
            int n = s.size();
            vector<int> dp(n+1, 0);  // Initialize with 0 instead of -1
            dp[n] = 1;
            
            // Handle last character as dp[n-1] could be 1 or 0
            dp[n-1] = (s[n-1]!='0') ? 1 : 0;  // E.g. "10"
            // or dp[n-1] = validCodes.count(s.substr(n-1, 1)) ? 1 : 0;  // E.g. "10"
            
            for(int i=n-2; i>=0; i--) {            
                string s1 = s.substr(i, 1);
                string s2 = s.substr(i, 2);
                if(validCodes.count(s1)) dp[i] = dp[i+1];
                if(validCodes.count(s2)) dp[i] += dp[i+2];
            }
            
            return dp[0];
        }
    };

// Method 1b: Recursion with memoization but bad base case
// Running time: O(n) due to the dp map recursion is atmost n times
// Auxiliary space: O(n) due to the dp map and the recursion stack
class Solution {
    string intToString(int n) {
        string s;
        while(n) {
            int rem = n%10;
            s += '0' + rem;
            n = n/10;
        }
        reverse(s.begin(), s.end());
        // cout<<s<<" ";
        return s;
    }
    int rec(string s, unordered_set<string> &validCodes,  unordered_map<string, int> &dp) {
        // if(s.empty()) return 1;
        if(dp.count(s)) return dp[s];
        else {
            int left = 0, right = 0;
            if(s.size()>0) {
                string s1 = s.substr(0, 1);
                if(validCodes.count(s1)) left = rec(s.substr(1), validCodes, dp);
            }
            if(s.size()>1) {
                string s2 = s.substr(0, 2);
                if(validCodes.count(s2)) right = rec(s.substr(2), validCodes, dp);
            }
            
            dp[s] = left + right;
            return dp[s];            
        }    
    }
public:
    int numDecodings(string s) {
        int count = 0;
        unordered_set<string> validCodes;
        unordered_map<string, int> dp;
        for(int i=1; i<=26; i++) {
            string validCode = intToString(i);
            validCodes.insert(validCode);
            if(i<=10 || i==20) dp[validCode] = 1; // This is a bad base case don't use it
            else dp[validCode] = 2;
        }
        dp[s] = rec(s, validCodes, dp);
        return dp[s];
    }
};


// Method 3: Recursion without memoization
// Running time: O(2^n) gets TLE
// Auxiliary space: O(26) ~ O(1) due to the validCodes set and count

class Solution {
    string intToString(int n) {
        string s;
        while(n) {
            s += '0' + n%10;
            n = n/10;
        }
        reverse(s.begin(), s.end());
        return s;
    }
    void rec(string s, unordered_set<string> &validCodes, int &count) {
        if(s.empty()) {
            count++;
            return;
        }
        string s1 = s.substr(0, 1);
        if(validCodes.count(s1)) rec(s.substr(1), validCodes, count);
        if(s.size()>1) {
            string s2 = s.substr(0, 2);
            if(validCodes.count(s2)) rec(s.substr(2), validCodes, count);
        }
    }
public:
    int numDecodings(string s) {
        int count = 0;
        unordered_set<string> validCodes;
        for(int i=1; i<=26; i++) validCodes.insert(intToString(i));
        rec(s, validCodes, count);
        return count;
    }
};


class Solution {
    string intToString(int n) {
        string s;
        while(n) {
            s += '0' + n%10;
            n = n/10;
        }
        reverse(s.begin(), s.end());
        // cout<<s<<" ";
        return s;
    }
    void rec(string s, unordered_set<string> &validCodes,  unordered_map<string, int> &dp, int &count) {
        if(s.empty()) {
            count++;
            return;
        }
        string s1 = s.substr(0, 1);
        if(validCodes.count(s1)) rec(s.substr(1), validCodes, dp, count);
        if(s.size()>1) {
            string s2 = s.substr(0, 2);
            if(validCodes.count(s2)) rec(s.substr(2), validCodes, dp, count);
        }
    }
public:
    int numDecodings(string s) {
        int count = 0;
        unordered_set<string> validCodes;
        unordered_map<string, int> dp;
        for(int i=1; i<=26; i++) validCodes.insert(intToString(i));
        rec(s, validCodes, dp, count);
        return count;
    }
};
