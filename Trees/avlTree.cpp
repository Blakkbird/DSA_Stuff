#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val, ht;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), ht(1), left(nullptr), right(nullptr) {} // height 1 of leaf initially !!
};

int height(TreeNode *node) {
    return node ? node->ht : 0;
}

int balanceFactor(TreeNode *node) {
    return height(node->left) - height(node->right);
}

void updateHeight(TreeNode *node) {
    node->ht = 1 + max(height(node->left), height(node->right));
}

TreeNode* rightRotate(TreeNode *y) {
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y); // y is now below x, so update y first
    updateHeight(x);
    return x;
}

TreeNode* leftRotate(TreeNode *x) {
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

// shared by insert and delete: fix height, then rotate if |bf| > 1
TreeNode* rebalance(TreeNode *root) {
    updateHeight(root);
    int bf = balanceFactor(root);

    if (bf > 1) {                                          // left heavy
        if (balanceFactor(root->left) < 0)                 // LR -> turn into LL
            root->left = leftRotate(root->left);
        return rightRotate(root);                          // LL
    }
    if (bf < -1) {                                         // right heavy
        if (balanceFactor(root->right) > 0)                // RL -> turn into RR
            root->right = rightRotate(root->right);
        return leftRotate(root);                           // RR
    }
    return root;
}

TreeNode* successor(TreeNode *node) {
    node = node->right;
    while (node->left)
        node = node->left;
    return node;
}

TreeNode* insertNode(TreeNode *root, int x) {
    if (!root)
        return new TreeNode(x);

    if (x < root->val)
        root->left = insertNode(root->left, x);
    else if (x > root->val)
        root->right = insertNode(root->right, x);
    else
        return root; // duplicates ignored

    return rebalance(root);
}

TreeNode* deleteNode(TreeNode *root, int x) {
    if (!root) return root;

    if (x < root->val)
        root->left = deleteNode(root->left, x);
    else if (x > root->val)
        root->right = deleteNode(root->right, x);
    else {
        if (!root->left || !root->right) {
            TreeNode *replacement = root->left ? root->left : root->right;
            delete root;
            return replacement;
        }
        TreeNode *succ = successor(root);
        root->val = succ->val;
        root->right = deleteNode(root->right, succ->val);
    }

    return rebalance(root);
}

void freeTree(TreeNode *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// debug print: full tree incl. nulls ("X"), O(2^h) so small trees only
void dfs(TreeNode* root, int depth, int maxDepth, vector<vector<string>>& res) { // dfs flex, w/ null for full tree structure
    if (depth == maxDepth) return;
    if (depth == (int)res.size())
        res.push_back({});

    if (!root) {
        res[depth].push_back("X"); // Optional addition
        dfs(nullptr, depth + 1, maxDepth, res);
        dfs(nullptr, depth + 1, maxDepth, res);
        return;
    }

    res[depth].push_back(to_string(root->val));
    dfs(root->left, depth + 1, maxDepth, res);
    dfs(root->right, depth + 1, maxDepth, res); // easy to flip, zig zag, etc !!!
}
void printTree(TreeNode* root) {
    vector<vector<string>> res;
    int h = height(root);

    dfs(root, 0, h, res);

    for (int i = 0; i < (int)res.size(); i++) {
        cout << "level " << i + 1 << ": ";
        for (auto& s : res[i])
            cout << s << " ";
        cout << "\n";
    }
}

int main() {
    TreeNode *root = nullptr;
    for (int x : {8, 9, 10, 2, 1, 5, 3, 6, 4, 7, 11, 12})
        root = insertNode(root, x);

    printTree(root);
    freeTree(root);
}
