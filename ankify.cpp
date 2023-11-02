#include <iostream>
#include <fstream>
using namespace std;


void standardIteration(string fileName);

int main(int argc, char* argv[]) {



    string fileName = argv[1];
    standardIteration(fileName);




    return 0;
}


// iterates over text file displaying each card - first front, then back.
void standardIteration(string fileName) {

    fstream inputFile(fileName);

    // clear the screen and save the cursor position
    cout << "\033[2J";
    cout << "\033[s";

    bool backOfCard = false; // flag used to track if the front or back of the card has been displayed
    string line {};
    while (getline(inputFile, line)) {

        if (line == "") {
            continue;
        }

        cout << "\t" << line << endl;
        cin.get();

        if (backOfCard) {
            // clear the terminal, restore cursor position, reset flag
            cout << "\033[2J";
            cout << "\033[u";
            backOfCard = false;
        } else {
            backOfCard = true;
        }
    }

    inputFile.close();
}