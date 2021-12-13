/*
Detect a cycle in a linked list. Note that the head pointer may be 'NULL' if the list is empty.

A Node is defined as:
    struct Node {
        int data;
        struct Node* next;
    }
*/

bool has_cycle(Node* head) {
    if (head == nullptr && head->next == nullptr )
        return 0;

    Node* tortoise = head;
    Node* hare = head;
    bool loopFound = false;

    while(hare != nullptr){

        hare = hare->next;

        if(hare != nullptr){
            hare = hare->next;
            tortoise = tortoise->next;
        }

        if(hare == tortoise){
            loopFound = true;
            break;
        }
    }
    return loopFound;
}
