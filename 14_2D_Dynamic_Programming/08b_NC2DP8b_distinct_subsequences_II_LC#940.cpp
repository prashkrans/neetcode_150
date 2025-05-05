/* LC#940. NC2DP8b. Distinct Subsequences II
Learn this formula to solve this question:

Approach: f(n) = 2 * f(n+1) - repetition, given f(n) = 1
where repetition = 0 if the character hasn't appeared before,
or repetition = f(prevIndex + 1), where `prevIndex` is the previous occurrence of the character.
Here, i varies from n-1 to 0.

We use an array dp[] where dp[i] represents the count of distinct subsequences up to position i in the string.
For each new character we encounter, we follow this rule:

There are two cases:
a. If the character is new (hasn't appeared before): The number of distinct subsequences doubles.
b. If the character has appeared before: We subtract the count of subsequences that include the previous 
occurrence to remove duplicates.

Thus, the recurrence becomes:
    dp[i] = 2 * dp[i + 1] - repetition

Alternatively, the problem can be solved in the forward direction using:
    f(n) = 2 * f(n - 1) - repetition, given f(0) = 1
where i varies from 1 to n.
*/



// Method 3a. Bottom Up DP (from n-1 to 0) - Prefer this method
// O(n)
// O(n) due to the DP array

class Solution {
public:
    int distinctSubseqII(string s) {
        int n = s.size();                             // Length of input string
        vector<int> dp(n+1, 0);                       // DP array for subsequence counts
        int mod = 1e9 + 7;                            // Modulo value for large numbers
        unordered_map<char, int> mp;                  // Tracks last position of each character
        dp[n] = 1;                                    // Base case: empty subsequence i.e. ""
        for(int i=n-1; i>=0; i--)  {
            int repetition = 0;                       // Tracks duplicate subsequences
            char currCh = s[i];
            if(mp.count(currCh)) repetition = dp[mp[currCh]]; // Get duplicates from last occurrence
            mp[currCh] = i+1;                         // Update position of current character to i + 1 not i 
            // dp[i] = (2 * dp[i+1]) - repetition;    // without mod
            dp[i] = (((2 * dp[i+1]) % mod - repetition % mod) + mod) % mod; // Double previous count and remove duplicates
        }
        return (dp[0] - 1 + mod) % mod;              // Final count minus empty subsequence
    }
};

// Method 3b. Bottom Up DP (from 1 to n)
// O(n)
// O(n) due to the DP array

class Solution {
    public:
        int distinctSubseqII(string s) {
            int n = s.size();
            vector<int> dp(n+1, 0);
            int mod = 1e9 + 7;
            unordered_map<char, int> mp;
            dp[0] = 1;
            for(int i=1; i<=n; i++)  {
                int repetition = 0;
                char currCh = s[i-1]; // Note: dp has size n+1 while s has size of only n
                if(mp.count(currCh)) repetition = dp[mp[currCh]];
                mp[currCh] = i-1;
                // dp[i] = (2 * dp[i-1]) - repetition; // without mod
                dp[i] = (((2 * dp[i-1]) % mod - repetition % mod) + mod) % mod;
            }
            return (dp[n] - 1 + mod) % mod; // Handle modulo correctly when returning
        }
    };