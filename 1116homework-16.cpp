//In computer science, a trie, also called digital tree or prefix tree, is a type of k-ary search tree,
//a tree data structure used for locating specific keys from within a set. 
//These keys are most often strings, with links between nodes defined not by the entire key, but by individual characters.]\
//Please finish the constructor and member function in class Trie.
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children; // 儲存子節點
    bool isEndOfWord; // 判斷是否為完整的字串

    TrieNode() : isEndOfWord(false) {}
    ~TrieNode() {
        for (auto &child : children) {
            delete child.second;
        }
    }
};

// 定義 Trie 類別
class Trie {
private:
    TrieNode *root; 

    // 輔助函式：遞迴進行先序遍歷
    void preorderHelper(TrieNode *node, string prefix, int level) {
        if (!node) return;

        if (!prefix.empty()) {
            cout << string(level * 2, ' ') << prefix << endl;
        }

        // 遍歷所有子節點
        for (auto &child : node->children) {
            preorderHelper(child.second, string(1, child.first), level + 1);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    ~Trie() {
        delete root;
    }

    // 插入一個字串
    void insert(string value) {
        TrieNode *current = root;
        for (char ch : value) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new TrieNode();
            }
            current = current->children[ch];
        }
        current->isEndOfWord = true; // 標記結尾
    }

    bool search(string key) {
        TrieNode *current = root;
        for (char ch : key) {
            if (current->children.find(ch) == current->children.end()) {
                return false; // 字符不存在
            }
            current = current->children[ch];
        }
        return current->isEndOfWord; // 確認是否為完整字的結尾
    }

    void preorder() {
        preorderHelper(root, "", 0);
    }
};

int main() {
    Trie *trie = new Trie();
    string command, key, value;

    while (true) {
        cin >> command;
        if (command == "insert") {
            cin >> value;
            trie->insert(value);
        } else if (command == "search") {
            cin >> key;
            if (trie->search(key))
                cout << "exist" << endl;
            else
                cout << "not exist" << endl;
        } else if (command == "print") {
            trie->preorder();
        } else if (command == "exit") {
            break;
        }
    }

    delete trie; 
    return 0;
}