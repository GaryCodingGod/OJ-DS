//Please finish the three sorting function in template, bubble sort, selection sort and insertion sort.
//When swap, you should swap node itself rather then the value in each node.
//You will get 80 point if you finish one of three, 90 point if two and 100 point for all three.
#include <iostream>
#include <cstdlib>
#include <ctime>

#define SIZE 100

using namespace std;

class Node
{
public:
    Node()
    {
        next = NULL;
        pre = NULL;
    }
    Node(int n)
    {
        data = n;
        next = NULL;
        pre = NULL;
    }
    int getData() { return data; }
    Node *getNext() { return next; }
    Node *getPre() { return pre; }
    void setData(int d) { data = d; }
    void setNext(Node *n) { next = n; }
    void setPre(Node *p) { pre = p; }
private:
    int data;
    Node *next, *pre;
};

class List
{
public:
    List() { list = NULL; }
    List(int n) { generate(n); }

    void generate(int n)
    {
        int j;
        list = NULL;
        for (j = 0; j < n; j++)
            generate();
    }

    void generate()
    {
        Node *buf = new Node(rand());
        buf->setNext(list);
        if (list != NULL)
            list->setPre(buf);
        list = buf;
    }

    void swapNodes(Node *a, Node *b)
    {
        if (a == b) return;

        Node *prevA = a->getPre();
        Node *nextA = a->getNext();
        Node *prevB = b->getPre();
        Node *nextB = b->getNext();

        // If a and b are adjacent nodes, special handling is needed.
        if (nextA == b) {
            a->setNext(nextB);
            if (nextB != NULL) nextB->setPre(a);
            a->setPre(b);

            b->setNext(a);
            b->setPre(prevA);
            if (prevA != NULL) prevA->setNext(b);
            else list = b;
        } else if (nextB == a) {
            b->setNext(nextA);
            if (nextA != NULL) nextA->setPre(b);
            b->setPre(a);

            a->setNext(b);
            a->setPre(prevB);
            if (prevB != NULL) prevB->setNext(a);
            else list = a;
        } else {
            // Non-adjacent nodes
            a->setNext(nextB);
            if (nextB != NULL) nextB->setPre(a);
            a->setPre(prevB);
            if (prevB != NULL) prevB->setNext(a);

            b->setNext(nextA);
            if (nextA != NULL) nextA->setPre(b);
            b->setPre(prevA);
            if (prevA != NULL) prevA->setNext(b);
            else list = b;
        }
    }

    void bubbleSort()
    {
        if (list == NULL) return;

        bool swapped;
        Node *cur;

        do {
            swapped = false;
            cur = list;

            while (cur->getNext() != NULL) {
                if (cur->getData() > cur->getNext()->getData()) {
                    swapNodes(cur, cur->getNext());
                    swapped = true;
                } else {
                    cur = cur->getNext();
                }
            }
        } while (swapped);
    }

    void selectionSort()
    {
        if (list == NULL) return;

        Node *cur = list;

        while (cur != NULL) {
            Node *min = cur;
            Node *nxt = cur->getNext();

            while (nxt != NULL) {
                if (nxt->getData() < min->getData()) {
                    min = nxt;
                }
                nxt = nxt->getNext();
            }

            if (min != cur) {
                swapNodes(cur, min);
            }
            cur = cur->getNext();
        }
    }

    void insertionSort()
    {
        if (list == NULL) return;

        Node *cur = list->getNext();

        while (cur != NULL) {
            Node *insert = cur;
            Node *pre = cur->getPre();

            while (pre != NULL && insert->getData() < pre->getData()) {
                pre = pre->getPre();
            }

            Node *next = cur->getNext();

            // Remove the current node
            if (cur->getPre() != NULL)
                cur->getPre()->setNext(cur->getNext());
            if (cur->getNext() != NULL)
                cur->getNext()->setPre(cur->getPre());

            // Insert the node at the correct position
            if (pre == NULL) {
                cur->setNext(list);
                list->setPre(cur);
                cur->setPre(NULL);
                list = cur;
            } else {
                cur->setNext(pre->getNext());
                cur->setPre(pre);
                if (pre->getNext() != NULL)
                    pre->getNext()->setPre(cur);
                pre->setNext(cur);
            }

            cur = next;
        }
    }

    void print()
    {
        Node *cur = list;
        while (cur != NULL)
        {
            cout << cur->getData() << " ";
            cur = cur->getNext();
        }
        cout << endl;
    }

private:
    Node *list;
};

int main()
{
    srand(time(NULL));
 List *l = new List(10);
 l->print();
 l->bubbleSort();
 l->print();
 
 l = new List(10);
 l->print();
 l->insertionSort();
 l->print();
 
 l = new List(10);
 l->print();
 l->selectionSort();
 l->print();

    return 0;
}