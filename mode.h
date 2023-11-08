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





        // while (getline(inputFile, line)) {

        //     if (line == "") 
        //         continue;

        //     if (!backOfCard)
        //         cout << "\033[36m CARDS REMAINING: \033[37m" << "\033[1m" << currentCard << "/" << cardCountTotal << "\033[0m" << endl << endl;
                
        //     cout << "\t" << line << endl;
        //     cout << "\t";

        //     cin.ignore(numeric_limits<streamsize>::max(), '\n');

        //     if (backOfCard) {
        //         cout << "\033[2J"; // clear the terminal
        //         cout << "\033[u"; // restore cursor position
        //         backOfCard = false;
        //         currentCard++;
        //     } else {
        //         backOfCard = true;
        //     }
        // }

    }
}




#endif