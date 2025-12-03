/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);
void helperForListing(string currString, string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();


    /* [TODO: Implement this!] */

    // we can put proteins and it will print all of the possibilities.
    // if we want to get out of this while loop we just press enter.
    while (true) {
        string protein = getLine("input protein (or if you want to RETURN press enter) : ");


        if (protein.empty()) {
            break;
        }
        cout << "possibilities of all RNA strands for this " << protein << " protein are :" << endl;
        listAllRNAStrandsFor(protein, codons);
    }


    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
// this is our main recursive code.
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
    string empty = "";
    helperForListing(empty, protein, codons);
    
}
//helper
void helperForListing(string currString,string protein, Map<char, Set<string> >& codons) {
    // this is our base case, if protein length is 0 that means that every protein was included .
    if (protein.length() == 0) {
        cout << currString << endl;
        return;
    }
   
    else {
        char firstChar = protein[0];
        string substringOfString = protein.substr(1);
        // and lastly this is our recursive code which generates protein chracters .
        // we loop through every codon.
        foreach(string currCodon in codons[firstChar]) {
            helperForListing(currString + currCodon,substringOfString, codons);
        }
    }
}
