struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0)
        return NULL;

    // Merge lists one by one
    struct ListNode* result = NULL;

    for (int i = 0; i < listsSize; i++) {
        struct ListNode dummy;
        dummy.next = NULL;

        struct ListNode* tail = &dummy;
        struct ListNode* a = result;
        struct ListNode* b = lists[i];

        while (a != NULL && b != NULL) {
            if (a->val <= b->val) {
                tail->next = a;
                a = a->next;
            } else {
                tail->next = b;
                b = b->next;
            }
            tail = tail->next;
        }

        if (a != NULL)
            tail->next = a;
        else
            tail->next = b;

        result = dummy.next;
    }

    return result;
}