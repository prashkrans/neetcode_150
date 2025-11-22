// LC#621. Task Scheduler

// 1. Math
// O(2m) ~ O(m) due to double pass where m = tasks.size()
// O(26+4) due to the character map of 'A' to 'Z'. 
// Could have also used vector<int> freq(26, 0); and index = tasks[i] - 'A'

// Time Complexity: O(m)
// - The first loop iterates through the tasks array to calculate frequencies, which takes O(m), where m is the size of the tasks array.
// - The second loop iterates through the frequency map, which has at most 26 entries (constant time).
// - Overall complexity is O(m).

// Space Complexity: O(1)
// - The unordered_map stores at most 26 characters (constant space).

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        unordered_map<char, int> mp;                     // Frequency map to count occurrences of each task
        int maxFrequency = 0;                            // Track the maximum frequency of any task
        for(int i = 0; i < tasks.size(); i++) {          // Count frequencies of tasks
            mp[tasks[i]]++;
            maxFrequency = max(maxFrequency, mp[tasks[i]]); // Update the maximum frequency
        }
        int maxFrequencyCount = 0;                       // Count how many tasks have the maximum frequency
        for(auto i : mp) {
            if(i.second == maxFrequency) maxFrequencyCount++;
        }
        
        // Mathematical formula to calculate the minimum time which works if n >= no. of unique elements
        int time = (maxFrequency - 1) * (n + 1) + maxFrequencyCount;

        int m = tasks.size();                            // Total number of tasks
        return max(m, time);                             // Return the larger of the total tasks or the calculated time
    }
};

// 2. Using a max heap and a queue. TODO
