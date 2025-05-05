/* Given a string, return all the partitions of the string.
Note: 
1. No. of total partitions of an array or string of size n = 2^(n-1)
2. There are two different recursion trees giving the same output.
    a. at each i (or each substring): partition from i to n-1 (from 0 to n-1) (prefer this approach)
    b. at each i: whether to partition or not and uses prev (TODO - yet to implement)
*/

// 1. This code gives all the paritions of a string but doesn't check for palindromes
// O(2^(n-1)) ~ O(2^n)
// O(n) due to the recursion stack without counting output space which is O(n*2^n)

#include<iostream>
#include<vector>
using namespace std;


class Solution {
    void rec(string s, vector<string> partition, vector<vector<string>> &ans) {
        int n = s.size();
        if(n==0) {                                         // Base case: string is empty
            ans.push_back(partition);                      // Add current partition to results
            return;
        }
        for(int i=0; i<n; i++) {                          // Try all possible first parts
            string subStr = s.substr(0, i+1);             // Extract substring from 0 to i
            partition.push_back(subStr);                  // Add substring to current partition
            rec(s.substr(i+1), partition, ans);           // Recurse with remaining string
            partition.pop_back();                         // Backtrack: remove last substring
        }
    }
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> ans;                       // Store all valid partitions
        rec(s, vector<string>(), ans);                    // Start recursion with empty partition
        return ans;                                       // Return all partitions
    }
};

int main() {
    cout<<"Input string: ";
    string s;
    cin>>s;
    Solution sol;
    vector<vector<string>> ans = sol.partition(s);
    cout<<endl<<"The partitions of the given string "<<s<<" are:"<<endl;
    for(int i=0; i<ans.size(); i++) {
        if(i==0) cout<<"[";
        for(int j=0; j<ans[i].size(); j++) {
            if(j==0) cout<<"[";
            if(j!=ans[i].size()-1) cout<<ans[i][j]<<", ";
            else if(i!=ans.size()-1) cout<<ans[i][j]<<"], ";
            else cout<<ans[i][j]<<"]";
        }
        if(i==ans.size()-1) cout<<"]";
    }
    return 0;
}