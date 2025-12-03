/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "fstream"
#include "simpio.h"
#include <vector.h>
#include <map.h>
#include "random.h"
using namespace std;
string makeWholeText(ifstream& file);
int getIntegerInARange(int start, int end);
Map<string, Vector<char>>  constructModel( string &wholeText, int k);
string  generate(Map<string, Vector<char>>& modelOfTheText, int n, string mostRepeatedKSeed);


int main() {
    // [TODO: fill with your code]
    string nameOfFile;
    ifstream file;
    // this while loop continues until we dont type in the right file name.
    while (true) {
        nameOfFile = getLine("enter filename:  ");
        file.open(nameOfFile);
        if (file) {
            break;

        }
        cout << "cant open the specified file " << endl;
        file.clear();
    }
    // makes the whole novel into one single string.
    string wholeText = makeWholeText(file);
    file.close();
    // with this we can ask ourselves what number to put in. this markov order k
    // the higher it is the more it looks like file's text.
    int k = getIntegerInARange(1, 10);

    // so basically this code constructs a model based on what k length we put it in.
    Map<string, Vector<char>> modelOfTheText = constructModel( wholeText,k);

    int maximum = 0;
    string mostRepeatedKSeed;
    // this code is supposed to find the most repeated k seed that we can use.
    for (string curr : modelOfTheText) {
        if (modelOfTheText[curr].size() > maximum) {
            maximum = modelOfTheText[curr].size();
            mostRepeatedKSeed = curr;
        }
    }
    // this code generates a text, in this case 2000 characters.
    string randomlyGeneratedText = generate(modelOfTheText, 2000, mostRepeatedKSeed);
    cout << "generated text: " << randomlyGeneratedText << endl;

    return 0;
}

// with the ifstream get method we can return text as a string
string makeWholeText(ifstream& file) {
    char c;
    string wholeText;
    while (file.get(c)) {
        wholeText += c;
    }
    return wholeText;
}
// if we dont put the markovs k in the range of 1-10 the method will asks us to put it in again.
int getIntegerInARange(int start, int end) {
    int number;
    while (true) {
        number = getInteger("enter markov oder (1 to 10): ");
        if (number <= 10 && number >= 1) {
            break;
        }
        cout << "you must input a number 1 to 10" << endl;
    }
    return number;
  }
//so this code is supposed to construct markovs model. it maps every single on of the k length seed
// to the characters which are followed after by.
Map<string, Vector<char>>  constructModel(string& wholeText, int k) {
    Map<string, Vector<char>> resultModel;
    for (int j = 0; j < wholeText.length() - k; j++) {
        char currChar = wholeText[j+k];
        string currSubstring = wholeText.substr(j, k);
        resultModel[currSubstring].add(currChar);
    }
    return resultModel;


}
// and lastly this code generates randomly n letter text .
string  generate(Map<string, Vector<char>>& modelOfTheText, int n, string mostRepeatedKSeed) {
    string newSeed = mostRepeatedKSeed;
    string res = newSeed;
    for (int j = 0; j < n; j++) {
        string line = newSeed.substr(newSeed.length() - mostRepeatedKSeed.length());
        // if the seed is not in the model we tell the code to stop.
        if (!modelOfTheText.containsKey(line)) {
            break;
        }
        Vector<char>& charsThatArePossible = modelOfTheText[line];
        int rand = randomInteger(0, charsThatArePossible.size() - 1);
        char currCharacter = charsThatArePossible[rand];
        res += currCharacter;
        newSeed = newSeed.substr(1) + currCharacter;
    }
    return res;
}
