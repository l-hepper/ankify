#include <iostream>
#include <fstream>
#include <ios>
#include <regex>
#include <limits>


using namespace std;

void standardIteration(string fileName);
void promptIteration(string fileName);

int cardCount(string fileName);
void formatForAnki(string fileName);

int main(int argc, char* argv[]) {

    string fileName = argv[1];
    standardIteration(fileName);


    cout << "\033[1;1H";
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

    cout << "\033[2J"; // clear the screen
    cout << "\033[20;8H"; // set cursor position
    cout << "\033[s"; // save cursor position

    int cardCountTotal = cardCount(fileName);
    int currentCard {1};

    bool backOfCard = false; // flag used to track if the front or back of the card has been displayed
    string line {};
    while (getline(inputFile, line)) {

        if (line == "") 
            continue;

        if (!backOfCard)
            cout << "\033[36m CARDS REMAINING: \033[37m" << "\033[1m" << currentCard << "/" << cardCountTotal << "\033[0m" << endl << endl;
            
        cout << "\t" << line << endl;
        cout << "\t";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (backOfCard) {
            cout << "\033[2J"; // clear the terminal
            cout << "\033[u"; // restore cursor position
            backOfCard = false;
            currentCard++;
        } else {
            backOfCard = true;
        }
    }

    inputFile.close();
}

// iterates over text file but prompts the user for input, displaying either CORRECT or INCORRECT
void promptIteration(string fileName) {

    fstream inputFile(fileName);

    // clear the screen and set cursor position to top-left
    cout << "\033[2J";
    cout << "\033[H";

    int cardCountTotal = cardCount(fileName);
    int currentCard {1};

    string line {};
    while (getline(inputFile, line)) {

        if (line == "") 
            continue;

        cout << "\033[36m CARDS REMAINING: \033[37m" << "\033[1m" << currentCard << "/" << cardCountTotal << "\033[0m" << endl << endl;

        cout << "\t" << line << endl;

        string answer {};
        getline(inputFile, answer);

        string userInput {};
        cout << "Enter your answer > ";
        getline(cin, userInput);

        if (userInput == answer) {
            cout << "CORRECT" << endl;
        } else {
            cout << "INCORRECT. Answer is: " << answer << endl;
        }

        cout << "CONTINUE >>";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // clear the terminal, restore cursor position, reset flag
        cout << "\033[2J";
        cout << "\033[H";
        currentCard++;
        
    }

    inputFile.close();
}


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

}