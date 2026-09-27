#include <stdlib.h>

struct ListNode* reverseList(struct ListNode* head){
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;

    while(curr !=NULL){
        struct ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}
struct ListNode* removeNodes(struct ListNode* head){
    
    head = reverseList(head);

    int maxVal = -1;

    struct ListNode* curr = head;
    struct ListNode* prev = NULL;

    while(curr !=NULL){
        if(curr->val < maxVal){
            /*
            *Remove current node
            */
            prev->next = curr->next;
            curr = prev->next;
        }
        else{
            maxVal = curr->val;
            prev = curr;
            curr = curr->next;
        }
    }
    return reverseList(head);
}
//krish