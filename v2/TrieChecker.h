//
// Created by Jay Vatti on 10/27/23.
//
#pragma once
#include <thread>
#include <future>

std::vector<std::string> deletionStrategy(const std::string& word, TrieDictionary& dictionary) {
    std::vector<std::string> suggestions;
    for (size_t i = 0; i < word.size(); i++) {
        std::string temp = word;
        temp.erase(i, 1);
        Trie* root = dictionary[temp[0] - 'a'];
        if (root && root->search(temp)) {
            suggestions.push_back(temp);
        }
    }
    return suggestions;
}

std::vector<std::string> transpositionStrategy(const std::string& word, TrieDictionary& dictionary) {
    std::vector<std::string> suggestions;
    for (size_t i = 0; i < word.size() - 1; i++) {
        std::string temp = word;
        std::swap(temp[i], temp[i+1]);
        Trie* root = dictionary[temp[0] - 'a'];
        if (root && root->search(temp)) {
            suggestions.push_back(temp);
        }
    }
    return suggestions;
}

std::vector<std::string> replacementStrategy(const std::string& word, TrieDictionary& dictionary) {
    std::vector<std::string> suggestions;
    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    for (size_t i = 0; i < word.size(); i++) {
        for (char c : letters) {
            std::string temp = word;
            temp[i] = c;
            Trie* root = dictionary[temp[0] - 'a'];
            if (root && root->search(temp)) {
                suggestions.push_back(temp);
            }
        }
    }
    return suggestions;
}

std::vector<std::string> insertionStrategy(const std::string& word, TrieDictionary& dictionary) {
    std::vector<std::string> suggestions;
    std::string letters = "abcdefghijklmnopqrstuvwxyz";
    for (size_t i = 0; i <= word.size(); i++) {
        for (char c : letters) {
            std::string temp = word;
            temp.insert(i, 1, c);
            Trie* root = dictionary[temp[0] - 'a'];
            if (root && root->search(temp)) {
                suggestions.push_back(temp);
            }
        }
    }
    return suggestions;
}

std::vector<std::string> spellCheckSuggestions(const std::string& word, TrieDictionary& dictionary) {
    std::vector<std::string> suggestions;

    Trie* root = dictionary[word[0] - 'a'];
    if (root && root->search(word)) {
        suggestions.push_back(word);
    }

    //integrate all strategies
    auto deletionSuggestions = deletionStrategy(word, dictionary);
    suggestions.insert(suggestions.end(), deletionSuggestions.begin(), deletionSuggestions.end());

    auto transpositionSuggestions = transpositionStrategy(word, dictionary);
    suggestions.insert(suggestions.end(), transpositionSuggestions.begin(), transpositionSuggestions.end());

    auto replacementSuggestions = replacementStrategy(word, dictionary);
    suggestions.insert(suggestions.end(), replacementSuggestions.begin(), replacementSuggestions.end());

    auto insertionSuggestions = insertionStrategy(word, dictionary);
    suggestions.insert(suggestions.end(), insertionSuggestions.begin(), insertionSuggestions.end());

    //removing duplicates
    std::sort(suggestions.begin(), suggestions.end());
    suggestions.erase(std::unique(suggestions.begin(), suggestions.end()), suggestions.end());

    return suggestions;
}

#include <future>

std::vector<std::string> spellCheckSuggestionsParallel(const std::string& word, TrieDictionary& dictionary) {
    std::vector<std::string> suggestions;

    Trie* root = dictionary[word[0] - 'a'];
    if (root && root->search(word)) {
        suggestions.push_back(word);
    }

    //strategies in a separate thread using std::async
    auto futureDeletionSuggestions = std::async(std::launch::async, deletionStrategy, word, std::ref(dictionary));
    auto futureTranspositionSuggestions = std::async(std::launch::async, transpositionStrategy, word, std::ref(dictionary));
    auto futureReplacementSuggestions = std::async(std::launch::async, replacementStrategy, word, std::ref(dictionary));
    auto futureInsertionSuggestions = std::async(std::launch::async, insertionStrategy, word, std::ref(dictionary));

    //collecting results from each thread
    auto deletionSuggestions = futureDeletionSuggestions.get();
    auto transpositionSuggestions = futureTranspositionSuggestions.get();
    auto replacementSuggestions = futureReplacementSuggestions.get();
    auto insertionSuggestions = futureInsertionSuggestions.get();

    //merging the results
    suggestions.insert(suggestions.end(), deletionSuggestions.begin(), deletionSuggestions.end());
    suggestions.insert(suggestions.end(), transpositionSuggestions.begin(), transpositionSuggestions.end());
    suggestions.insert(suggestions.end(), replacementSuggestions.begin(), replacementSuggestions.end());
    suggestions.insert(suggestions.end(), insertionSuggestions.begin(), insertionSuggestions.end());

    //removing duplicates
    std::sort(suggestions.begin(), suggestions.end());
    suggestions.erase(std::unique(suggestions.begin(), suggestions.end()), suggestions.end());

    return suggestions;
}

