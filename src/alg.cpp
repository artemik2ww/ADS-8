// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string currentWord = "";

    while (!file.eof()) {
        int ch = file.get();
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = ch + ('a' - 'A');
            }
            currentWord += static_cast<char>(ch);
        } else {
            if (!currentWord.empty()) {
                tree.insert(currentWord);
                currentWord = "";
            }
        }
    }

    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    BST<std::string>::Pair* arr = nullptr;
    int size = tree.getSortedArray(arr);

    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cout << "Error creating result file!" << std::endl;
        if (arr != nullptr) delete[] arr;
        return;
    }

    for (int i = 0; i < size; i++) {
        std::cout << arr[i].word << ": " << arr[i].count << std::endl;
        outFile << arr[i].word << ": " << arr[i].count << "\n";
    }

    outFile.close();
    delete[] arr;
}
