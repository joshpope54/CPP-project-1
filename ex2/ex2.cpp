#include <iostream>
#include "ReadWords.cpp"
#include "BarChart.h"
#include <map>
#include <vector>

int main() {
    //3 C strings for the file input
    char inputFile[50];
    char outputFile[50];
    char searchFile[50];

    //Ask the user for each file name, Inputting them into the 3 c strings
    cout << "Enter the name of the input file that is to be search: ";
    cin >> inputFile;
    cout << "Enter the name of the file that holds the search words: ";
    cin >> searchFile;
    cout << "Enter the name of the output files: ";
    cin >> outputFile;

    //2 Objects of Readwords, one of the main file and one of the file that contains the search words
    ReadWords word = ReadWords(inputFile);
    ReadWords search = ReadWords(searchFile);

    int wordcount = 0;
    //A bar chart object
    BarChart b = BarChart(outputFile);
    //a Vector to contain the search words.
    vector<string> v1;
    //looping over the search object and adding the words to the vector
    while(search.isNextWord()) {
        string currentSearchWord = search.getNextWord();
        v1.push_back(currentSearchWord);

    }
    //looping over the main file
    while(word.isNextWord()){
        //setting the next word to a string, all change to the word(Punctuation removal and )
        string currentWord = word.getNextWord();

        //checking if the search word is equal to a word in the main file. if it is add it to a corresponding bar
        for(int i=0; i<v1.size();i++){
            if (v1.at(i)==currentWord) {
                b.addBar(currentWord);
            }
        }
    }
    //set and return the scale
    b.setScale();
    b.returnScale();
    //set the first line of the file/output
    b.setFirstLine();
    //loop over the search word vector and print all the bars
    for(int i=0; i<v1.size();i++){
        string wordBar = v1.at(i);
        b.printBar(wordBar);
    }
    //close the files
    word.close();
    search.close();
}