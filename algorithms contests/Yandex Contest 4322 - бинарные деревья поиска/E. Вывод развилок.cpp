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

void printCrossesInorder(Node* node) {
    if (!node) return;

    printCrossesInorder(node->left);
    if (node->left && node->right)
        std::cout << node->key << "\n";
    printCrossesInorder(node->right);
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

    printCrossesInorder(tree);

    deleteTree(tree);
    system("pause");
    return 0;
}
