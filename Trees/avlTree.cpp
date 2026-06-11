#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val, ht;
    TreeNode *left, *right;
    TreeNode(int x) : val(x), ht(1), left(NULL), right(NULL) {} // height 1 of leaf initially !!
};

int height(TreeNode *node) {
    return node ? node->ht : 0;
}

int balanceFactor(TreeNode *node) {
    return height(node->left) - height(node->right);
}

TreeNode* rightRotate(TreeNode *y) {
    TreeNode *x = y->left;
    TreeNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->ht = 1 + max(height(y->left), height(y->right));
    x->ht = 1 + max(height(x->left), height(x->right));
    return x;
}

TreeNode* leftRotate(TreeNode *x) {
    TreeNode *y = x->right;
    TreeNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->ht = 1 + max(height(x->left), height(x->right));
    y->ht = 1 + max(height(y->left), height(y->right));
    return y;
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
        return root;

    root->ht = 1 + max(height(root->left), height(root->right));

    int bf = balanceFactor(root);

    if (bf > 1 && x < root->left->val)
        return rightRotate(root);
    if (bf < -1 && x > root->right->val)
        return leftRotate(root);
    if (bf > 1 && x > root->left->val) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && x < root->right->val) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
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
        } else {
            TreeNode *succ = successor(root);
            root->val = succ->val;
            root->right = deleteNode(root->right, succ->val);
        }
    }

    root->ht = 1 + max(height(root->left), height(root->right));
    int bf = balanceFactor(root);

    if (bf > 1 && balanceFactor(root->left) >= 0)
        return rightRotate(root);
    if (bf > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (bf < -1 && balanceFactor(root->right) <= 0)
        return leftRotate(root);
    if (bf < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int heightMax(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(height(root->left), height(root->right));
}
void dfs(TreeNode* root, int depth, int maxDepth, vector<vector<string>>& res) { // dfs flex, w/ null for full tree structure
    if (depth == maxDepth) return;
    if (depth == res.size())
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

    for (int i = 0; i < res.size(); i++) {
        cout << "level " << i + 1 << ": ";
        for (auto& s : res[i])
            cout << s << " ";
        cout << "\n";
    }
}

int main() {
    TreeNode *root = NULL;
    root = insertNode(root, 8);
    root = insertNode(root, 9);
    root = insertNode(root, 10);
    root = insertNode(root, 2);
    root = insertNode(root, 1);
    root = insertNode(root, 5);
    root = insertNode(root, 3);
    root = insertNode(root, 6);
    root = insertNode(root, 4);
    root = insertNode(root, 7);
    root = insertNode(root, 11);
    root = insertNode(root, 12);
    
    printTree(root);
}
