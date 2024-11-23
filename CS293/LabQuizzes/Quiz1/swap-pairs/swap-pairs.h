#ifndef REVERSE_LINKED_LIST_H
#define REVERSE_LINKED_LIST_H

struct Node {
    const int data;
    Node* link;

    Node(int val) : data(val), link(nullptr) {}
};

void reverseAdjacentNodes(Node*& head);
void append(Node*& head, int new_data);
void printList(const Node* node);

#endif // REVERSE_LINKED_LIST_H