

/*
 * Complete the 'insertNodeAtPosition' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_SINGLY_LINKED_LIST llist
 *  2. INTEGER data
 *  3. INTEGER position
 */


SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
    if (llist == nullptr)
        return new SinglyLinkedListNode(data);
    if (position == 0)
        return llist;

    SinglyLinkedListNode* head = llist;
    SinglyLinkedListNode* old = llist;

    for (int i = 0; i < position; i++) {
        old = llist;
        llist =  llist->next;
    }


    SinglyLinkedListNode* inserted = new SinglyLinkedListNode(data);
    old->next = inserted;
    inserted->next = llist;

    return head;
}
