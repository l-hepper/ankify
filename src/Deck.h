#ifndef _DECK_H_
#define _DECK_H_
#include <iostream>
#include <vector>
#include <fstream>

#include "Card.h"

using namespace std;

class Deck {
    private:
        vector<Card> cardArray;

    public:
        // creates a deck and populates it with the provided text in the passed file
        Deck(string filePath) {

            fstream inputFile(filePath);

            string front {};
            string back {};

            while (getline(inputFile, front)) {
                if (front == "") 
                    continue;

                getline(inputFile, back);
                Card newCard(front, back);
                cardArray.push_back(newCard);
            }

            inputFile.close();
        }

        vector<Card> getCards() {
            return cardArray;
        }

        void addCard(Card card) {
            cardArray.push_back(card);
        }

        // prints all of the cards in the deck to the terminal
        void printDeck() {
            for (Card c : cardArray) {
                cout << "CARD FRONT: " << c.getFront() << endl;
                cout << "CARD BACK: " << c.getBack() << endl;
        }
}
};

#endif