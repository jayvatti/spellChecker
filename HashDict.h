#pragma once
#include "Node.h"
#include <array>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
//header file for HashDict

class HashDict{
public:
    HashDict();
    std::array<Node*, 26> dictionary;//Dictionary
    int hashFunc(std::string &query);//hashFunction
    void chainHashDict(std::string &query);//chaining each word to the Dictionary
    void readFile(std::string &textFile);//reading the file
    std::vector<std::string> bigramSplit(std::string& query);//splitting as Bigrams
    void checkWord(std::string& query);//checking for the word
    bool wordExist(std::string& query);//if word exists ? return True : return False
    bool checkIndex(int error_size, int index);//checks ithe index is valid

    std::string spellCheck(std::string& query);//spell checking algorithm
    void printHashDict();//FOR DEBUGGING // PRINTS THE HASH TABLE
    ~HashDict();//deletes HEAP MEMORY
};
