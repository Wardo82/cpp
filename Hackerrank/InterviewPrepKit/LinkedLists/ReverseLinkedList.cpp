

/*
 * Complete the 'reverse' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts INTEGER_DOUBLY_LINKED_LIST llist as parameter.
 */

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 *     int data;
 *     DoublyLinkedListNode* next;
 *     DoublyLinkedListNode* prev;
 * };
 *
 */

DoublyLinkedListNode* reverse(DoublyLinkedListNode* llist) {
    if (llist == nullptr || llist->next == nullptr)
        return llist;

    // First, the head turns to tail
    DoublyLinkedListNode* tail = llist;
    tail->prev = llist->next;
    llist = llist->next; // Step
    tail->next = nullptr;
    // Second, turn the middle nodes
    DoublyLinkedListNode* tmp;
    while (llist->next != nullptr) {
        tmp = llist->next;
        llist->next = llist->prev;
        llist->prev = tmp->next;
        llist = tmp;
    }
    // Third, the tail turns to head;
    DoublyLinkedListNode* head = llist;
    head->next = head->prev;
    head->prev = nullptr;

    return head;
}
