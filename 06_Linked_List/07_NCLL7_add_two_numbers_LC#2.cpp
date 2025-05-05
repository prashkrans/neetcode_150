/* LC#2. NCLL7. Add Two Numbers

Approaches:
1. Recursive (Best)
2. Iterative using a dummy (TODO)

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

// 1a. Recursion with check for 4 cases
// O(max(n, m)) where n = size of list1 and m = size of list 2
// O(1) extra and O(max(n, m)) for the resutlant list
class Solution {
    ListNode* add(ListNode* head1, ListNode* head2, int carry) {
        if(!head1 && !head2 && carry == 0) return nullptr;
        int a = 0, b = 0, c = 0;
        if(head1) a = head1->val;
        if(head2) b = head2->val;
        c = a + b + carry; // Note: c != a + b only but a + b + carry
        int rem = c%10;
        carry = c/10;
        ListNode* newNode = new ListNode(rem);  // Note: new ListNode(c) is incorrect
        if(head1 && head2) newNode->next = add(head1->next, head2->next, carry); // 4 cases
        else if(head1) newNode->next = add(head1->next, nullptr, carry);
        else if(head2) newNode->next = add(nullptr, head2->next, carry);
        else newNode->next = add(nullptr, nullptr, carry);
        return newNode;
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return add(l1, l2, 0);
    }
};

// 1b. Recursion with check for 4 cases (same as above) (Prefer this approach)
// O(max(n, m)) where n = size of list1 and m = size of list 2
// O(1) extra and O(max(n, m)) for the resutlant list
class Solution {
    ListNode* add(ListNode* head1, ListNode* head2, int carry) {
        if(!head1 && !head2 && carry == 0) return nullptr;
        // There are 4 cases here: (next, next), (NULL, next), (next, NULL), (NULL, NULL)
        ListNode* headNext1 = nullptr;
        ListNode* headNext2 = nullptr;
        int a = 0, b = 0, c = 0;
        if(head1) {
            a = head1->val;
            headNext1 = head1->next;
        }
        if(head2) {
            b = head2->val;
            headNext2 = head2->next;
        }
        c = a + b + carry; // Note: c != a + b only but a + b + carry
        int rem = c%10;
        carry = c/10;
        ListNode* newNode = new ListNode(rem);  // Note: new ListNode(c) is incorrect
        newNode->next = add(headNext1, headNext2, carry); 
        return newNode;
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return add(l1, l2, 0);
    }
};