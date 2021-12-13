

/*
 * Complete the 'sortedInsert' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts following parameters:
 *  1. INTEGER_DOUBLY_LINKED_LIST llist
 *  2. INTEGER data
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

DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data) {
    DoublyLinkedListNode* inserted = new DoublyLinkedListNode(data);
    DoublyLinkedListNode* head = llist;

    if (llist == nullptr)
        return inserted;

    while (llist->next != nullptr &&
            data > llist->data) {
        llist = llist->next;
    }

    if (llist->next == nullptr && data > llist->data){
        inserted->next = llist->next;
        inserted->prev = llist;
        llist->next = inserted;
    } else if(llist->prev == nullptr) {
        inserted->next = llist;
        llist->prev = inserted;
        head = inserted;
    } else {
        inserted->next = llist;
        inserted->prev = llist->prev;
        llist->prev->next = inserted;
        llist->prev = inserted;
    }

    return head;
}
