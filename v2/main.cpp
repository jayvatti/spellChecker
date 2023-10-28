#include <iostream>
#include <fstream>

#include "Dictionary.h"
#include "spellChecker.h"

#include "TrieDictionary.h"
#include "TrieChecker.h"

#include "Timer.h"

template <typename T>
void readDictionary(T & dictionary, const std::string& filename = "words.txt") {
    std::ifstream file(filename);
    if (!file.is_open()) std::cerr<<"Failed to open the file."<<std::endl;
    std::string word;
    while (file >> word) dictionary.insert(word);
    file.close();
}


int main() {
    Dictionary dictionary(26);
    //reading the file
    readDictionary<Dictionary>(dictionary);
    /*
    std::cout<<dictionary[0]->data;
    {
        TimeInterval timer;
        std::cout<<spellChecker("ahell", dictionary);
    }
    std::cout<<std::endl;
    {
        TimeInterval timer;
        std::cout<<parallelSpellChecker("ahell", dictionary);
    }*/
    TrieDictionary trieDictionary(26);
    readDictionary<TrieDictionary>(trieDictionary);
//    trieDictionary.printWordsAtIndex(0);
 //   std::cout<<trieDictionary['h' - 'a']->search("hello")<<std::endl;
//    std::vector<std::string> suggestions;
//    {
//        TimeInterval timer;
//        suggestions = spellCheckSuggestions("hello",trieDictionary);
//    }
//
//    for (const auto& i: suggestions) {
//        std::cout << i << std::endl;
//    }
    std::cout<<"Words Starting with 'he': \n";
    std::vector<std::string> prefixVector = trieDictionary.getWordsStartingWith("he");

    for(const auto& i: prefixVector) {
        std::cout << i << std::endl;
    }
    return 0;
}
