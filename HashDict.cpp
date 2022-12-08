//
// Created by Jay Vatti on 11/8/22.
//

#include "HashDict.h"
#include "TimeInterval.h"

HashDict::HashDict() {for(int i = 0; i < 26;i++){dictionary[i] = nullptr;}}//initializing a nullptr dictionary

int HashDict::hashFunc(std::string &query){
    std::transform(query.begin(), query.end(), query.begin(), ::tolower);//transforming to lower case
    std::string strAlphabet = query.substr(0,1);//first letter
    return strAlphabet.at(0)%97;//hashing
}
void HashDict::chainHashDict(std::string &query){
    int hash_index = hashFunc(query);//calling the hash Function
    Node* new_word = new Node();
    new_word->word = query;

    Node *first = dictionary[hash_index];
    new_word->next = first;
    dictionary[hash_index] = new_word;//inserting at that index
}

void HashDict::printHashDict() {//for TESTING //DEBUG
    for(Node* i: dictionary){
        while(i!= nullptr){
            std::cout<<i->word<<"->";
            i = i->next;
        }
        std::cout<<std::endl;
        std::cout<<std::endl;
    }
}
bool HashDict::wordExist(std::string &query) {//checking if that word exists
    int hash_index = hashFunc(query);//calling the hash Function
    Node* index = dictionary[hash_index];
    while(index!= nullptr){
        if(index->word == query){return true;}
        index = index->next;
    }
    return false;
}
void HashDict::checkWord(std::string& query){//checks for the Word
    int hash_index = hashFunc(query);
    Node* index = dictionary[hash_index];
    bool exists = wordExist(query);
    TimeInterval time;//time
    if(!exists){
        query = spellCheck(query);
        if (query == "INVALID_WORD"){
            std::cout<<"False"<<std::endl;
            return;
        }
        std::cout<<"Do you mean '"<<query<<"'? (yes/no):"<<std::endl;
        std::string userInput;
        std::cin>>userInput;
        time.start();//time.start
        std::transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);
        if(userInput=="yes"){
            exists=true;
        }
    }
    std::cout<<"The program responds: "<<std::boolalpha<<exists<<std::endl;
    if(exists){
        while(index!= nullptr){
            if(index->word.substr(0,2) == query.substr(0,2)){
                if(query!=index->word){std::cout<<index->word<<std::endl;}
            }
            index = index->next;
        }
    }
    time.stop();//time.stop
    std::cout<<std::endl;
    std::cout<<time.GetInterval()<<" microseconds"<<std::endl;//printing the time

}
std::vector<std::string> HashDict::bigramSplit(std::string& query){//splitting as bigrams
    std::vector<std::string>bigram_vector;
    for(int i = 0; i < query.length()-1; i++){
        bigram_vector.push_back(query.substr(i,2));
    }
    return bigram_vector;
}
bool HashDict::checkIndex(int error_size, int index){//checks if the index is valid
    if(0<=index && index<error_size){
        return true;
    }
    return false;

}
std::string HashDict::spellCheck(std::string& query){
    //spell checking algorithm //USES BIGRAM WORD SPLIT
    int hash_index = hashFunc(query);
    Node* index = dictionary[hash_index];
    std::string correctWord;//storing the highest scored word
    int q_score = INT16_MIN;//setting q_score to the lowest 16bit INT //highest scored correctWord
    while(index!=nullptr){
        std::vector<std::string> errorList = bigramSplit(query);//bigramSplit
        std::string currentWord = index->word;//getting the current word
        std::vector<std::string> wordList = bigramSplit(currentWord);//bigramSplit
        int tempScore = 0;
        for(int i = 0; i < wordList.size(); i++){
            bool i_m1 =  checkIndex(errorList.size(),i-1);//checks for index i - 1
            bool i_p1 =  checkIndex(errorList.size(),i+1);//checks for index i + 1
            bool i_m2 =  checkIndex(errorList.size(),i-2);//checks for index i - 2
            bool i_p2 =  checkIndex(errorList.size(),i+2);//checks for index i + 2
            if(checkIndex(errorList.size(),i)){
                wordList[i] == errorList[i]? tempScore+=9: tempScore+=0;
            }
            else if(i_m1 || i_p1){
                if(i_m1 && i_p1){
                    if((wordList[i] == errorList[i-1]) ^ (wordList[i] == errorList[i+1])){tempScore+=6;}
                }
                else{tempScore+=6;}
            }
            else if(i_m2 || i_p2){
                if(i_m2 && i_p2){
                    if((wordList[i] == errorList[i-2]) ^ (wordList[i] == errorList[i+2])){tempScore+=3;}
                }
                else{tempScore+=3;}
            }
        }
        if(q_score<tempScore){
            int vec_diff = errorList.size() - wordList.size();//calculating the difference in lengths
            tempScore = tempScore - abs(vec_diff);//ignoring negative values
            q_score = tempScore;//updating highest score
            correctWord = index->word;//updating the highest score word
        }
        index = index->next;
    }
    if(query.length()>correctWord.length()*2 && query.length()>2){//CASE FOR THE WORD TO BE VALID
        correctWord = "INVALID_WORD";//returns invalid word if the user enters gibberish
    }
    return correctWord;
}
/*
    * TESTING INDEXING
    * computer
    * co om mp pu ut te er     - WORD
    * cm mp pu ut te er        - QUERY1
    * cm mp pu ut te ee er re  - QUERY1
    * cmputer
    * cmputeere
    *
    */

void HashDict::readFile(std::string &textFile){//reads the file
    std::ifstream inFile(textFile);
    std::string str;
    while (std::getline(inFile, str)){
        chainHashDict(str);
    }
    inFile.close();
}
HashDict::~HashDict() {
    //frees the memory
    for(Node* i: dictionary){
        Node* temp;//temporary Node*
        while(i!= nullptr){
            temp = i;
            i = i->next;
            delete temp;//deleting the Node* on the heap
        }
    }
    std::cout<<"Freed Memory"<<std::endl;//DEBUG ->TO CHECK IF THE MEMORY IS FREE
}



