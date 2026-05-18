// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::string current_word = "";
    int ch;
    while ((ch = file.get()) != EOF) {
        if (std::isalpha(ch) && isascii(ch)) {
            current_word += std::tolower(ch);
        } else {
            if (!current_word.empty()) {
                tree.add(current_word);
                current_word = "";
            }
        }
    }
    if (!current_word.empty()) {
        tree.add(current_word);
    }
    file.close();
}

bool compareNodes(const BST<std::string>::Node* a, const BST<std::string>::Node* b) {
    if (a->count != b->count) {
        return a->count > b->count;
    }
    return a->key < b->key;
}
void printFreq(BST<std::string>& tree) {
    std::vector<BST<std::string>::Node*> nodes = tree.getAllNodes();
    std::sort(nodes.begin(), nodes.end(), compareNodes);
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cout << "Error creating result/freq.txt!" << std::endl;
        return;
    }

    for (const auto* node : nodes) {
        std::cout << node->key << ": " << node->count << std::endl;
        outFile << node->key << ": " << node->count << "\n";
    }

    outFile.close();
}
