

// Complete the findMergeNode function below.

/*
 * For your reference:
 *
 * SinglyLinkedListNode {
 *     int data;
 *     SinglyLinkedListNode* next;
 * };
 *
 */
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {

    std::unordered_map<SinglyLinkedListNode*, char> visitedNodes;

    while (head1->next != nullptr) {
        visitedNodes.insert({head1, 0});
        head1 = head1->next;
    }

    while (head2->next != nullptr) {
        if (visitedNodes.count(head2))
            break;
        head2 = head2->next;
    }

    return head2->data;
}
