/* LC#23. NCLL10. Merge k Sorted Lists

This problem uses mergeTwoSortedLists() LC#21 or NCLL2

Approach:
1. The solution uses a sequential merging strategy for k sorted lists
2. Helper function mergeTwoSortedLists merges two lists using recursion:
  - Base cases handle empty lists
  - Compare current nodes and recursively build result
  - Always returns head of newly merged list
3. Main mergeKLists function:
  - Handles empty input case
  - Merges lists sequentially: list[0] with list[1], result with list[2], and so on
  - Each merge result is stored back in the lists array
  - Final result is in the last position of the array
4. Time complexity is O(n*k) because each node is processed k-1 times in worst case
5. Not optimal compared to divide-and-conquer approach which would be O(n log k)

There's also a heap based method. (TODO)

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

/*
a. mergeTwoSortedLists:
- Time: O(n) where n is the total number of nodes in both lists
- Space: O(k) where k is the depth of recursion (equals length of smaller list)

b. mergeKLists:
- Time: O(n*k) where n is total number of nodes across all lists and k is number of lists
- Space: O(logk) from recursive stack in mergeTwoSortedLists
*/

class Solution {
    ListNode * mergeTwoSortedLists(ListNode* head1, ListNode* head2) {
        if(!head1) return head2;                                // If list1 is empty, return list2
        if(!head2) return head1;                                // If list2 is empty, return list1
        if(head1->val <= head2->val) {                          // If value in list1 is smaller
            head1->next = mergeTwoSortedLists(head1->next, head2); // Recursively merge the rest
            return head1;                                       // Return list1 as the new head
        }
        else {                                                  // If value in list2 is smaller
            head2->next = mergeTwoSortedLists(head1, head2->next); // Recursively merge the rest
            return head2;                                       // Return list2 as the new head
        }
    }
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.empty()) return nullptr;                       // [#IMP] base case i.e. if no lists, return null
        int n = lists.size();                                   // Get number of lists
        for(int i=0; i<n-1; i++) {                              // Iterate through n-1 pairs
            lists[i+1] = mergeTwoSortedLists(lists[i], lists[i+1]); // Merge current result with next list
        }
        return lists[n-1];                                      // Return final merged list
    }
};

// Method 2. Divide and Conquer

// Time Complexity:
// ----------------
// Let k = number of linked lists
//     n = total number of nodes across all lists
//
// The divide step splits the k lists in log(k) levels (like merge sort).
// At each level, all nodes (n) are processed once during merging.
//
// Therefore, total time complexity = O(n * log(k))


// Space Complexity:
// -----------------
// 1. No extra space is used for the divide-and-conquer logic itself (just recursion stack).
// 2. The conquer (merge) step uses recursion. In the worst case, the recursion depth 
//    can go up to O(log(k)) for divide, and O(n) for merging (conquer).
//
// So,
// - If using recursive merging (as in conquer function above): O(n) stack space
// - If conquer used iterative merge instead: O(log(k)) stack space (due to divide)
//
// Final space complexity = O(n) due to recursive merge calls


// 2a. Divide and Conquer using recursion similar to mergeSort():
// O(nlogk) faster than method 1 | 0ms beats 100%
// O(logk) due to the recursion stack

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return divide(0, lists.size()-1, lists);                 // Start divide and conquer on full list range
    }

    ListNode* divide(int start, int end, vector<ListNode*> &lists) {
        if(start > end) return nullptr;                          // Base case: invalid range
        if(start == end) return lists[start];                    // Base case: only one list to return
        int mid = (start + end) / 2;                             // Find the midpoint
        ListNode* left = divide(start, mid, lists);             // Recursively divide left half
        ListNode* right = divide(mid + 1, end, lists);          // Recursively divide right half
        return conquer(left, right);                            // Merge the two halves
    }

    ListNode* conquer(ListNode* head1, ListNode* head2) {        // conquer is simply merging two sorted lists
        if(!head1) return head2;                                 // If list1 is empty, return list2
        if(!head2) return head1;                                 // If list2 is empty, return list1
        if(head1->val <= head2->val) {                           // Choose node from list1
            head1->next = conquer(head1->next, head2);           // Recurse on next of list1 and head2
            return head1;                                        // Return current node of list1
        } else {                                                 // Choose node from list2
            head2->next = conquer(head1, head2->next);           // Recurse on head1 and next of list2
            return head2;                                        // Return current node of list2
        }
    }
};

// 2b. Divide and Conquer using interation
// Time Complexity: O(n * log k)
// - n = total number of nodes
// - k = number of linked lists
// - log k levels of merge, each touching all n nodes once

// Space Complexity: O(log k)
// - Due to recursion stack in divide-and-conquer (log k depth)


class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return divide(0, lists.size()-1, lists);                 // Start divide and conquer from full range
    }

    ListNode* divide(int start, int end, vector<ListNode*> &lists) {
        if(start > end) return nullptr;                          // No lists to merge
        if(start == end) return lists[start];                    // Only one list, return as is
        int mid = (start + end) / 2;                             // Find midpoint
        ListNode* left = divide(start, mid, lists);              // Recursively divide left half
        ListNode* right = divide(mid + 1, end, lists);           // Recursively divide right half
        return conquer(left, right);                             // Merge the two halves
    }

    ListNode* conquer(ListNode* head1, ListNode* head2) {
        // Dummy node to simplify merging logic
        ListNode* dummy = new ListNode(0); 
        ListNode* curr = dummy;
        while(curr && head1 && head2) {
            if(head1->val <= head2->val) {                       // Append smaller node to result
                curr->next = head1;
                head1 = head1->next;
            }
            else {
                curr->next = head2;
                head2 = head2->next;
            }
            curr = curr->next;                                   // Move to next position
        }
        if(head1) curr->next = head1;                            // Append remaining nodes from head1
        if(head2) curr->next = head2;                            // Append remaining nodes from head2
        return dummy->next;                                      // Return merged list starting after dummy
    }
};


