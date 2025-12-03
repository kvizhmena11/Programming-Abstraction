/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence);

int main() {
    // [TODO: fill with your code]
    // we can input our main and subsequence texts.
    string text = getLine("input main text: ");
    string subsequence = getLine("input subsequence : ");
    // if its subsequence then we print that it is a subsequence,
    // if not then we print the relative message.
    if (isSubsequence(text, subsequence)) {
        cout << subsequence << " is subsequence of " << text << endl;
    }
    else {
        cout << subsequence << " is not subsequence of " << text << endl;
    }
    return 0;
}
// this is our main recursive method .
bool isSubsequence(string text, string subsequence) {
    // basecase is that if all of the characters in subsequence string are found then we return true.
    if (subsequence.empty()) {
        return true;
    }
    // but if the main text runs out letters then we return false.
    if (text.empty()) {
        return false;
    }
    //if they match, then we can move on to the next index of characters.
    if (subsequence[0] == text[0]) {
       return isSubsequence(text.substr(1), subsequence.substr(1));
    }
    // if they dont we only move our main text character index.
    else {
      
      return  isSubsequence(text.substr(1), subsequence);
    }
    
}

