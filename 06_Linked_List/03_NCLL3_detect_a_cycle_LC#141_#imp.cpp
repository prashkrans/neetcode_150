/* LC#141. Linked List Cycle
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

// 1. Using visited array as in a graph
// O(n) if using unordered set
// O(n) due to the unordered set

class Solution {
public:
    bool hasCycle(ListNode* head) {
        unordered_set<ListNode*> st;
        while(head) {
            if(st.find(head) != st.end()) return true;
            st.insert(head);
            head = head->next;
        }
        return false;
    }
};


// 2. Fast and Slow pointers
// O(n)
// O(1) better than method 1

class Solution {
public:
    bool hasCycle(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if(slow == fast) return true;
        }
        return false;
    }
};