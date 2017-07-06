#include <iostream>
#include <algorithm>

struct Node {
    int key;
    Node* left;
    Node* right;
    explicit Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

Node* insertNode(Node* node, int value) {
    if (!node) node = new Node(value);

    if (value < node->key) node->left = insertNode(node->left, value);
    if (value > node->key) node->right = insertNode(node->right, value);
    return node;
}

int height(Node* node) {
    if (!node) return 0;
    return 1 + std::max(height(node->left), height(node->right));
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

    std::cout << height(tree) << "\n";

    deleteTree(tree);
    return 0;
}
