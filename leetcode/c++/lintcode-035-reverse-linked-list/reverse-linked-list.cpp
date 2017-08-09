/*
 * http://www.lintcode.com/en/problem/reverse-linked-list
 */


class Solution {
public:
    /**
     * @param head: The first node of linked list.
     * @return: The new head of reversed linked list.
     */
    ListNode *reverse(ListNode *head) {
        ListNode *prev = NULL;
        while (head != NULL) {
            ListNode *temp = head->next;
            head->next = prev;
            prev = head;
            head = temp;
        }
        return prev;
    }
};
