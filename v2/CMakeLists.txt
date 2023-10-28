cmake_minimum_required(VERSION 3.26)
project(Hashing)

set(CMAKE_CXX_STANDARD 17)

add_executable(Hashing main.cpp
        Node.h
        Dictionary.h
        LCS.h
        editDistance.h
        ngrams.h
        spellChecker.h
        Timer.h
        Trie.h
        TrieDictionary.h
        TrieChecker.h)
