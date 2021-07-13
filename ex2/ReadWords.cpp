using namespace std;

#include "ReadWords.h"
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <string>

string removePunct(string word) {
    /*
     *  This method will remove the punction from a word. It works by looking through the word for the first letter
     *  then removing anything that came before it, It also looks for the last letter and then removes anything after
     *  it. That way any punctuation within the word will not be deleted.
     *
     *  returns a string.
     *
     * */
    int initialWordLength = word.length();
    int firstLetterPosition = 0;

    for (int i = 0; i<initialWordLength; i++){
        if (isalnum(word.at(i))){
            firstLetterPosition=i;
            break;
        }
    }

    word = word.substr(firstLetterPosition,initialWordLength);
    int newWordLength = word.length();
    int lastLetterPosition = 0;

    for (int i = newWordLength; i>0; --i){
        if (isalnum(word.at(i-1))){
            lastLetterPosition=i-1;
            break;
        }
    }
    word = word.substr(0,lastLetterPosition+1);
    return word;
}

ReadWords::ReadWords(const char *fname) {
    /*
     * This is the constructor, It takes a file name that is to be opened.
     * If the file does not exist program will terminate
     *
     * */

    wordfile.open(fname);//open file
    if (!wordfile) {
        cout << "Failed to open " << fname << endl;
        exit(1);
    }
    wordfile >> nextword;
    eoffound = false;
}

string ReadWords::getNextWord() {
    /*
     * This method retunrs a string that is the next word in the file. The returned word is converted to lower case.
     * If the word contains no letters then a empty string is returned.
     *
     * */

    // uses a one-word lookahead to avoid any problems relating to when if end-of-file
    // is detected due to absence/presence of newline at end of file

    string word = nextword;
    wordfile >> nextword;

    if (wordfile.eof())
        eoffound = true;

    //use one of the previously defined methods to remove punctuation from a word
    word = removePunct(word);

    bool isWord = false;
    int wordLength = word.length();

    for (int i=0; i<wordLength; i++){
        if (isalpha(word.at(i))){
            isWord= true;
        }
    }

    if (!isWord){
        word = "";
    }

    int i =0;
    char chara;
    while (word[i]) {
        chara = word[i];
        if (isupper(chara)){
            word.replace(i,1,1,tolower(chara));
        }
        i++;
    }

    return word;
}

bool ReadWords::isNextWord() {
    //Check if there is another word in the file.
    return !eoffound;
}

void ReadWords::close() {
    //Close the file
    wordfile.close();
}
