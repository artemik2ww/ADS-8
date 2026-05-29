// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;

        Node(T val) {
            value = val;
            count = 1;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    Node* insertNode(Node* node, T val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val == node->value) {
            node->count++;
        } else if (val < node->value) {
            node->left = insertNode(node->left, val);
        } else {
            node->right = insertNode(node->right, val);
        }
        return node;
    }

    int getDepth(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return std::max(leftDepth, rightDepth) + 1;
    }

    Node* searchNode(Node* node, T val) {
        if (node == nullptr || node->value == val) {
            return node;
        }
        if (val < node->value) {
            return searchNode(node->left, val);
        }
        return searchNode(node->right, val);
    }

    struct WordFreq {
        T word;
        int count;
    };

    void collectData(Node* node, WordFreq* arr, int& index) {
        if (node == nullptr) return;
        collectData(node->left, arr, index);
        arr[index].word = node->value;
        arr[index].count = node->count;
        index++;
        collectData(node->right, arr, index);
    }

    int countUniqueNodes(Node* node) {
        if (node == nullptr) return 0;
        return countUniqueNodes(node->left) + countUniqueNodes(node->right) + 1;
    }

 public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        clear(root);
    }

    void insert(T val) {
        root = insertNode(root, val);
    }

    int depth() {
        return getDepth(root);
    }

    bool search(T val) {
        return searchNode(root, val) != nullptr;
    }

    struct Pair {
        T word;
        int count;
    };

    int getSortedArray(Pair*& outputArr) {
        int totalNodes = countUniqueNodes(root);
        if (totalNodes == 0) {
            outputArr = nullptr;
            return 0;
        }

        WordFreq* tempArr = new WordFreq[totalNodes];
        int index = 0;
        collectData(root, tempArr, index);

        for (int i = 0; i < totalNodes - 1; i++) {
            for (int j = 0; j < totalNodes - i - 1; j++) {
                if (tempArr[j].count < tempArr[j + 1].count) {
                    WordFreq temp = tempArr[j];
                    tempArr[j] = tempArr[j + 1];
                    tempArr[j + 1] = temp;
                }
            }
        }
        outputArr = new Pair[totalNodes];
        for (int i = 0; i < totalNodes; i++) {
            outputArr[i].word = tempArr[i].word;
            outputArr[i].count = tempArr[i].count;
        }

        delete[] tempArr;
        return totalNodes;
    }
};

#endif
