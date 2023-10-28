//
// Created by Jay Vatti on 10/27/23.
//
#pragma once
#include "Trie.h"
#include <vector>
#include <iostream>

class TrieDictionary {

private:
    std::vector<Trie*> table;



public:
    explicit TrieDictionary(int s) {
        table.resize(s, nullptr);
    }

    ~TrieDictionary() {
        for (Trie* trie : table) {
            delete trie;
        }
    }

    void insert(const std::string& word) {
        int index = hashFunction(word);

        if (!table[index]) {
            table[index] = new Trie();
        }
        table[index]->insert(word);
    }

    void printWordsAtIndex(int index) {
        if (index >= 0 && index < table.size() && table[index]) {
            table[index]->printWordsFromTrie("");
        }
    }
    static int hashFunction(const std::string &word) {
        return int(word[0]) % 97;  //considering only the first character
    }

    Trie* operator[](int index) {
        return table[index];
    }

    std::vector<std::string> getWordsStartingWith(const std::string& prefix) {
        std::vector<std::string> result;
        Trie* node = table[prefix[0] - 'a'];
        return node->wordsWithPrefix(prefix);
    }

};
