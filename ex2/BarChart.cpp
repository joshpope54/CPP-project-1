
#include "BarChart.h"
#include <iostream>
#include <iomanip>

using namespace std;


BarChart::BarChart(const char *fname) {
    wordfile.open(fname);//open file
    //Inform the user that the file did not open and so we are generating one
    if (!wordfile) {
        cout << "Failed to open " << fname << ". Generating..." << endl;
    }
}

void BarChart::addBar(string word) {
    //Add one to the count if a word is found, else create a new item in the map
    if (barMap.count(word) > 0 ){
        barMap[word]+=1;
    }else{
        barMap[word]=1;
    }
}

void BarChart::printBar(string word) {
    string bar;
    int barSize = returnBarTotal(word);
    int largestWord=0;
    string currentWord;

    //Look for the largest word to create proper formatting
    for (map<string, int>::iterator it = barMap.begin(); it != barMap.end(); ++it) {
        currentWord = it->first;
        if (largestWord < currentWord.length()) {
            largestWord = currentWord.length();
        }
    }

    //add a * to the bar, depending on the scale.
    for (int i = 0; i < barSize; i += scale) {
        bar += "*";
    }

    //If bar the bar size is equal to 0 print the bar with no bar
    if (barSize == 0) {
        cout << left << setw(largestWord + 3) << word << "(" << barSize << ")"<< endl;
        wordfile << left << setw(largestWord + 3) << word << " (" << barSize << ")\n";


    } else {//Else print the bar
        cout << left << setw(largestWord + 3) << word << bar << " (" << barSize << ")"<< endl;
        wordfile << left << setw(largestWord + 3) << word << bar << " (" << barSize << ")\n";

    }

}

//Print the first line for the user
void BarChart::setFirstLine() {
    cout << "The Scale is one (*) to " << scale<< " item(s)." <<endl;
    wordfile << "The Scale is one (*) to " << scale<< " item(s)." << endl;
}

void BarChart::setScale(){
    //Largest size of the bar
    int maxSize = 50;
    int largestBar;
    string currentWord;
    scale = 1;

    //Looking for the largest bar
    for (map<string, int>::iterator it = barMap.begin(); it != barMap.end(); ++it) {
        currentWord = it->first;
        for (int i = 0; i < barMap.size(); i++) {
            int currentBar = returnBarTotal(currentWord);
            if (largestBar < currentBar) {
                largestBar = currentBar;
            }
        }
    }

    //generating the correct scale based off of the largest bar
    while (largestBar / scale > maxSize) {
        scale += 1;
    }
}

int BarChart::returnScale() {
    //Simply return the scale.
    return scale;
}

int BarChart::returnBarTotal(string word){
    //return the size of a bar.
    map<string, int>::iterator it;
    int value;
    if((it = barMap.find(word)) != barMap.end())
        value= it->second;
    return value;
}