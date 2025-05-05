/* NCBM 1 to 7 i.e. NeetCode Bit Manipulation 1 to 7
 * 
 * 1. Single Number LC# 136
 * 2. Hamming Weight LC# 191
 * 3. Counting Bits LC# 338
 * 4. Reverse Bits LC# 190
 * 5. Missing Number LC# 268
 * 6. Sum of Two Integers LC# 371
 * 7. Reverse Integer 
 */



class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int xorVal = 0; // since x ^ 0 = x
        for(auto num: nums) xorVal = xorVal ^ num; // since x ^ x = 0
        return xorVal;
    }
};


// #######################

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        while(n) {
            count++;
            n = n & (n - 1);
        }
        return count;
    }
};

class Solution {
public:
    int hammingWeight(uint32_t n) {
        int count = 0;
        for(int i=0; i<32; i++) {
            if(n & (1 << i)) count++;
        }
        return count;
    }
};

// #######################

class Solution {
    int noOfSetBits(int x) {
        int count = 0;
        while(x) {
            x = x & x-1;
            count++;
        }
        return count;
    }
public:
    vector<int> countBits(int n) {
        vector<int> ans;
        for(int i=0; i<=n; i++) ans.push_back(noOfSetBits(i));
        return ans;    
    }
};


// #######################

// Reverse bits:

class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        int x = 0;
        for(int i=0; i<32; i++) {
            if(n & 1<<i) x = x | 1 << (32-i-1);
        }
        return x;
    }
};


// #######################


class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int xorVal = 0;
        for(int i=0; i<nums.size(); i++) xorVal ^= nums[i]; // xor of all the num in nums i.e.  nums[0] to nums[n-1]
        for(int i=1; i<=nums.size(); i++) xorVal ^= i;		// xor with 1 to n i.e i from 1 to n
        return xorVal;
    }
};

// or, 

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        long long sumToNTerms = (n*(n+1))/2;
        long long sum = 0;
        for(auto num: nums) sum += num;
        return (sumToNTerms - sum);
    }
};




// #######################


class Solution {
public:
    int getSum(int a, int b) {
        int c = 0;
        int carry = 0;
        for(int i=0; i<32; i++) {
            bool bitA = (a & (1 << i)) != 0;
            bool bitB = (b & (1 << i)) != 0;
            
            if (carry == 0) {
                if(!bitA && !bitB) {
                    // 0 + 0 = 0, carry = 0
                    // bit remains 0
                } 
                else if(bitA && bitB) {
                    // 1 + 1 = 0, carry = 1
                    carry = 1;
                    // bit remains 0
                }
                else {
                    // 0 + 1 or 1 + 0 = 1, carry = 0
                    c |= (1 << i);
                }
            }
            else { // carry == 1
                if(!bitA && !bitB) {
                    // 0 + 0 + 1(carry) = 1, carry = 0
                    c |= (1 << i);
                    carry = 0;
                }
                else if(bitA && bitB) {
                    // 1 + 1 + 1(carry) = 1, carry = 1
                    c |= (1 << i);
                    // carry remains 1
                }
                else {
                    // 0 + 1 + 1(carry) or 1 + 0 + 1(carry) = 0, carry = 1
                    // bit remains 0
                    // carry remains 1
                }
            }
        }
        return c;
    }
};

// or,

class Solution {
public:
    int getSum(int a, int b) {
        while(b) {
            int carry = a & b;
            a = a ^ b;
            b = carry << 1;
        }
        return a;
    }
};


// #######################

// Used direct solution (which is not allowed) and not bitmap
class Solution {
public:
    long long rec(int x, int i) {
        if(x == 0) return 0;
        int rem = x % 10;
        return pow(10, i) * rem + rec(x / 10, i-1);
    }
    int reverse(int x) {
        int n = x;
        int count = 0;
        while(n) {
            n = n/10;
            count++;
        }
        long long ans = rec(x, count-1);
        cout<<ans<<endl;
        if(ans < INT_MIN || ans > INT_MAX) return 0;
        else return ans;
    }
};


