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
void formatForAnki(string fileName);
void printTitle();

int main(int argc, char* argv[]) {

    printTitle();

    // ankify only works with 3 arguments in the command - i.e. ankify [-OPTION] [-FILEPATH]
    if (!validate::correctNumberOfArguments(argc))
        return 1;

    validate::option = argv[1];
    validate::filePath = argv[2];

    if (validate::option == "-q") {
        string prompt = generativeai::generatePromptToFormatCards(argv[2]);
        cout << prompt << endl;
        generativeai::apiRequestToGPT(prompt, argv[2]);
        return 1;
    }


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
        case 'x':
            mode::overkillPrompt(deck);
        case 'a':
            formatForAnki(argv[2]);
        break;
    }
    
    cout << "\033[2J"; // clear the screen
    
    return 0;
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
    inputFile.close();
}

void printTitle() {
    string word = R"(
                _    _  __       
    /\         | |  (_)/ _|      
   /  \   _ __ | | ___| |_ _   _ 
  / /\ \ | '_ \| |/ / |  _| | | |
 / ____ \| | | |   <| | | | |_| |
/_/    \_\_| |_|_|\_\_|_|  \__, |
                            __/ |
v1.0                       |___/ 
                        )";
}