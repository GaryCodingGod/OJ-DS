#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class BinaryTreeInArray {
private:
    vector<int> tree; 

    // 使用 stack 進行 Inorder 遍歷
    void inorder() {
        stack<int> s;
        int index = 0;
        while (!s.empty() || index < tree.size()) {
            while (index < tree.size() && tree[index] != -1) {
                s.push(index);
                index = 2 * index + 1;
            }
            if (!s.empty()) {
                index = s.top();
                s.pop();
                cout << tree[index] << " ";
                index = 2 * index + 2;
            }
        }
        cout << endl;
    }

    // 使用 stack 進行 Preorder 遍歷
    void preorder() {
        stack<int> s;
        if (!tree.empty() && tree[0] != -1) {
            s.push(0); 
        }
        while (!s.empty()) {
            int index = s.top();
            s.pop();
            cout << tree[index] << " ";
            int right = 2 * index + 2; 
            if (right < tree.size() && tree[right] != -1) {
                s.push(right);
            }
            int left = 2 * index + 1; 
            if (left < tree.size() && tree[left] != -1) {
                s.push(left);
            }
        }
        cout << endl;
    }

    // 使用 stack 進行 Postorder 遍歷
    void postorder() {
        stack<int> s1, s2;
        if (!tree.empty() && tree[0] != -1) {
            s1.push(0); 
        }
        while (!s1.empty()) {
            int index = s1.top();
            s1.pop();
            s2.push(index);
            int left = 2 * index + 1; 
            if (left < tree.size() && tree[left] != -1) {
                s1.push(left);
            }
            int right = 2 * index + 2; 
            if (right < tree.size() && tree[right] != -1) {
                s1.push(right);
            }
        }
        while (!s2.empty()) {
            cout << tree[s2.top()] << " ";
            s2.pop();
        }
        cout << endl;
    }

public:
    BinaryTreeInArray() {}
    void addElement(int data) {
        tree.push_back(data);
    }

    // a) 顯示二元樹
    void displayTree() {
        for (int i = 0; i < tree.size(); i++) {
            cout << tree[i] << " ";
        }
        cout << endl;
    }

    // b) Inorder 遍歷
    void displayInorder() {
        inorder();
    }

    // c) Preorder 遍歷
    void displayPreorder() {
        preorder();
    }

    // d) Postorder 遍歷
    void displayPostorder() {
        postorder();
    }

    // e) 利用 Postorder 重建二元樹
    void RebuildPostorder(vector<int> postorder) {
        tree.clear();
        for (auto it = postorder.rbegin(); it != postorder.rend(); ++it) {
            tree.push_back(*it);
        }
    }

    // f) 判定深度與高度
    void calculateDepthAndHeight() {
        int depth = 0, totalNodes = tree.size();
        while (totalNodes > 1) {
            totalNodes /= 2;
            depth++;
        }
        cout << "Depth: " << depth << ", Height: " << depth << endl;
    }

    // g) 判定 Terminal Nodes 與 Internal Nodes
    void findNodes() {
        vector<int> terminalNodes;
        vector<int> internalNodes;
        for (int i = 0; i < tree.size(); i++) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left >= tree.size() && right >= tree.size()) {
                terminalNodes.push_back(tree[i]); // 無子節點
            } else {
                internalNodes.push_back(tree[i]); // 至少有一個子節點
            }
        }

        cout << "Terminal Nodes: ";
        for (auto n : terminalNodes) cout << n << " ";
        cout << endl;

        cout << "Internal Nodes: ";
        for (auto n : internalNodes) cout << n << " ";
        cout << endl;
    }
};

int main() {
    BinaryTreeInArray tree;

    cout << "Input nodes for the binary tree (e.g., 1 2 3 4 5 -1 -1):" << endl;
    int data;
    while (cin >> data) {
        if (data == -1) break; 
        tree.addElement(data);
    }
    cout << "Binary Tree in Array Representation: ";
    tree.displayTree();

    cout << "Inorder Traversal: ";
    tree.displayInorder();

    cout << "Preorder Traversal: ";
    tree.displayPreorder();

    cout << "Postorder Traversal: ";
    tree.displayPostorder();

    cout << "Depth and Height: ";
    tree.calculateDepthAndHeight();

    cout << "Terminal Nodes and Internal Nodes: ";
    tree.findNodes();

    return 0;
}
