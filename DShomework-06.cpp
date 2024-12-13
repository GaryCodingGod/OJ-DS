// Write a short C++ function to count the number of nodes in a circularly linked list.
#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {} 
};

class CircularLinkedList {
public:
    Node* head;

    CircularLinkedList() : head(nullptr) {}

    void addNode(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            newNode->next = head; 
        } else {
            Node* temp = head;
            while (temp->next != head) { 
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head; 
        }
    }

    int countNodes() {
        if (head == nullptr) return 0; 
        
        int count = 1;
        Node* current = head->next;

        while (current != head) { // Traverse until we come back to the head
            count++;
            current = current->next;
        }

        return count;
    }
};

int main() {
    CircularLinkedList number;
    number.addNode(1);
    number.addNode(2);
    number.addNode(3);

    cout << " Count nodes in circular linked list: " << number.countNodes() << endl;

    return 0;
}
