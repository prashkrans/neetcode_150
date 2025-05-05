/*LC#21. Merge Two Sorted Lists
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
// 1. Recursive
// O(n+m) time | Its not O(max(n, m))
// O(n+m) space due to recursion
// where n = size of list1 and m = size of list2

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        // if(!list1 && !list2) return nullptr; // redundant
        if(!list1) return list2;                // If list1 is empty, return list2
        if(!list2) return list1;                // If list2 is empty, return list1
        if(list1->val <= list2->val) {          // If first node of list1 is smaller
            list1->next = mergeTwoLists(list1->next, list2); // Attach merged result to list1's head
            return list1;                       // Return list1 as the merged list head
        }
        else {                                  // If first node of list2 is smaller
            list2->next = mergeTwoLists(list1, list2->next); // Attach merged result to list2's head
            return list2;                       // Return list2 as the merged list head
        }
    }
};


// 2a. Iterative using a dummy node to handle the edges cases easily (Compact version)
// O(n+m) time and O(n+m) space
// where n = size of list1 and m = size of list2

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* head1, ListNode* head2) {
        // Don't directly create ListNode* curr = new ListNode(0); since we have to return dummy->next at the end
        ListNode* dummy = new ListNode(0); 
        ListNode* curr = dummy;
        while(curr && head1 && head2) {
            if(head1->val <= head2->val) {
                curr->next = head1;
                head1 = head1->next;
            }
            else {
                curr->next = head2;
                head2 = head2->next;
            }
            curr = curr->next;
        }
        if(head1) curr->next = head1;
        if(head2) curr->next = head2;
        return dummy->next;
    }
};

// 2b. Iterative using a dummy node to handle the edges cases easily
// O(n+m) time and O(n+m) space
// where n = size of list1 and m = size of list2

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* head1, ListNode* head2) {
        // Don't directly create ListNode* curr = new ListNode(0); since we have to return dummy->next at the end
        ListNode* dummy = new ListNode(0); 
        ListNode* curr = dummy;
        while(curr) {
            if(head1 == nullptr) {
                curr->next = head2; 
                break;
            }
            if(head2 == nullptr) {
                curr->next = head1; 
                break;
            }
            if(head1->val <= head2->val) {
                curr->next = head1;
                head1 = head1->next;
            }
            else {
                curr->next = head2;
                head2 = head2->next;
            }
            curr = curr->next;
        }
        return dummy->next;
    }
};


