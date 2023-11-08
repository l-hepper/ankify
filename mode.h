#ifndef _MODE_H_
#define _MODE_H_

using namespace std;

#include <iostream>
#include <limits>
#include "Deck.h"

namespace mode {

    void review(Deck *deck) {

        int cardCountTotal = deck->getCards().size();
        int currentCard {1};

        for (auto card : deck->getCards()) {

            cout << "\033[2J"; // clear the screen
            cout << "\033[20;8H"; // set cursor position

            cout << "\033[36m\033[1mCARDS REMAINING: \033[37m" << currentCard << "/" << cardCountTotal << "\033[0m" << endl << endl;

            cout << "\t" << card.getFront() << endl;
            cout << "\t";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // any key press will prompt showing the back of the card

            cout << "\t" << card.getBack() << endl;
            cout << "\n\t" << "CONTINUE >>";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // any key press moves to the next card

            currentCard++;
        }
    }

    void prompt(Deck *deck) {

        int cardCountTotal = deck->getCards().size();
        int currentCard {1};

        int correct {0};
        int incorrect {0};

        for (auto card : deck->getCards()) {

            cout << "\033[2J"; // clear the screen
            cout << "\033[20;8H"; // set cursor position

            // these 4 lines are for the display of the status bar as the user iterates and works through the deck
            cout << "\033[36m \033[1mCARDS REMAINING: \033[37m" << "\033[1m" << currentCard << "/" << cardCountTotal << "\033[0m";
            cout << "\033[32m \033[1m\tCORRECT: \033[37m" << "\033[1m" << correct << "/" << cardCountTotal << "\033[0m";
            cout << "\033[31m \033[1m\tINCORRECT: \033[37m" << "\033[1m" << incorrect << "/" << cardCountTotal << "\033[0m" << endl << endl;

            cout << "\t" << card.getFront() << endl;

            string answer {};
            cout << "\n\tANSWER >> ";
            getline(cin, answer);

            if (answer == card.getBack()) {
                cout << "\n\t\033[32m\033[1mCORRECT.\033[0m" << endl << endl;
                correct++;
            } else {
                cout << "\n\t\033[31m\033[1mINCORRECT.\033[0m" << endl << endl;
                cout << "\tAnswer is: " << card.getBack() << endl;
                incorrect++;
            }

            cout << "\n\t" << "CONTINUE >> ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // any key press moves to the next card

            currentCard++;
        }
    }
}




#endif