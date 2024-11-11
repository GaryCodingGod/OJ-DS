//Please complete functionsinsertElement, search, and height in class BinarySearchTree.
//Function insertElement will insert an element into binary search tree.
//Function search return true if element can be found in the binary search tree, return false if not.
//Function height return the height of the binary search tree.
#include <iostream>
#include <string>

using namespace std;

template<class T>
class BinarySearchTree {
private:
  struct Node {
    T data;
    Node *left, *right;
    Node(T val) : data(val), left(nullptr), right(nullptr) {}  // 節點的建構函數
  };
  
  Node *root;

  void inorder(Node *cur) {
    if(!cur)
      return;
    inorder(cur->left);
    cout << cur->data << " ";
    inorder(cur->right);
  }

  Node* insertElement(Node* node, T d) {
    if (node == nullptr) {
      return new Node(d);
    }
    if (d < node->data) {
      node->left = insertElement(node->left, d);
    } else if (d > node->data) {
      node->right = insertElement(node->right, d);
    }
    return node;
  }

  bool search(Node* node, T d) {
    if (node == nullptr) {
      return false;
    }
    if (node->data == d) {
      return true;
    }
    if (d < node->data) {
      return search(node->left, d);
    }
    return search(node->right, d);
  }

  int height(Node* node) {
    if (node == nullptr) {
      return -1; // 空樹高度為 -1
    }
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return max(leftHeight, rightHeight) + 1;
  }

public:
  BinarySearchTree() : root(nullptr) {}

  void insertElement(T d) {
    root = insertElement(root, d);
  }

  bool search(T d) {
    return search(root, d);
  }

  int height() {
    return height(root);
  }

  void print() {
    inorder(root);
    cout << endl;
  }
};

int main() {
  int data;
  string command;
  BinarySearchTree<int> *bst = new BinarySearchTree<int>();
  while(true) {
    cin >> command;
    if(command == "insert") {
      cin >> data;
      bst->insertElement(data);
    }
    else if(command == "search") {
      cin >> data;
      if(bst->search(data))
        cout << "true" << endl;
      else
        cout << "false" << endl;
    }
    else if(command == "height") {
      cout << bst->height() << endl;
    }
    else if(command == "print") {
      bst->print();
    }
    else if(command == "exit") {
      break;
    }
  }
  delete bst;
  return 0;
}