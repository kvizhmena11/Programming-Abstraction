/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);
//helper 
bool helpIsSurrounded(Set<string> surroundedCities,
    Set<string>& cities,
    Vector< Set<string> >& locations,
    int numHospitals,
    Vector< Set<string> >& result,
    int indexOfLocation);


int main() {
    /* TODO: Add testing code here! */
    Vector<Set<string>> result;
    Vector<Set<string>> locations;
    Set<string> hospital;
    // so basically what i did was i inputed the cities hospital 1 covers,add them to locations
    // and then clear the hospital.
    hospital.add("A");
    hospital.add("B");
    hospital.add("C");
    locations.add(hospital);
    hospital.clear();
    // this is hospital2
    hospital.add("A");
    hospital.add("C");
    hospital.add("D");
    locations.add(hospital);
    hospital.clear();
    //hospital 3
    hospital.add("B");
    hospital.add("F");
    locations.add(hospital);
    hospital.clear();

    // and hospital 4
    hospital.add("C");
    hospital.add("E");
    hospital.add("F");
    locations.add(hospital);
    hospital.clear();
    Set<string> cities;
    // i just added cities.
    cities.add("A");
    cities.add("B");
    cities.add("C");
    cities.add("D");
    cities.add("E");
    cities.add("F");
    
   
    int numHospitals = getInteger("input the number of hospitals for cities : ");
    //so this function checks if numHospitals can cover all of the cities.
    if (canOfferUniversalCoverage(cities, locations, numHospitals, result)) {
        // if it does then it prints result.
        cout << "it is possible to cover all of the cities" << endl;
        cout << "result of hospitals: " << endl;
        foreach(Set<string> city in result) {
            cout << city <<endl;
        }

    }
    // else it prints not possible.
    else {
        cout << "it is not possible"<<endl;
    }
    return 0;

}
// this is our main recursive backtracking method.
bool canOfferUniversalCoverage(Set<string>& cities,
    Vector< Set<string> >& locations,
    int numHospitals,
    Vector< Set<string> >& result) {
    Set<string> currentlySurroundedCities;
    return helpIsSurrounded(currentlySurroundedCities,
        cities,
        locations,
        numHospitals ,
        result,
        0);
    
}
// and this is a helper for our main backtracking method.
bool helpIsSurrounded(Set<string> surroundedCities,
    Set<string>& cities,
    Vector< Set<string> >& locations,
    int numHospitals,
    Vector< Set<string> >& result,
    int indexOfLocation) {
    
    if (numHospitals == 0) {
        return surroundedCities == cities;
    }
    // basecase, if all of the cities are covered.
    if (surroundedCities == cities) {
        return true;
    }
    // if there are no hospitals left it return false.
    if (locations.size() <= indexOfLocation) {
        return false;
    }
    // so then we divide our code into two methods. this is the first 
    // method where we include current hospital.
    
    Vector<Set<string>> IncludedLocationResult = result;
    IncludedLocationResult.add(locations[indexOfLocation]);
    Set<string> currentSurroundedCities = locations[indexOfLocation] + surroundedCities;

    if (helpIsSurrounded(currentSurroundedCities,
        cities,
        locations,
        numHospitals-1,
        IncludedLocationResult,
        indexOfLocation+1)) {
        result = IncludedLocationResult;
        return true;
    }

    // and this second method just skips the current hospital.
    Vector<Set<string>> notIncludedLocationResult = result;

    if (helpIsSurrounded(surroundedCities,
        cities,
        locations,
        numHospitals,
        notIncludedLocationResult,
        indexOfLocation + 1)) {
        result = notIncludedLocationResult;
        return true;
    }
    return false;
}