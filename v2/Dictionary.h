//
// Created by Jay Vatti on 10/27/23.
//

#pragma once
#include "Node.h"
#include <vector>

class Dictionary {

private:
    std::vector<Node *> table;

    //hashing function
    static int hashFunction(const std::string &word) {
        return int(word[0]) % 97; //considering only the first character
    }
public:
    Dictionary(const Dictionary&) = delete;  //disabling copy constructor
    Dictionary& operator=(const Dictionary&) = delete;  //disabling assignment operator

    int size;

    explicit Dictionary(int s) : size(s) {
        table.resize(size, nullptr);
    }

    ~Dictionary(){
        for(Node *node : table){
            while(node != nullptr){
                Node *temp = node;
                node = node->next;
                delete temp;
            }
        }
    }
    //always inserting at the head of the linked list
    void insert(const std::string& word) {
        int index = hashFunction(word);

        Node* newNode = new Node(word);


        newNode->next = table[index];
        table[index] = newNode;
    }

    void printNodesAtIndex(int index) const{
        Node *node = table[index];
        while(node != nullptr){
            std::cout<<node->data<<" ";
            node = node->next;
        }
        std::cout << std::endl;
    }

    //returns the head of the linked list for the given word
    Node* listForWord(const std::string &word) const{
        return table[hashFunction(word)];
    }

    //overloading subscript operator
    Node* operator[](int index) const{
        return table[index];
    }

};


