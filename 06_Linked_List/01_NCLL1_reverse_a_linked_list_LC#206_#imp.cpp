/* LC#206. NCLL1. Reverse Linked List
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
class Solution {
    public:
        // 1. Recursive (Best method) | O(n) time | O(n) space due to the recursion stack (not O(1))
        ListNode* reverseList(ListNode* head) {
            if(head == nullptr || head->next == nullptr) return head;                 // base case
            ListNode* res = reverseList(head->next);                                 // reverse the rest of the list
            head->next->next = head;                                                 // make the next node point back to current
            head->next = nullptr;                                                    // disconnect current node from next
            return res;                                                              // return new head
        }
    
        // 2. Iterative I (easier than Iterative II) | O(n) | O(1) space (Takes less space than recursive function)
        ListNode* reverseList(ListNode* head) {
            if(!head || !head->next) return head;                                    // handle empty or single node list
            ListNode* resultHead = nullptr;                                          // new head of reversed list
            ListNode* curr = head;                                                   // current node being processed
            while(curr) {
                ListNode* currNext = curr->next;                                     // store next node
                curr->next = resultHead;                                             // reverse current node's pointer
                resultHead = curr;                                                   // move resultHead to current node
                curr = currNext;                                                     // move to next node
            } 
            return resultHead;                                                       // return new head
        }
    
        // 3. Iterative II (my custom code) | O(n) | O(1)
        ListNode* reverseList(ListNode* head) {
            if(!head || !head->next) return head;                                    // handle empty or single node list
            ListNode* curr = head;                                                   // current node
            ListNode* currNext = curr -> next;                                       // next node
            curr->next = nullptr;                                                    // disconnect the first node
            while(currNext) {
                ListNode* currNextNext = currNext -> next;                           // store next of next
                currNext -> next = curr;                                             // reverse link
                curr = currNext;                                                     // move curr forward
                currNext = currNextNext;                                             // move currNext forward
            }
            return curr;                                                             // return new head
        }
    };
    