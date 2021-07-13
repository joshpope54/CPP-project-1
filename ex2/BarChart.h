
#ifndef BARCHART_H
#define BARCHART_H

using namespace std;

#include <string>
#include <fstream>
#include <map>

/**
 * Bar Chart class. Provides methods to generate a bar chart of words.
 *
 * */

class BarChart {

    public:
        /**
         * Constructor. Opens a file with a given name,
         * If the file does not exist it will be generated as this will be the output file.
         * @param filename - a C string naming the file to be opened.
         * */
        BarChart(const char *filename);

        /**
         * Increments the BarMap, If a word does not exist in the map it will be added, Otherwise
         * it will be incremented
         * */
        void addBar(string);

        /**
         * Returns a Integer. This integer is the value of a given key. Uses a Iterator to
         * search the map properly
         * @param word - The word of which its count will be returned.
         * @return - int - The Value of the given key.
         * */
        int returnBarTotal(string word);


        /**
         * Will print and add to the file the bar for a given key,
         * This method performs the formatting of the bar as well.
         * */
        void printBar(string);

        /**
         * This method will find the scale of the bars.
         * */
        void setScale();

        /**
         * This method sets the first output line of the bars - Informs the user of the scale.
         * */
        void setFirstLine();

        /**
         * This method returns the scale so it can be used
         * */
        int returnScale();

private:
        int scale;
        ofstream wordfile;
        string nextword;
        map<string, int> barMap;
};


#endif //BARCHART_H
