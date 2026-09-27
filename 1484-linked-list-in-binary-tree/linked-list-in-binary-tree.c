#include <stdbool.h>

/**
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 *
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

bool match(struct ListNode* head, struct TreeNode* root) {
    if (head == NULL)
        return true;

    if (root == NULL)
        return false;

    if (head->val != root->val)
        return false;

    return match(head->next, root->left) ||
           match(head->next, root->right);
}

bool isSubPath(struct ListNode* head, struct TreeNode* root) {
    if (root == NULL)
        return false;

    if (match(head, root))
        return true;

    return isSubPath(head, root->left) ||
           isSubPath(head, root->right);
}
//krissh