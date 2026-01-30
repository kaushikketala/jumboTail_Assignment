#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    bool isEnd;
    unordered_map<char, TrieNode*> children;
    TrieNode() : isEnd(false) {}
};

class Trie {
    TrieNode* root;

    void dfs(TrieNode* node, string prefix, vector<string>& res) {
        if (node->isEnd)
            res.push_back(prefix);

        for (auto& it : node->children)
            dfs(it.second, prefix + it.first, res);
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children[c])
                curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->isEnd = true;
    }

    vector<string> autocomplete(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            if (!curr->children[c])
                return {};
            curr = curr->children[c];
        }

        vector<string> res;
        dfs(curr, prefix, res);
        return res;
    }
};

int main() {
    Trie trie;

    // Insert search terms (products)
    vector<string> products = {
        "iphone",
        "iphone 13",
        "iphone 14",
        "iphone cover",
        "iphone charger",
        "ipad",
        "iwatch",
        "samsung phone"
    };

    for (auto& p : products)
        trie.insert(p);

    string input;
    cout << "Search: ";
    cin >> input;

    auto suggestions = trie.autocomplete(input);

    cout << "Suggestions:\n";
    for (auto& s : suggestions)
        cout << s << endl;
}
