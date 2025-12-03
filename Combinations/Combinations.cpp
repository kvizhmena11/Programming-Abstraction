/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */


#include "console.h"
#include <iostream>
#include "simpio.h"
using namespace std;

// in the assignment's description they told us that C(n, k) = C(n-1, k-1) + C(n-1, k)
// so i used this formula recursively . on the edges of the triangle the sum is 1 so thats the base case.
int combination(int n, int k) {
    if (k == 0 || n==k) {
        return 1;
    }
    
    else {
        return combination(n - 1, k - 1) + combination(n - 1, k);
    }
    
}
// i let the user choose n and k and then i print the combination of n and k.
int main() {
    // [TODO: fill in the code]
    int n = getInteger("input n: ");
    if (n < 0) {
        cout << "Invalid input, n must atleast be a 0." << endl;
        return 1;
    }
    int k = getInteger("input k: ");
    if (k< 0 || k>n) {
        cout << "Invalid input, k must atleast be a 0  and less or equal to n." << endl;
    }
    int number = combination( n,  k);
    cout << number << endl;
    return 0;
}
