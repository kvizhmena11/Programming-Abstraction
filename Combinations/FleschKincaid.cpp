/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "fstream"
#include "simpio.h"
#include <tokenscanner.h>

using namespace std;
const string endingCharacters = ".!?";
const string vowelCharacters = "AEIOUYaeiouy";
void countNumbersInText(TokenScanner scnr, int& syllable,
    int& word, int& sentence);
void printText(int word, int sentence, int syllable);
int syllableCounter(string tk);
double calculateGrade(int word, int sentence, int syllable);

//constants
const double c0 = -15.59;
const double c1 = 0.39;
const double c2 = 11.8;


int main() {
    // [TODO: fill in the code]
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
    TokenScanner scnr(file);
    scnr.ignoreWhitespace();
    // allows apostrophes.
    scnr.addWordCharacters("'");
    int syllable;
    int word;
    int sentence;

    countNumbersInText(scnr, syllable, word, sentence);
    file.close();
    // we dont want to divide by zero . 
    if (word == 0) {
        word = 1; 
    }
    if (sentence == 0) {
        sentence = 1;
    }
     printText( word,  sentence,  syllable);
     double finalGrade = calculateGrade(word, sentence, syllable);
     cout << "grade level: " << finalGrade << endl;

    return 0;
}
// checks if token is a word
bool isWord(const string& tk) {
    return !tk.empty() && isalpha(tk[0]);
}
// counts number of words syllables and sentences.
void countNumbersInText(TokenScanner scnr, int& syllable,
    int& word, int& sentence) {

    sentence = 0;
    word = 0;
    syllable = 0;

    while (scnr.hasMoreTokens()) {
        string tk = scnr.nextToken();

        // if last character ends with the symbols count it as sentece++.
        if (!tk.empty() && endingCharacters.find(tk.back()) != string::npos) {
            sentence++;
        }

        else if (isWord(tk)) {
            syllable += syllableCounter(tk);
            word++;
        }
    }
}
bool isVowel(char ch) {
    for (char curr : vowelCharacters) {
        if (ch == curr) {
            return true;
        }
    }
    return false;
}
    // counts syllables.
int syllableCounter(string tk) {
    int syllables = 0;
    bool lastWasVowel = false;

    for (size_t i = 0; i < tk.length(); i++) {
        char ch = tk[i];

        
        bool isCurrentVowel = isVowel(ch) || (ch == 'y' && (i > 0 && !isVowel(tk[i - 1])));

        if (isCurrentVowel) {
            // counts first vowel and not the other consecutive vowels.
            if (syllables == 0 || !lastWasVowel) {
                syllables++;
            }
            lastWasVowel = true;
        }
        else {
            lastWasVowel = false;
        }
    }

        // special case about words that end with 'e'
    if (tk.length() > 1 && tk.back() == 'e' && !isVowel(tk[tk.length() - 2]) && syllables > 1) {
        syllables--;
    }

    
    if (syllables < 1) {
        return 1;
    }
    else {
        return syllables;
    }
}

// calculates grade
double calculateGrade(int word, int sentence, int syllable) {
    return c0 +((c1 * (word / (double)sentence)) + (c2 * (syllable / (double)word)));
}

// method for printing words, sentences and syllables
void printText(int word, int sentence, int syllable){
    cout << "words: " << word << endl;
    cout << "sentences: " << sentence << endl;
    cout << "syllables : " << syllable << endl;
}
