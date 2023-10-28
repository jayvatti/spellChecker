//
// Created by Jay Vatti on 10/27/23.
//
#pragma once
#include <set>

// function to compute the Jaccard similarity between two sets
double jaccardSimilarity(const std::set<std::string>& set1, const std::set<std::string>& set2) {
    int intersectionSize = 0;
    for (const auto& elem : set1)
        if (set2.find(elem) != set2.end())
            intersectionSize++;

    int unionSize = set1.size() + set2.size() - intersectionSize;

    return static_cast<double>(intersectionSize) / unionSize;
}

// function to compute the n-gram similarity between two words
double ngramSimilarity(const std::string& word1, const std::string& word2, int n = 2) {
    std::set<std::string> ngramsWord1;
    std::set<std::string> ngramsWord2;

    if(word1.length() >= n) {
        for (int i = 0; i <= word1.length() - n; i++)
            ngramsWord1.insert(word1.substr(i, n));
    }

    if(word2.length() >= n) {
        for (int i = 0; i <= word2.length() - n; i++)
            ngramsWord2.insert(word2.substr(i, n));
    }

    return jaccardSimilarity(ngramsWord1, ngramsWord2);
}
