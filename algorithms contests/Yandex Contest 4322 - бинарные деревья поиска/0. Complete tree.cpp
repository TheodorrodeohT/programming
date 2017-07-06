#include <iostream>
#include <algorithm>

struct Node {
    int key;
    int repeats;
    Node* left;
    Node* right;
    Node* parent;
    explicit Node(int value, Node* parent)
        : key(value)
        , repeats(0)
        , left(nullptr)
        , right(nullptr)
        , parent(parent)
    {}
};

Node* insertNode(Node* node, int value, Node* parent = nullptr) {
    if (!node) node = new Node(value, parent);

    if (value < node->key) node->left = insertNode(node->left, value, node);
    if (value > node->key) node->right = insertNode(node->right, value, node);
    if (value == node->key) ++node->repeats;
    return node;
}

int height(Node* node) {
    if (!node) return 0;
    return 1 + std::max(height(node->left), height(node->right));
}

Node* findMax(Node* node) {
    return node->right ? findMax(node->right) : node;
}

Node* secondMax(Node* node) {
    node = findMax(node);
    return node->left ? findMax(node->left) : node->parent;
}

void printInorder(Node* node) {
    if (!node) return;

    printInorder(node->left);
    std::cout << node->key << "\n";
    printInorder(node->right);
}

void printLeavesInorder(Node* node) {
    if (!node) return;

    if (!node->left && !node->right)
        std::cout << node->key << "\n";
    printLeavesInorder(node->left);
    printLeavesInorder(node->right);
}

void printCrossesInorder(Node* node) {
    if (!node) return;

    printCrossesInorder(node->left);
    if (node->left && node->right)
        std::cout << node->key << "\n";
    printCrossesInorder(node->right);
}

void printBranchesInorder(Node* node) {
    if (!node) return;

    printBranchesInorder(node->left);
    if (node->left && !node->right || !node->left && node->right)
        std::cout << node->key << "\n";
    printBranchesInorder(node->right);
}

void printInorderWithDuplicates(Node* node) {
    if (!node) return;

    printInorderWithDuplicates(node->left);
    std::cout << node->key;
    std::cout << " " << node->repeats << "\n";
    printInorderWithDuplicates(node->right);
}

bool isBalanced(Node* node) {
    if (!node) return 1;

    int lHeight = height(node->left);
    int rHeight = height(node->right);
    if (abs(lHeight - rHeight) < 2 && isBalanced(node->left) && isBalanced(node->right))
        return 1;
    return 0;
}

void deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int main() {
    Node* tree = nullptr;

    int num = 0;
    while (std::cin >> num && num != 0)
        tree = insertNode(tree, num);

    printInorderWithDuplicates(tree);

    deleteTree(tree);
    return 0;
}
