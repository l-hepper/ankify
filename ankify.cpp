#include <iostream>
#include <fstream>
#include <ios>
#include <regex>
#include <limits>

#include "Card.h"


using namespace std;

// prototypes
void standardIteration(string fileName);
void promptIteration(string fileName);
void overkillIteration(std::vector<Card> deck);

vector<Card> getArrayOfCards(string fileName);
void printDeck(vector<Card> deck);

int cardCount(string fileName);
void formatForAnki(string fileName);



int main(int argc, char* argv[]) {

    vector<Card> deck = getArrayOfCards(argv[1]);

    printDeck(deck);

}

// Takes in a text file of cards and iterates through the line generates Card objects to add to a deck array
vector<Card> getArrayOfCards(string fileName) {

    fstream inputFile(fileName);

    vector<Card> deck {};

    string front {};
    string back {};
    while (getline(inputFile, front)) {
        if (front == "")
            continue;

        getline(inputFile, back);
        Card newCard(front, back);
        deck.push_back(newCard);
    }

    inputFile.close();
    return deck;
}

// Takes in an entire deck and prints to ensure that text file has been passed and parsed correctly
void printDeck(const vector<Card> deck) {
    for (int i {0}; i < deck.size(); i++) {
        cout << "CARD " << i << " FRONT: " << deck[i].getFront() << endl;
        cout << "CARD " << i << " BACK: " << deck[i].getBack() << endl;
    }
}


// Counts the number of 'cards' produced from the text file by counting the lines and dividing by 2 (there are two lines to each card - front and back)
int cardCount(vector<Card> deck) {
    return deck.size();
}


// iterates over text file displaying each card - first front, then back.
// void standardIteration(string fileName) {

//     fstream inputFile(fileName);

//     cout << "\033[2J"; // clear the screen
//     cout << "\033[20;8H"; // set cursor position
//     cout << "\033[s"; // save cursor position

//     int cardCountTotal = cardCount(fileName);
//     int currentCard {1};

//     bool backOfCard = false; // flag used to track if the front or back of the card has been displayed
//     string line {};
//     while (getline(inputFile, line)) {

//         if (line == "") 
//             continue;

//         if (!backOfCard)
//             cout << "\033[36m CARDS REMAINING: \033[37m" << "\033[1m" << currentCard << "/" << cardCountTotal << "\033[0m" << endl << endl;
            
//         cout << "\t" << line << endl;
//         cout << "\t";

//         cin.ignore(numeric_limits<streamsize>::max(), '\n');

//         if (backOfCard) {
//             cout << "\033[2J"; // clear the terminal
//             cout << "\033[u"; // restore cursor position
//             backOfCard = false;
//             currentCard++;
//         } else {
//             backOfCard = true;
//         }
//     }

//     inputFile.close();
// }


// iterates over text file but prompts the user for the answer, then informs of correct and incorrect and tracks record
// void promptIteration(string fileName) {

//     fstream inputFile(fileName);

//     cout << "\033[2J"; // clear the screen
//     cout << "\033[20;8H"; // set cursor position

//     int cardCountTotal = cardCount(fileName);
//     int currentCard {1};
//     int correct {0};
//     int incorrect {0};
//     string line {};
//     while (getline(inputFile, line)) {

//         if (line == "") 
//             continue;

//         // these 4 lines are for the display of the status bar as the user iterates and works through the deck
//         cout << "\033[36m CARDS REMAINING: \033[37m" << "\033[1m" << currentCard << "/" << cardCountTotal << "\033[0m";
//         cout << "\033[32m \tCORRECT: \033[37m" << "\033[1m" << correct << "/" << cardCountTotal << "\033[0m";
//         cout << "\033[31m \tINCORRECT: \033[37m" << "\033[1m" << incorrect << "/" << cardCountTotal << "\033[0m" << endl << endl;
//         cout << "\t" << line << endl;

//         string answer {};
//         getline(inputFile, answer);

//         string userInput {};
//         cout << "\n\tAnswer > ";
//         getline(cin, userInput);

//         if (userInput == answer) {
//             cout << "\n\t\033[32m\033[1mCORRECT.\033[0m" << endl << endl;
//             correct++;
//         } else {
//             cout << "\n\t\033[31m\033[1mINCORRECT.\033[0m" << endl << endl;
//             cout << "\tAnswer is: " << answer << endl;
//             incorrect++;
//         }

//         cout << "\n\tCONTINUE >>";
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');

//         // clear the terminal, restore cursor position, reset flag
//         cout << "\033[2J";
//         cout << "\033[20;8H"; // set cursor position
//         currentCard++;
        
//     }

//     inputFile.close();
// }


// overkill iteration will begin by iterating through the first three cards until all three are answered correctly before adding an additional card
// the loop does not stop until all cards in the 'deck' are entered 100% correctly.
// overkill iteration then repeats in the opposite direction - N.B. this is called overkill for good reason and is not recommended for regular study
// void overkillIteration(vector<Card> deck) {

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