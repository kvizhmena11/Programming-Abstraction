#include <iostream>
#include "console.h"
#include "random.h"

using namespace std;
// prob of getting heads.
const double prob = 0.5;

int getCount() {
    int cnt = 0;
    int headsCount = 0;
    // we flip until we get 3 consecutive heads.
    while (headsCount < 3) {
        bool  randomProb = randomChance(0.5);// we randomly get either tails or heads.

        // if its heads we add heads count.
        if (randomProb) {
            headsCount++;
            cout << "heads" << endl;

        }
        //if its tails we make the heads count 0;
        else {
            headsCount = 0;
            cout << "tails" << endl;

        }
        cnt++;

    }
    return cnt;

}

int main() {
    // [TODO: fill in the code]
    int number = getCount();
    cout << "it took " << number << " tries to get 3 consecutive heads." << endl;
    return 0;
}