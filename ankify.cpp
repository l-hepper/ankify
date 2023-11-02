#include <iostream>
#include <fstream>
using namespace std;

void standardIteration(string fileName);
int cardCount(string fileName);
void formatForAnki(string fileName);

int main(int argc, char* argv[]) {

    string fileName = argv[1];
    formatForAnki(fileName);

    return 0;
}

// Counts the number of 'cards' produced from the text file by counting the lines and dividing by 2 (there are two lines to each card - front and back)
int cardCount(string fileName) {

    fstream inputFile(fileName);

    int lineCount {0};
    string line {};
    while (getline(inputFile, line)) {

        if (line == "") {
            continue;
        } else {
            lineCount++;
        }
    }

    // TODO - add check for odd number of lines/empty file, etc, or even tabs in the file which would throw off the anki formatting

    return lineCount / 2;
}


// iterates over text file displaying each card - first front, then back.
void standardIteration(string fileName) {

    fstream inputFile(fileName);

    // clear the screen and set cursor position to top-left
    cout << "\033[2J";
    cout << "\033[H";

    int cardCountTotal = cardCount(fileName);
    int currentCard {1};

    bool backOfCard = false; // flag used to track if the front or back of the card has been displayed
    string line {};
    while (getline(inputFile, line)) {

        if (line == "") 
            continue;

        if (!backOfCard)
            cout << currentCard << "/" << cardCountTotal << endl;
            
        cout << "\t" << line << endl;
        cin.get();

        if (backOfCard) {
            // clear the terminal, restore cursor position, reset flag
            cout << "\033[2J";
            cout << "\033[H";
            backOfCard = false;
            currentCard++;
        } else {
            backOfCard = true;
        }
    }

    inputFile.close();
}



void formatForAnki(string fileName) {

    fstream inputFile(fileName);

    ofstream outputFile(fileName + "_for_anki.txt");
    outputFile << "\t" << endl;

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

}