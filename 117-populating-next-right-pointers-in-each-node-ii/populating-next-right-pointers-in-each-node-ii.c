/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *left;
 *     struct Node *right;
 *     struct Node *next;
 * };
 */

struct Node* connect(struct Node* root) {
    if (root == NULL)
        return NULL;

    struct Node *level = root;

    while (level != NULL) {

        // Dummy node for the next level
        struct Node dummy;
        dummy.next = NULL;

        struct Node *tail = &dummy;

        // Traverse current level using next pointers
        struct Node *curr = level;

        while (curr != NULL) {

            if (curr->left != NULL) {
                tail->next = curr->left;
                tail = tail->next;
            }

            if (curr->right != NULL) {
                tail->next = curr->right;
                tail = tail->next;
            }

            curr = curr->next;
        }

        // First node of next level
        level = dummy.next;
    }

    return root;
}
//krish