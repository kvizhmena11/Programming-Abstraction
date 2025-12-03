/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

/* Main program */




int main() {
    // [TODO: fill in the code]
    // lets the user input number.
    int number = getInteger("input integer: ");
    cout<<"int to string is : " << intToString(number) << endl;
    // lets the user input string.
   string text = getLine("input string: ");
   cout << "string to int is : " << stringToInt(text) << endl;
    return 0;
}

// if the int is a single digit number, then it return that number. 
// if the number is more or equal to 10 then we chop this number into two pieces
// and continue the code recursively.
// and lastly if the integer is negative we just add minus manualy and do the code recursively on negative number. 
string intToString(int n) {
    if (n == 0)return "0";
    if (n > 0 && n <= 9) {
        char nChar = char(n + '0');

        return string() + nChar;
    }
    else if (n >= 10) {
     
        int n1 = n % 10;
        int n2 = n / 10;
            char n1Char = char(n1 + '0');
            return intToString(n2)+ n1Char;
    }
    else {
        int negativeN = -n;
        return "-" + intToString(negativeN);
    
    }


}

// if string is empty then it return 0.
// if string starts with a - symbol then we do the recursive method on a substring,
// and we make it a negative number at the end.
// and lastly we do the recursive method and we use pow method to multiply digits by their place value.
int stringToInt(string str) {
   
    
    if (str.length() == 0) {
        return 0;
    }
    else if (str[0] == '-') {
        string stringWithoutSymbol = str.substr(1);
        return -stringToInt(stringWithoutSymbol);
    }
    else {
        int currNumber = str[0] - '0';
        string subs = str.substr(1);
        return currNumber * pow(10, str.length() - 1 ) + stringToInt(subs);
    
    }
}
