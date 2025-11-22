/**LC#70. NC1DP1. Climbing Stairs

Running time: O(n);
Auxiliary space: O(2) ~ O(1) due to n1 and n2

**/
class Solution {
public:
    int climbStairs(int n) {
        if(n==1 || n==2) return n;
        int n1 = 1;
        int n2 = 2;
        int ans = 0;
        for(int i=3; i<=n; i++) {
            ans = n1 + n2;
            n1 = n2;
            n2 = ans;
        }
        return ans;
    }
};
    