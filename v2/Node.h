#pragma once
#include <string>
#include <utility>

class Node {
public:
    std::string data;
    Node* next;

    explicit Node(std::string word) : data(std::move(word)), next(nullptr) {}
};