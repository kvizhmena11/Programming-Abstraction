/*
* File: Boggle.cpp
* ----------------
* Name : [TODO:enter name here]
* Section : [TODO:enter section leader here]
* This file is the main starter file for Assignment #4, Boggle.
* [TODO:extend the documentation]
*/

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"


using namespace std;

/*Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

const string STANDARD_CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
// i pushed in cubes in vector in order to return it after.
Vector<string> constCubes() {
    Vector<string> cubes;
    cubes.push_back("AAEEGN");
    cubes.push_back("ABBJOO");
    cubes.push_back("ACHOPS");
    cubes.push_back("AFFKPS");
    cubes.push_back("AOOTTW");
    cubes.push_back("CIMOTU");
    cubes.push_back("DEILRX");
    cubes.push_back("DELRVY");
    cubes.push_back("DISTTY");
    cubes.push_back("EEGHNW");
    cubes.push_back("EEINSU");
    cubes.push_back("EHRTVW");
    cubes.push_back("EIOSST");
    cubes.push_back("ELRTTY");
    cubes.push_back("HIMNQU");
    cubes.push_back("HLNNRZ");
    return cubes;
}




const string BIG_BOGGLE_CUBES[25] = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();

void askIfWantsPaint();

void manualPainting();
void randomPainting();

void startPlaying();

void playerTurn();
void computerTurn();

static Lexicon englishLexicon("EnglishWords.dat");


Grid<char> charBoard(4, 4);
Set<string> playerCorrectWords;

void highlightMethod(Grid<bool>& used);

bool playerWordExist(string line, Grid<char>& charBoard);
bool playerHelper(string& line, Grid<char>& charBoard, Grid<bool>& used, int row, int col, int index);

void generateRemainingWords(Set<string> playerCorrectWords, Grid<bool>& used, Set<string>& correctlyGeneratedWords,
    int row, int col, string curr, int &numbOfCorrects);
/* Main program */

int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);

    Lexicon englishLexicon("EnglishWords.dat");

    welcome();
    giveInstructions();
    // first i ask player if he wants to paint or not manully and then game starts.
    askIfWantsPaint();
    startPlaying();
    // when game ends, here comes the loop. in this loop we can end the game or start again.
    while (true) {
        string yesOrNo = getLine("if you want to restart type (yes), else (no): ");
        if (yesOrNo == "no") {
            cout << "thx for playing, good luck next time :))" << endl;
            break;
        }

        drawBoard(4, 4);

        askIfWantsPaint();
        startPlaying();


        
    }
   
    
    return 0;
}

/*
 * Function: welcome
 * Usage: welcome();
 * -----------------
 * Print out a cheery welcome message.
 */

void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: giveInstructions
 * Usage: giveInstructions();
 * --------------------------
 * Print out the instructions for the user.
 */

void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl << endl;
    cout << "Hit return when you're ready...";
    getLine();
}

// [TODO: Fill in the rest of the code]


// if input is yes then manual painting will start, else randompainting.
void askIfWantsPaint() {
    string ln = getLine("if you want to draw the board by yourself type (yes), else (no): ");
    if (ln == "yes") {
        manualPainting();
    }
    else if (ln == "no") {
        randomPainting();
    }
    else {
        cout << "input yes or no !!!" << endl;
        askIfWantsPaint();
    }
}
// we randomly choose cubes and its characters and by shuffling we set up the board.
void randomPainting() {
    Vector<string> cubes = constCubes();
    for (int i = 0; i < cubes.size(); i++) {
        int rand = randomInteger(i, cubes.size() - 1);
        swap(cubes[i], cubes[rand]);
    }

    int count = 0;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            string currCube = cubes[count++];
            char generatedLetter = currCube[randomInteger(0, 5)];
            charBoard.set(row, col, toupper(generatedLetter));


        }
    }
    drawBoard(4, 4);
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            char currLetter = charBoard[row][col];
            labelCube(row, col, currLetter);
        }
    }



}
// but here we can actually input 6 letter words and then it starts shuffling again.
void manualPainting() {
    Vector<string> manualCubes;

    for (int i = 0; i < 16; i++) {
        string line;
        while (line.length() != 6) {
            line = getLine(to_string(i + 1) + "'th cube (6 letters) :");
            line = toUpperCase(line);

        }
        manualCubes.push_back(line);

    }

    for (int i = 0; i < manualCubes.size(); i++) {
        int rand = randomInteger(i, manualCubes.size() - 1);
        swap(manualCubes[i], manualCubes[rand]);
    }

    int count = 0;
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            string currCube = manualCubes[count++];
            char generatedLetter = currCube[randomInteger(0, 5)];
            charBoard.set(row, col, toupper(generatedLetter));
        }
    }
    drawBoard(4, 4);
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            char currLetter = charBoard[row][col];
            labelCube(row, col, currLetter);
        }
    }
}
// fitst its humand turn then computers.
void startPlaying() {
    playerTurn();
    computerTurn();
}
// players turn, we have 4 cases and every single case is defined and working.
void playerTurn() {

    int playerScoringCount = 0;
    playerCorrectWords.clear();
   
    while (true) {
        string line = toUpperCase(trim(getLine("input a word you can see on the board  (or press return to quit) : ")));
        if (line.empty())break;
        if (line.length() < 4 || line.length() > 16) {
            cout << "word must be between 4 and 9 characters." << endl;
        }
        else if (playerCorrectWords.contains(line)) {
            cout << " you have already inputed that word" << endl;
        }
        else if (!englishLexicon.contains(line)) {
            cout << "such word doesnt exist in english words lexicon" << endl;
        }
        else  if (!playerWordExist(line, charBoard)) {
            cout << "you are lying! you cant create such word on board." << endl;
        }
        else {
            int currPoints = line.length() - 3;
            playerScoringCount += currPoints;
            playerCorrectWords.add(line);


            recordWordForPlayer(line, HUMAN);

            cout <<  "player  has been awarded with " << currPoints << " points." << endl;
        }

    }
}
// here is the main recursive method for human. it cheks if the word can be made up.
bool playerWordExist(string line, Grid<char>& charBoard) {

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            Grid<bool> used(4, 4);  
            for (int r = 0; r < 4; r++) {
                for (int c = 0; c < 4; c++) {
                    used[r][c] = false;
                }
            }
            if (playerHelper(line, charBoard, used, row, col, 0)) {
                highlightMethod(used);
                return true;
            }
        }
    }
    return false;

}
// and here we have helper for the main recursive method.

bool playerHelper(string& line, Grid<char>& charBoard, Grid<bool>& used, int row, int col, int index) {
    if (index == line.length()) {
        return true;
    }
    
    if (row < 0 || col < 0 || row >= 4 || col >= 4) {
        return false;
    }
    if (used[row][col]) return false;
    if (charBoard[row][col] != line[index]) return false;

    used[row][col] = true;

    for (int r = -1; r <= 1; r++) {
        for (int c = -1; c <= 1; c++) {
            if (r != 0 || c != 0) {
                if (playerHelper(line, charBoard, used, row + r, col + c, index + 1)) {
                    return true;
                }
            }
        }
    }

    used[row][col] = false;
    return false;
}
// our job was to visualise chosen words so thats what i did wiith this method.
void highlightMethod(Grid<bool>& used) {
    for (int r = 0; r < used.numRows(); r++) {
        for (int c = 0; c < used.numCols(); c++) {
            highlightCube(r, c, used[r][c]);
        }
    }
    pause(450);
    for (int r = 0; r < used.numRows(); r++) {
        for (int c = 0; c < used.numCols(); c++) {
            highlightCube(r, c, false);
        }
    }
}
// computers turn and as we can see i am using second recursive method which generates remaining words and 
// with other loops we can print them all. 
void computerTurn() {
    Set<string> correctlyGeneratedWords;
    string curr = "";
    int numbOfCorrects = 0;
    Grid<bool> used(4, 4);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            used[r][c] = false;
        }
    }
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            generateRemainingWords(playerCorrectWords, used, correctlyGeneratedWords, row, col, curr, numbOfCorrects);
        }
    }
    for (string line : correctlyGeneratedWords) {
        recordWordForPlayer(line, COMPUTER);
    }
    cout << "remaining words are: " << endl;
    for (string line : correctlyGeneratedWords) {
        cout << line << endl;
    }

    cout << "you missed " << correctlyGeneratedWords.size() << " words." << endl;
    cout << "I (COMPUTER) generated " << numbOfCorrects << " points" << endl;
}
// recursive method that finds all of the remaining words.
    void generateRemainingWords(Set<string> playerCorrectWords, Grid<bool>&used, Set<string>&correctlyGeneratedWords,
        int row, int col, string curr, int &numbOfCorrects) {
        
        if (row < 0 || col < 0 || row >= 4 || col >= 4) {
            return ;
        }
        if (used[row][col]) return ;
       
        curr += charBoard[row][col];
        if (!englishLexicon.containsPrefix(curr)) return;
        used[row][col] = true;

        if (curr.length() >= 4 && curr.length() <= 16 &&
            englishLexicon.contains(curr) &&
            !correctlyGeneratedWords.contains(curr) &&
            !playerCorrectWords.contains(curr)) {
            numbOfCorrects += curr.length() - 3;
            correctlyGeneratedWords.add(curr);
        }
           
            


        for (int r = -1; r <= 1; r++) {
            for (int c = -1; c <= 1; c++) {
                if (r != 0 || c != 0) {
                    generateRemainingWords(playerCorrectWords, used, correctlyGeneratedWords,
                        row + r, col + c, curr, numbOfCorrects);
                       
                    
                }
            }
        }
        used[row][col] = false;

    }