/* 204. Count Primes
Given an integer n, return the number of prime numbers that are strictly 
less than n.

### Approach: Sieve of Eratosthenes
1. **Initialize Primality Array**:
   - Create a boolean array `isPrime` of size `n+1` and initialize all elements to `true`.
   - Mark `0` and `1` as non-prime since they are not prime numbers.

2. **Mark Non-Prime Numbers**:
   - Iterate from `2` to `sqrt(n)`:
     - If a number `i` is prime, mark all its multiples starting from `i * i` as non-prime.
     - Use a step size of `i` to efficiently mark multiples.

3. **Collect Prime Numbers**:
   - Iterate through the `isPrime` array from `2` to `n-1`.
   - Collect all numbers marked as `true` in the `isPrime` array.

4. **Return the Count**:
   - Return the size of the list of prime numbers.

5. **Time Complexity**:
   - The outer loop runs up to `sqrt(n)`, and the inner loop marks multiples of each prime.
   - The total complexity is O(n * log(log(n))) due to the harmonic series.

6. **Space Complexity**:
   - The `isPrime` array requires O(n) space to store the primality of each number.
*/

// Time Complexity: O(n * log(log(n)))
// - The Sieve of Eratosthenes algorithm marks non-prime numbers in O(n * log(log(n))) time.

// Space Complexity: O(n)
// - The `isPrime` vector requires O(n) space to store the primality of each number.

class Solution {
public:
    int countPrimes(int n) {
        vector<bool> isPrime(n+1, true); // all true   // [#IMP] Initialize all numbers as prime
        for(int i = 2; i * i <= n; i++) {              // Iterate up to the square root of n
            if(isPrime[i]) {                           // If the number i is prime
                for(int j = i * i; j <= n; j += i)     // Mark all multiples of i as non-prime starting from i^2
                    isPrime[j] = false;
            }
        }
        vector<int> primes;                            // Store all prime numbers
        for(int i = 2; i < n; i++)                     // Collect primes less than n
            if(isPrime[i]) primes.push_back(i);
        return primes.size();                          // Return the count of primes
    }
};

// or, same as above but using a count variable instead of primes array

class Solution {
public:
    int countPrimes(int n) {
        vector<bool> isPrime(n+1, true);
        for(int i=2; i*i<=n; i++) {
            if(isPrime[i]) {
                for(int j=i*i; j<=n; j+=i) isPrime[j] = false;
            }
        }
        int ans = 0;
        for(int i=2; i<n; i++) if(isPrime[i]) ans++;
        return ans;
    }
};