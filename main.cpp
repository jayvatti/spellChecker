#include "HashDict.h"
int main()
{
    HashDict h;
    std::string fileName = "Dictionary.txt";//fileName
    h.readFile(fileName);//reading the file

    std::string query;
    std::cout<<"Enter a word:";
    std::cin>>query;
    h.checkWord(query);//checking  for the word
}
