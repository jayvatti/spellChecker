//
// Created by Jay Vatti on 10/27/23.
//
#pragma once

#include <thread>
#include <future>


#include "vector"
#include <algorithm>

#include "Dictionary.h"

#include "LCS.h"
#include "editDistance.h"
#include "ngrams.h"


//this is slow... still need to optimize it
double averageScore(const std::string& word, const std::string& dictWord) {
//using async to compute the LCS score
    auto futureLcsScore = std::async(std::launch::async, longestCommonSubsequenceLength, word, dictWord);

    auto futureEditDistance = std::async(std::launch::async, editDistance, word, dictWord);

    auto futureNgramSimilarity = std::async(std::launch::async, [&word, &dictWord](){
        return ngramSimilarity(word, dictWord);
    });


    //retrieving results from the futures
    auto lcsScore = static_cast<double>(futureLcsScore.get());
    double normalizedLcs = lcsScore / std::max(word.length(), dictWord.length());
    double normalizedEditDistance = 1.0 / (1.0 + futureEditDistance.get());
    double ngramScore = futureNgramSimilarity.get();

    //ngram score is given more weightage
    return (2 * ngramScore + normalizedLcs + normalizedEditDistance) / 4;
}
std::string spellChecker(const std::string& word, const Dictionary& dict) {
    double maxScore = 0;
    std::string bestMatch;

    Node* current = dict.listForWord(word);

    while (current != nullptr) {
        const std::string& dictWord = current->data;
        double score = averageScore(word, dictWord);
        if (score > maxScore) {
            maxScore = score;
            bestMatch = dictWord;
        }
        current = current->next;
    }
    return bestMatch;
}

const int batchSize = 26 / std::thread::hardware_concurrency();

std::string parallelSpellChecker(const std::string& word, const Dictionary& dict) {
    //local search
    auto futureLocalSearch = std::async(std::launch::async, [&word, &dict](){
        return spellChecker(word, dict);
    });

    //global Search
    std::vector<std::future<std::string>> futureGlobalSearches;

    for (int i = 0; i < dict.size; i += batchSize) {
        futureGlobalSearches.push_back(
                std::async(std::launch::async, [i, &word, &dict](){
                    double maxScore = 0;
                    std::string bestMatch;

                    for(int j = i; j < std::min(i + batchSize, dict.size); j++) {
                        Node* current = dict[j];
                        while (current != nullptr) {
                            const std::string& dictWord = current->data;
                            double score = averageScore(word, dictWord);
                            if (score > maxScore) {
                                maxScore = score;
                                bestMatch = dictWord;
                            }
                            current = current->next;
                        }
                    }
                    return bestMatch;
                })
        );
    }

    std::string bestGlobalMatch;
    double maxGlobalScore = 0;

    for (auto& future : futureGlobalSearches) {
        std::string candidate = future.get();
        double score = averageScore(word, candidate);
        if (score > maxGlobalScore) {
            maxGlobalScore = score;
            bestGlobalMatch = candidate;
        }
    }

    //comparing the local best match and the global best match
    double localScore = averageScore(word, futureLocalSearch.get());
    return (localScore > maxGlobalScore) ? futureLocalSearch.get() : bestGlobalMatch;
}
