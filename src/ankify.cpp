#include <iostream>
#include <fstream>
#include <ios>
#include <regex>
#include <limits>

#include "Card.h"
#include "Deck.h"

#include "validate.h"
#include "mode.h"
#include "generativeai.h"


using namespace std;

// prototypes
void review(string fileName);
void prompt(string fileName);
void overkill(std::vector<Card> deck);

void formatForAnki(string fileName);

int main(int argc, char* argv[]) {

    // ankify only works with 3 arguments in the command - i.e. ankify [-OPTION] [-FILEPATH]
    if (!validate::correctNumberOfArguments(argc))
        return 1;

    validate::option = argv[1];
    validate::filePath = argv[2];

    if (!validate::validateFile())
        return 1;

    Deck* deck = new Deck(argv[2]);

    switch (argv[1][1]) {
        case 'r':
            mode::review(deck);
        break;
        case 'p':
            mode::prompt(deck);
        break;
        case 'a':
            formatForAnki(argv[2]);
        break;
    }
    
    cout << "\033[2J"; // clear the screen
    
    return 0;
}


// overkill iteration will begin by iterating through the first three cards until all three are answered correctly before adding an additional card
// the loop does not stop until all cards in the 'deck' are entered 100% correctly.
// overkill iteration then repeats in the opposite direction - N.B. this is called overkill for good reason and is not recommended for regular study
// void overkill(vector<Card> deck) {

//     cout << "\033[2J"; // clear the screen
//     cout << "\033[20;8H"; // set cursor position

//     int cardCountTotal = cardCount(deck);

//     string line {};
//     int correctCount {0};
//     int i = 0;
//     while (correctCount != cardCountTotal) {

//         line = deck[i].getFront();

//         cout << "\t" << line << endl;
//         cout << "\t";

//         string answer {};
//         getline(inputFile, answer);

//         string userInput {};
//         cout << "\n\tAnswer > ";
//         getline(cin, userInput);

//         if (userInput == answer) {
//             cout << "\n\t\033[32m\033[1mCORRECT.\033[0m" << endl << endl;
//             correctCount++;
//         } else {
//             cout << "\n\t\033[31m\033[1mINCORRECT.\033[0m" << endl << endl;
//             cout << "\tAnswer is: " << answer << endl;
//             correctCount = 0;
//         }

//         cout << endl << "\tCONTINUE >>";
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');

//         // clear the terminal, restore cursor position
//         cout << "\033[2J";
//         cout << "\033[u"; // restore cursor position
        
//     }

//     inputFile.close();
// }


// formats a plaintext file of question and answer notes (each separated by a \n) for direct import into Anki
void formatForAnki(string fileName) {

    fstream inputFile(fileName);

    fileName = regex_replace(fileName, regex(".txt"), ""); // solution for this form of replace found on stack overflow 
    ofstream outputFile(fileName + "_for_anki.txt");

    outputFile << "\t" << endl; // insert tab on top line so anki recognises this as character to parse cards

    // Iterate through the file - replacing the end of questions with a /TAB to delineate front of card from back of card
    string line;
    bool endOfQuestion {true};
    while (getline(inputFile, line)) {

        if (line == "") {
            continue;
        }

        if (endOfQuestion) {
            outputFile << line << "\t";
            endOfQuestion = false;
        } else {
            outputFile << line << endl;
            endOfQuestion = true;
        }
    }
    outputFile.close();
    inputFile.close();
}