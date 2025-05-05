/* LC#143. NCLL4. Reorder List

Approach:
1. Slow and Fast pointer => reverse(slow->next) => split at slow => merge(head2, head2)
2. Recursion (TODO)
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

// 1. Slow and Fast pointer
// O(n)
// O(1) due to the slow and fast pointers

class Solution {
    ListNode* reverseList(ListNode* head) {
        if(!head || !head->next) return head;               // Base case: empty or single node
        ListNode* res = reverseList(head->next);            // Recursively reverse the rest
        head->next->next = head;                            // Point next node back to current
        head->next = nullptr;                               // Break original forward link
        return res;                                         // Return new head (original tail)
    }

    ListNode* merge(ListNode* head1, ListNode* head2, int flag) {
        if(!head1) return head2;                            // If list1 empty, return list2
        if(!head2) return head1;                            // If list2 empty, return list1
        if(flag == 0) {                                     // If flag=0, take from list1
            head1->next = merge(head1->next, head2, 1);     // Next node from alternating lists
            return head1;                                   // Return current node from list1
        }
        else {                                              // If flag=1, take from list2
            head2->next = merge(head1, head2->next, 0);     // Next node from alternating lists
            return head2;                                   // Return current node from list2
        }            
    }

public:
    void reorderList(ListNode* head) {
        if(!head || !head->next) return;                    // Early return for 0/1 nodes
        ListNode* slow = head;                              // Slow pointer starts at head
        ListNode* fast = head->next;                        // Fast pointer advances faster. If fast = head; slow is moved to mid + 1 but we want slow to be at mid
        
        while(fast && fast->next) {                         // Find middle using two pointers
            slow = slow->next;                              // Slow moves one step
            fast = fast->next->next;                        // Fast moves two steps
        }
        // cout<<"slow: "<<slow->val<<endl;
        ListNode* head2 = slow->next;                       // Second half starts after slow
        slow->next = nullptr;                               // [#IMP] to split the list in two parts, else merge fails
        head2 = reverseList(head2);                         // Reverse the second half
        merge(head, head2, 0);                              // Merge lists alternating nodes
    }    
};