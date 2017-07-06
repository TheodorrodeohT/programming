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

void printInorderWithDuplicates(Node* node) {
    if (!node) return;

    printInorderWithDuplicates(node->left);
    std::cout << node->key;
    std::cout << " " << node->repeats << "\n";
    printInorderWithDuplicates(node->right);
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
