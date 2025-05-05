// LC#17. Letter Combinations of a Phone Number

// 1a. Recursion that returns vector<string>
// O(n * (3^n or 4^n)) ~ O(n*4^n) where n = size of digits
// O(n) extra and O(n*4^n) for the output vector<string> ans

class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if(digits.empty()) return vector<string>();
        vector<string> res = letterCombinations(digits.substr(1));
        vector<string> ans;
        vector<string> curr;

        if(digits[0] == '2') curr = {"a", "b", "c"};
        if(digits[0] == '3') curr = {"d", "e", "f"};
        if(digits[0] == '4') curr = {"g", "h", "i"};
        if(digits[0] == '5') curr = {"j", "k", "l"};
        if(digits[0] == '6') curr = {"m", "n", "o"};
        if(digits[0] == '7') curr = {"p", "q", "r", "s"};
        if(digits[0] == '8') curr = {"t", "u", "v"};
        if(digits[0] == '9') curr = {"w", "x", "y", "z"};

        if(res.size() == 0) ans = curr;
        else {
            for(int i=0; i<res.size(); i++) {
                for(int j=0; j<curr.size(); j++) {
                    ans.push_back(curr[j] + res[i]);
                }
            }
        }
        return ans;
    }
};

// 1b. Void recursive function
// O(n * (3^n or 4^n)) ~ O(n*4^n) where n = size of digits
// O(n) extra and O(n*4^n) for the output vector<string> ans

class Solution {
public:
    vector<string> res;
    vector<string> digitToChar = {"", "", "abc", "def", "ghi", "jkl", 
                                    "mno", "qprs", "tuv", "wxyz"};

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return res;
        backtrack(0, "", digits);
        return res;
    }

    void backtrack(int i, string curStr, string &digits) {
        if (curStr.size() == digits.size()) {
            res.push_back(curStr);
            return;
        }
        string chars = digitToChar[digits[i] - '0'];
        for (char c : chars) {
            backtrack(i + 1, curStr + c, digits);
        }
    }
};


// 2. Iterative