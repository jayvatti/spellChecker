#pragma once
#include <string>
//linkedList for Dictionary //FOR CHAINING HASH
class Node{
public:
    std::string word;
    Node* next;
    Node(): next(nullptr) {};//by default -> Node *next = nullptr
};
