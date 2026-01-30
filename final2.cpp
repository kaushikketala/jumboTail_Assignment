#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    bool isEnd;
    unordered_map<char, TrieNode*> children;
    TrieNode() : isEnd(false) {}
};

class Trie {
    TrieNode* root;

    /* ---------- PREFIX SEARCH ---------- */
    void dfsPrefix(TrieNode* node, string current, vector<string>& res) {
        if (node->isEnd)
            res.push_back(current);

        for (auto it = node->children.begin();
             it != node->children.end(); ++it) {
            dfsPrefix(it->second, current + it->first, res);
        }
    }

    /* ---------- FUZZY SEARCH ---------- */
    void dfsFuzzy(TrieNode* node, const string& word,
                  string current, int idx, int edits,
                  int maxEdits, vector<string>& res) {

        if (edits > maxEdits) return;

        if (idx == word.size()) {
            if (node->isEnd)
                res.push_back(current);

            for (auto it = node->children.begin();
                 it != node->children.end(); ++it) {
                dfsFuzzy(it->second, word,
                         current + it->first,
                         idx, edits + 1, maxEdits, res);
            }
            return;
        }

        for (auto it = node->children.begin();
             it != node->children.end(); ++it) {

            char ch = it->first;
            TrieNode* child = it->second;

            // Match
            if (ch == word[idx]) {
                dfsFuzzy(child, word,
                         current + ch,
                         idx + 1, edits,
                         maxEdits, res);
            }
            // Replace
            else {
                dfsFuzzy(child, word,
                         current + ch,
                         idx + 1, edits + 1,
                         maxEdits, res);
            }

            // Insert
            dfsFuzzy(child, word,
                     current + ch,
                     idx, edits + 1,
                     maxEdits, res);
        }

        // Delete
        dfsFuzzy(node, word,
                 current,
                 idx + 1, edits + 1,
                 maxEdits, res);
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children[c])
                curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->isEnd = true;
    }

    vector<string> prefixSearch(const string& prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            if (!curr->children.count(c))
                return {};
            curr = curr->children[c];
        }

        vector<string> res;
        dfsPrefix(curr, prefix, res);
        return res;
    }

    vector<string> fuzzySearch(const string& word, int maxEdits = 1) {
        vector<string> res;
        dfsFuzzy(root, word, "", 0, 0, maxEdits, res);
        return res;
    }
};

int main() {
    Trie trie;

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

    for (string p : products)
        trie.insert(p);

    string query;
    cout << "Search: ";
    cin >> query;

    vector<string> results;

    if (query.length() <= 2) {
        results = trie.prefixSearch(query);
    } else {
        results = trie.fuzzySearch(query, 1);
    }

    cout << "\nResults:\n";
    if (results.empty()) {
        cout << "No matches found\n";
    } else {
        for (string s : results)
            cout << s << endl;
    }

    return 0;
}
