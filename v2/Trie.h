#pragma once
#include <string>
#include <vector>

const int ALPHABET_SIZE = 26;  //lowercase letters

class Trie {
public:
    Trie* children[ALPHABET_SIZE];
    bool isEndOfWord;

    Trie() : isEndOfWord(false) {
        for (int i = 0; i < ALPHABET_SIZE; i++)
            children[i] = nullptr;
    }

    void insert(const std::string &word) {
        Trie* current = this;
        for (char ch : word) {
            int index = ch - 'a';  //convert character to index
            if (!current->children[index]) {
                current->children[index] = new Trie();
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }

    //helper function for print
    void printWordsFromTrie(const std::string &prefix) {
        if (isEndOfWord) {
            std::cout << prefix << std::endl;
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (children[i]) {
                children[i]->printWordsFromTrie(prefix + static_cast<char>(i + 'a'));
            }
        }
    }

    bool search(const std::string& word) {
        Trie* node = this;
        for (char c : word) {
            int index = c - 'a';
            if (!node->children[index]) {
                return false; //word is not present in the Trie
            }
            node = node->children[index];
        }
        return node && node->isEndOfWord;
    }

    void collectWordsStartingWith(Trie* node, const std::string& currentWord, std::vector<std::string>& result) {
        if (!node) return;
        if (node->isEndOfWord) {
            result.push_back(currentWord);
        }

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            if (node->children[i]) {
                collectWordsStartingWith(node->children[i], currentWord + static_cast<char>(i + 'a'), result);
            }
        }
    }

    std::vector<std::string> wordsWithPrefix(const std::string& prefix) {
        Trie* node = this;
        std::vector<std::string> result;

        //navigating to the end of the prefix in the trie
        for (char c : prefix) {
            int index = c - 'a';
            if (!node->children[index]) {
                return result; //prefix is not in the trie
            }
            node = node->children[index];
        }

        collectWordsStartingWith(node, prefix, result);

        return result;
    }
};
