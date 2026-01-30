#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    bool isEnd;
    int frequency;   // number of times selected / requested
    unordered_map<char, TrieNode*> children;

    TrieNode() {
        isEnd = false;
        frequency = 0;
    }
};

class Trie {
private:
    TrieNode* root;

    // DFS to collect all words with their frequency
    void dfs(TrieNode* node, string current,
             vector<pair<string,int>>& results) {

        if (node->isEnd) {
            results.push_back({current, node->frequency});
        }

        for (auto it = node->children.begin();
             it != node->children.end(); ++it) {
            dfs(it->second, current + it->first, results);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a product into trie
    void insert(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children[c])
                curr->children[c] = new TrieNode();
            curr = curr->children[c];
        }
        curr->isEnd = true;
    }

    // Increase frequency when user clicks/selects a product
    void incrementFrequency(const string& word) {
        TrieNode* curr = root;
        for (char c : word) {
            if (!curr->children.count(c))
                return; // word not found
            curr = curr->children[c];
        }
        if (curr->isEnd)
            curr->frequency++;
    }

    // Prefix search + ranking
    vector<string> recommend(const string& prefix, int topK = 5) {
        TrieNode* curr = root;
        for (char c : prefix) {
            if (!curr->children.count(c))
                return {};
            curr = curr->children[c];
        }

        vector<pair<string,int>> collected;
        dfs(curr, prefix, collected);

        // Sort by frequency (descending)
        sort(collected.begin(), collected.end(),
             [](const auto& a, const auto& b) {
                 if (a.second == b.second)
                     return a.first < b.first; // tie-breaker
                 return a.second > b.second;
             });

        vector<string> result;
        for (int i = 0; i < collected.size() && i < topK; i++)
            result.push_back(collected[i].first);

        return result;
    }
};

int main() {
    Trie trie;

    // Initial product catalog
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

    cout << "=== Trie-based Product Recommendation System ===\n";

    while (true) {
        cout << "\n1. Search\n2. Select Product (simulate click)\n3. Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string prefix;
            cout << "Enter search prefix: ";
            getline(cin, prefix);

            auto recommendations = trie.recommend(prefix);

            if (recommendations.empty()) {
                cout << "No recommendations found\n";
            } else {
                cout << "Recommended Products:\n";
                for (int i = 0; i < recommendations.size(); i++) {
                    cout << i+1 << ". " << recommendations[i] << endl;
                }
            }
        }

        else if (choice == 2) {
            string product;
            cout << "Enter exact product name selected: ";
            getline(cin, product);

            trie.incrementFrequency(product);
            cout << "Frequency updated for \"" << product << "\"\n";
        }

        else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }

        else {
            cout << "Invalid choice\n";
        }
    }

    return 0;
}
