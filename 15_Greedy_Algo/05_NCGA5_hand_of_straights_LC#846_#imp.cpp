/* LC#846. NCGA5. Hand of Straights (Same problem as LC#1296. Divide Array in Sets of K Consecutive Numbers)
   Problem: Given an array of integers representing cards, determine if it is possible to
   rearrange the cards into groups of consecutive cards of a specified size (groupSize).
   Each group must consist of exactly groupSize cards, and all cards in a group must be
   consecutive.
   
   Example: Input: hand = [1,2,3,4,5], groupSize = 2
            Output: true (can form groups [1,2] and [3,4])

### Approach: Frequency Counting with Manual Selection
1. Create a frequency map (unordered_map) to count how many times each card appears
in the input array. This allows O(1) lookups.
2. Sort the input array in ascending order to ensure cards are processed in sequential
order, which is necessary for forming groups.
3. Iterate through the sorted array. For each card, check if it is still available
in the frequency map. If not, skip to the next card.
4. If the card is available, attempt to form a group of size groupSize starting
from the current card. Decrement the frequency of each card in the group.
5. If any card required to complete the group is missing (frequency is zero),
return false immediately as forming groups is impossible.
6. Continue this process until all cards are processed. If all groups are successfully
formed, return true.
7. The sorting step ensures that groups are formed in ascending order, and the
frequency map ensures efficient tracking of card availability.
*/


// 1. Frequency Counting with Manual Selection (Greedy Approach)
// Time Complexity: O(nlogn) for sorting + O(n) for the loop
// Space Complexity: O(n) for the frequency map
// Note: The solution uses a frequency map to keep track of the counts of each card in the hand.  

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();                                   // Get the size of the hand array
        if(n % groupSize != 0) return false;                  // If total cards can't form groups, return false
        sort(hand.begin(), hand.end());                       // Sort the cards in ascending order
        unordered_map<int, int> freq;                         // Create a frequency map to count occurrences
        for(int i=0; i<n; i++) freq[hand[i]]++;               // Populate the frequency map with card counts
        for(int i=0; i<n; i++) {                              // Iterate through the sorted hand array
            int curr = hand[i];                               // Get the current card value
            if(freq[curr] > 0) {                              // If the current card is still available
                int remSize = groupSize;                      // Initialize remaining group size
                while(remSize > 0) {                          // Loop to form a group of size groupSize
                    if(freq[curr] == 0) return false;         // If a required card is missing, return false
                    freq[curr]--;                             // Decrement the frequency of the current card
                    curr++;                                   // Move to the next card in the sequence
                    remSize--;                                // Decrease the remaining group size
                }
            }
        }
        return true;                                          // Return true if all groups are successfully formed
    }
};


// 1b. Frequency Counting with Manual Selection (Greedy Approach)
// Time Complexity: O(nlogn) for sorting + O(n) for the loop
// Space Complexity: O(n) for the frequency map

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        int n = hand.size();
        if ((n % groupSize) != 0) return false;

        sort(hand.begin(), hand.end());
        unordered_map<int, int> freq;
        for (int card : hand) freq[card]++;

        for (int card : hand) {
            if (freq[card] == 0) continue; // Skip already processed cards

            for (int i = 0; i < groupSize; i++) {
                if (freq[card + i] == 0) return false; // Missing card in sequence
                freq[card + i]--; // Decrement frequency of the card
            }
        }
        return true;
    }
};