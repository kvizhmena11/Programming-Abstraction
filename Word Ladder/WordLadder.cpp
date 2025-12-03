/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include <lexicon.h>
#include <vector>
#include <set>
#include <queue>
#include "simpio.h"
using namespace std;
// english letters.
const string englishAlphabet = "abcdefghijklmnopqrstuvwxyz";
vector<string> shortestLadder(string startWord, string destination, Lexicon& englishLexicon);



int main() {
    // [TODO: fill with your code]
    // here is stored lots of english words.
    Lexicon englishLexicon("EnglishWords.dat");
    while (true) {

        // we can input start word.
        string startWord = getLine("enter start word (RETURN to quit) :  ");
        // if we return the program breaks.
        if (startWord.size() == 0) {
            cout << "the end" << endl;
            break;
        }
        // we can input destination word.
        string destination= getLine("enter destination word: ");
        // if this lexicon does not contain destination or startword then this code prints that the words must be english words and then continues.
        if (!(englishLexicon.contains(destination) && englishLexicon.contains(startWord))) {
            cout << "startWord and destination must be english words" << endl;
            continue;
        }
        // these two words must be equal size.
        if (destination.length() != startWord.length()) {
            cout << "startWord and destination must be equal length!!!" << endl;
            continue;
        }
        // calculates shortest ladder and we store it in res.
        vector<string> res = shortestLadder(startWord, destination, englishLexicon);
        // if its not empty then it prints words with space.
        if (!res.empty()) {
            cout << "found ladder : ";
            for (size_t j = 0; j < res.size(); j++) {
                cout << res[j];
                if (j != res.size() - 1) {
                    cout << " ";
                }
            }
            cout << endl;
        }
        // if its empty then it prints no ladder found.
        else {
            cout << "no ladder found" << endl;
        }
    }

    return 0;
}
// this method finds the shortest word ladder.
vector<string> shortestLadder(string startWord, string destination, Lexicon& englishLexicon) {
    // we store already used words. this helps us to avoid looping.
    set<string> alreadyUsedWords;
    // we keep track.
    queue<vector<string>> track;
    vector<string> ladder;
    ladder.push_back(startWord);
    alreadyUsedWords.insert(startWord);
    // we push ladder to the queue.
    track.push(ladder);

    vector<string> currtrack;
    while (!track.empty()) {
        currtrack = track.front();
        track.pop();
        // if current tracks last word matches with the destination then we return currtrack.
            if (currtrack.back() == destination) {
                return currtrack;
            }
            for (int k = 0; k < (currtrack.back()).length(); k++) {
                // we replace each letter of the word with all 26 other letters.
                for (char ch : englishAlphabet) {
                    // if characters match we skip. we dont need consider that.
                    if (ch == (currtrack.back())[k]) {
                        continue;
                    }
                    string neighbour = currtrack.back();
                    neighbour[k] = ch;
                    // we check if the word exists in the leciton and that its not used.
                    if (!alreadyUsedWords.count(neighbour) && englishLexicon.contains(neighbour)) {
                        vector<string> otherTrack = currtrack;
                        otherTrack.push_back(neighbour);
                        track.push(otherTrack);
                        alreadyUsedWords.insert(neighbour);
                    }
                }
            }
    }
    // if there was no ladder we return empty vector.
    return {};

}
