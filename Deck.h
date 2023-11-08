#ifndef _DECK_H_
#define _DECK_H_
#include <iostream>
#include <vector>
#include <fstream>

#include "Card.h"

using namespace std;

class Deck {
    private:
        vector<Card> deck;
        size_t deckSize;

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
                deck.push_back(newCard);
                deckSize++;
            }

            inputFile.close();
        }

        size_t size() {
            return deckSize;
        }

        void addCard(Card card) {
            deck.push_back(card);
            deckSize++;
        }

        // prints all of the cards in the deck to the terminal
        void printDeck() {
            for (Card c : deck) {
                cout << "CARD FRONT: " << c.getFront() << endl;
                cout << "CARD BACK: " << c.getBack() << endl;
        }
}
};

#endif