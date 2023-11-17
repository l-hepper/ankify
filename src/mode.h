#ifndef _MODE_H_
#define _MODE_H_

using namespace std;

#include <iostream>
#include <limits>
#include "Deck.h"
#include "Card.h"

namespace mode {

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

        cout << word << endl;
    }

    void review(Deck *deck) {

        int cardCountTotal = deck->getCards().size();
        int currentCard {1};

        for (auto card : deck->getCards()) {

            cout << "\033[2J"; // clear the screen
            cout << "\033[15;8H"; // set cursor position
            printTitle();
            cout << "\033[36m\033[1m\tCURRENT CARD: \033[37m" << currentCard << "/" << cardCountTotal << "\033[0m" << endl << endl;

            cout << "\t" << card.getFront() << endl;
            cout << "\t";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // any key press will prompt showing the back of the card

            cout << "\t" << card.getBack() << endl;
            cout << "\n\n\t" << "CONTINUE >>";
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
            cout << "\033[15;8H"; // set cursor position
            printTitle();
            // these 4 lines are for the display of the status bar as the user iterates and works through the deck
            cout << "\033[36m\033[1m\tCURRENT CARD: \033[37m" << "\033[1m" << currentCard << "/" << cardCountTotal << "\033[0m";
            cout << "\033[32m\033[1m   CORRECT: \033[37m" << "\033[1m" << correct << "/" << cardCountTotal << "\033[0m";
            cout << "\033[31m\033[1m   INCORRECT: \033[37m" << "\033[1m" << incorrect << "/" << cardCountTotal << "\033[0m" << endl << endl;

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

    /*
    Variation of prompt mode - this mode begins with a pool of 2 cards, the user must get all cards in the pool correct to increase the size of the pool,
    on each pool reset the user must get all previous cards correct to increase the size of the pool again. If at any point the user gets any card incorrect,
    the pool size resets to 2. Not recommended for regular study, but useful for drilling information requiring fast retrieval times.
    */
    void overkillPrompt(Deck* deck) {

        cout << "\033[2J"; // clear the screen
        cout << "\033[20;8H"; // set cursor position

        int cardCountTotal = deck->getCards().size();

        int correctTotal {0};
        int i {0}; // iterator for the deck
        int currentPoolSize {2}; 
        while (correctTotal != cardCountTotal) {

            cout << "\033[2J"; // clear the screen
            cout << "\033[20;8H"; // set cursor position
            printTitle();
            // status bar
            cout << "\033[32m \033[1mCORRECT: \033[37m" << "\033[1m" << correctTotal << "/" << currentPoolSize << "\033[0m";
            cout << "\033[36m \033[1m\tCURRENT POOL SIZE: \033[37m" << "\033[1m" << currentPoolSize << "/" << cardCountTotal << "\033[0m";
            if (currentPoolSize == cardCountTotal)
                cout << "\033[35m \033[1m\t\tFINAL ITERATION \033[37m" << "\033[1m" << "\033[0m";
            cout << endl << endl;

            cout << "\t" << deck->getCards()[i].getFront() << endl;

            string answer {};
            cout << "\n\tANSWER >> ";
            getline(cin, answer);

            if (answer == deck->getCards()[i].getBack()) {
                cout << "\n\t\033[32m\033[1mCORRECT.\033[0m" << endl << endl;
                correctTotal++;
                i++;

                // the 'currentPoolSize < cardCountTotal' poolsize exceeds cardcountotal - this would result in an additional loop otherwise
                if (i == currentPoolSize && currentPoolSize < cardCountTotal) {
                    i = 0;
                    correctTotal = 0;
                    currentPoolSize++;
                }

            } else {
                cout << "\n\t\033[31m\033[1mINCORRECT.\033[0m" << endl << endl;
                cout << "\tAnswer is: " << deck->getCards()[i].getBack() << endl;

                currentPoolSize = 2;
                correctTotal = 0;
                i = 0;
            }


            cout << "\n\t" << "CONTINUE >> ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // any key press moves to the next card
        }
    }

}




#endif