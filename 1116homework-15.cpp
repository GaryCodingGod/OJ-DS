//A suffix tree is a specialized data structure 
//that represents all the suffixes of a given string in a way that allows for fast pattern matching and other string-related operations.
// It is a compressed trie of all the suffixes of the string, where each path from the root to a leaf node represents a suffix of the string.
//Suffix trees are useful in various string processing tasks, such as substring search, pattern matching, and finding longest common substrings.
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class SuffixTreeNode {
public:
    unordered_map<char, SuffixTreeNode*> children; // 子節點映射
    vector<int> indices; // 紀錄當前節點所代表的子字串在原始字串中的起始位置

    ~SuffixTreeNode() {
        for (auto &child : children) {
            delete child.second;
        }
    }
};

class SuffixTree {
private:
    SuffixTreeNode *root; 
    string text; 

    //插入子字串到後綴樹
    void insertSuffix(const string &suffix, int index) {
        SuffixTreeNode *current = root;
        for (char ch : suffix) {
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new SuffixTreeNode();
            }
            current = current->children[ch]; 
            current->indices.push_back(index); // 儲存所有後綴的起始位置
        }
    }

    SuffixTreeNode* findNode(const string &substring) const {
        SuffixTreeNode *current = root;
        for (char ch : substring) {
            if (current->children.find(ch) == current->children.end()) {
                return nullptr; 
            }
            current = current->children[ch];
        }
        return current;
    }

public:
    SuffixTree(const string &text) : text(text) {
        root = new SuffixTreeNode();
        for (size_t i = 0; i < text.size(); ++i) { //從 i 開始的子字串就是後綴 ex:'carrot' --> 'arrot'
            insertSuffix(text.substr(i), i); 
        }
    }

    // 檢查子字串是否存在
    bool exist(const string &substring) const {
        return findNode(substring) != nullptr;
    }

    int count(const string &substring) const {
        SuffixTreeNode *node = findNode(substring);
        return node ? node->indices.size() : 0; // 出現次數 = 陣列大小的原因是因為每一次的出現都會記錄
    }

    ~SuffixTree() {
        delete root;
    }
};

int main() {
    string text;
    cout << "Enter text (press Enter twice to finish):" << endl;
    while (true) {
        string temp;
        getline(cin, temp);
        if (temp.empty()) break;
        text += temp;
    }

    SuffixTree tree(text);

    string query;
    cout << "Enter queries (press Enter twice to finish):" << endl;
    while (true) {
        getline(cin, query);
        if (query.empty()) break;
        cout << "Existence of '" << query << "': " << (tree.exist(query) ? "Yes" : "No") << endl;
        cout << "Count of '" << query << "': " << tree.count(query) << endl;
    }

    return 0;
}
