#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 public:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        explicit Node(T value) : key(value), count(1), left(nullptr), right(nullptr) {}
    };

 private:
    Node* root;

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* addNode(Node* node, T value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value < node->key) {
            node->left = addNode(node->left, value);
        } else if (value > node->key) {
            node->right = addNode(node->right, value);
        } else {
            node->count++;
        }
        return node;
    }

    int getDepth(Node* node) const {
        if (node == nullptr) {
            return -1;
        }
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return 1 + std::max(leftDepth, rightDepth);
    }

    Node* searchNode(Node* node, T value) const {
        if (node == nullptr || node->key == value) {
            return node;
        }
        if (value < node->key) {
            return searchNode(node->left, value);
        }
        return searchNode(node->right, value);
    }

    void collectNodes(Node* node, std::vector<Node*>& nodes) const {
        if (node == nullptr) return;
        collectNodes(node->left, nodes);
        nodes.push_back(node);
        collectNodes(node->right, nodes);
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void add(T value) {
        root = addNode(root, value);
    }

    int depth() const {
        return getDepth(root);
    }

    int search(T value) const {
        Node* result = searchNode(root, value);
        if (result != nullptr) {
            return result->count;
        }
        return 0;
    }

    Node* getRoot() const {
        return root;
    }

    std::vector<Node*> getAllNodes() const {
        std::vector<Node*> nodes;
        collectNodes(root, nodes);
        return nodes;
    }
};

#endif  // INCLUDE_BST_H_
