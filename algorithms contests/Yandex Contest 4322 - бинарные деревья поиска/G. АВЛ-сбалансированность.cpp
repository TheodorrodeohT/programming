#include <iostream>
#include <algorithm>

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;
    explicit Node(int value, Node* parent)
        : key(value)
        , left(nullptr)
        , right(nullptr)
        , parent(parent)
    {}
};

Node* insertNode(Node* node, int value, Node* parent = nullptr) {
    if (!node) node = new Node(value, parent);

    if (value < node->key) node->left = insertNode(node->left, value, node);
    if (value > node->key) node->right = insertNode(node->right, value, node);
    return node;
}

int height(Node* node) {
    if (!node) return 0;
    return 1 + std::max(height(node->left), height(node->right));
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

    if (isBalanced(tree))
        std::cout << "YES\n";
    else
        std::cout << "NO\n";

    deleteTree(tree);
    system("pause");
    return 0;
}
